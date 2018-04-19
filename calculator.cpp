#include <QtWidgets>
#include <math.h>
#include <QtMath>
#include "button.h"
#include "calculator.h"

Calculator::Calculator(QWidget *parent) : QDialog(parent) {
 sumInMemory = 0.0;
 sumSoFar = 0.0;
 factorSoFar = 0.0;
 waitingForOperand = true;

 display = new QLineEdit("0");
 display->setReadOnly(true);
 display->setAlignment(Qt::AlignRight);
 display->setMaxLength(15);
 display->installEventFilter(this);

 QFont font = display->font();
 font.setPointSize(font.pointSize() + 8);
 display->setFont(font);

 QColor digitColor(150, 205, 205);
 QColor backspaceColor(225, 185, 135);
 QColor memoryColor(100, 155, 155);
 QColor operatorColor(155, 175, 195);

 for (int i = 0; i < NumDigitButtons; ++i) {
  digitButtons[i] = createButton(QString::number(i), digitColor, SLOT(digitClicked()));
 }

 pointButton = createButton(tr("."), digitColor, SLOT(pointClicked()));
 changeSignButton = createButton(tr("+/-"), digitColor, SLOT(changeSignClicked()));
 backspaceButton = createButton(tr("Bksp"), backspaceColor, SLOT(backspaceClicked()));
 clearButton = createButton(tr("Clear"), backspaceColor, SLOT(clear()));
 clearAllButton = createButton(tr("Clear All"), backspaceColor.light(120), SLOT(clearAll()));
 clearMemoryButton = createButton(tr("MC"), memoryColor, SLOT(clearMemory()));
 readMemoryButton = createButton(tr("MR"), memoryColor, SLOT(readMemory()));
 setMemoryButton = createButton(tr("MS"), memoryColor, SLOT(setMemory()));
 addToMemoryButton = createButton(tr("M+"), memoryColor, SLOT(addToMemory()));
 divisionButton = createButton(tr("/"), operatorColor, SLOT(multiplicativeOperatorClicked()));
 timesButton = createButton(tr("*"), operatorColor, SLOT(multiplicativeOperatorClicked()));
 minusButton = createButton(tr("-"), operatorColor, SLOT(additiveOperatorClicked()));
 plusButton = createButton(tr("+"), operatorColor, SLOT(additiveOperatorClicked()));
 squareRootButton = createButton(tr("Sqrt"), operatorColor, SLOT(unaryOperatorClicked()));
 powerButton = createButton(tr("x^2"), operatorColor, SLOT(unaryOperatorClicked()));
 reciprocalButton = createButton(tr("1/x"), operatorColor, SLOT(unaryOperatorClicked()));
 equalButton = createButton(tr("="), operatorColor.light(120), SLOT(equalClicked()));
 sinButton = createButton(tr("sin"), operatorColor, SLOT(unaryOperatorClicked()));
 cosButton = createButton(tr("cos"), operatorColor, SLOT(unaryOperatorClicked()));
 tanButton = createButton(tr("tan"), operatorColor, SLOT(unaryOperatorClicked()));
 logButton = createButton(tr("ln"), operatorColor, SLOT(unaryOperatorClicked()));
 expButton = createButton(tr("exp"), operatorColor, SLOT(unaryOperatorClicked()));
 powButton = createButton(tr("x^y"), operatorColor, SLOT(multiplicativeOperatorClicked()));

 QGridLayout *mainLayout = new QGridLayout;
 mainLayout->setSizeConstraint(QLayout::SetFixedSize);

 mainLayout->addWidget(display, 0, 0, 1, 6);
 mainLayout->addWidget(backspaceButton, 1, 0, 1, 2);
 mainLayout->addWidget(clearButton, 1, 2, 1, 2);
 mainLayout->addWidget(clearAllButton, 1, 4, 1, 2);

 mainLayout->addWidget(clearMemoryButton, 2, 0);
 mainLayout->addWidget(readMemoryButton, 3, 0);
 mainLayout->addWidget(setMemoryButton, 4, 0);
 mainLayout->addWidget(addToMemoryButton, 5, 0);

 for (int i = 1; i < NumDigitButtons; ++i) {
  int row = ((9 - i) / 3) + 2;
  int column = ((i - 1) % 3) + 1;
  mainLayout->addWidget(digitButtons[i], row, column);
 }

 mainLayout->addWidget(digitButtons[0], 5, 1);
 mainLayout->addWidget(pointButton, 5, 2);
 mainLayout->addWidget(changeSignButton, 5, 3);

 mainLayout->addWidget(divisionButton, 2, 4);
 mainLayout->addWidget(timesButton, 3, 4);
 mainLayout->addWidget(minusButton, 4, 4);
 mainLayout->addWidget(plusButton, 5, 4);

 mainLayout->addWidget(squareRootButton, 2, 5);
 mainLayout->addWidget(powerButton, 3, 5);
 mainLayout->addWidget(reciprocalButton, 4, 5);
 mainLayout->addWidget(equalButton, 5, 5);
 mainLayout->addWidget(sinButton, 2, 7);
 mainLayout->addWidget(cosButton, 3, 7);
 mainLayout->addWidget(tanButton, 4, 7);
 mainLayout->addWidget(logButton, 5, 7);
 mainLayout->addWidget(expButton, 1, 7);
 mainLayout->addWidget(powButton, 0, 7);
 setLayout(mainLayout);

 setWindowTitle(tr("Calculator"));
}

bool Calculator::eventFilter(QObject *target, QEvent *event) {
 if (target == display) {
  if (event->type() == QEvent::MouseButtonPress
  || event->type() == QEvent::MouseButtonDblClick
  || event->type() == QEvent::MouseButtonRelease
  || event->type() == QEvent::ContextMenu) {
   QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
   if (mouseEvent->buttons() & Qt::LeftButton) {
    QPalette newPalette = palette();
    newPalette.setColor(QPalette::Base, display->palette().color(QPalette::Text));
    newPalette.setColor(QPalette::Text, display->palette().color(QPalette::Base));
    display->setPalette(newPalette);
   }
   else {
    display->setPalette(palette());
   }
   return true;
  }
 }
 return QDialog::eventFilter(target, event);
}

void Calculator::digitClicked() {
 Button *clickedButton = qobject_cast<Button *>(sender());
 int digitValue = clickedButton->text().toInt();
 if (display->text() == "0" && digitValue == 0.0) return;
 if (waitingForOperand) {
  display->clear();
  waitingForOperand = false;
 }
 display->setText(display->text() + QString::number(digitValue));
}

void Calculator::unaryOperatorClicked() {
 Button *clickedButton = qobject_cast<Button *>(sender());
 QString clickedOperator = clickedButton->text();
 double operand = display->text().toDouble();

 double result = 0.0;

 if (clickedOperator == tr("Sqrt")) {
  if (operand < 0.0) {
   abortOperation();
   return;
  }
  result = sqrt(operand);
 }
 else if (clickedOperator == tr("x^2")) {
  result = pow(operand, 2.0);
 }
 else if (clickedOperator == tr("1/x")) {
  if (operand == 0.0) {
   abortOperation();
   return;
  }
  result = 1.0 / operand;
 }
 else if (clickedOperator ==( "sin"))
{


    result = qSin(operand);
}

else if (clickedOperator ==( "cos"))
{
    result = qCos(operand);
}
else if (clickedOperator ==( "tan"))
{ /*if (operand == 0.0) {
         abortOperation();
         return;}*/
    result = qTan(operand);
}
else if (clickedOperator ==( "ln"))
{
  if (operand == 0.0) {
             abortOperation();
             return;

    result = log(operand);
}
     }
 else if (clickedOperator ==( "exp"))
 {
     result = qExp(operand);
 }

 display->setText(QString::number(result));
 waitingForOperand = true;
}

void Calculator::additiveOperatorClicked() {
 Button *clickedButton = qobject_cast<Button *>(sender());
 QString clickedOperator = clickedButton->text();
 double operand = display->text().toDouble();

 if (!pendingMultiplicativeOperator.isEmpty()) {
  if (!calculate(operand, pendingMultiplicativeOperator)) {
   abortOperation();
   return;
  }
  display->setText(QString::number(factorSoFar));
  operand = factorSoFar;
  factorSoFar = 0.0;
  pendingMultiplicativeOperator.clear();
 }

 if (!pendingAdditiveOperator.isEmpty()) {
  if (!calculate(operand, pendingAdditiveOperator)) {
   abortOperation();
   return;
  }
  display->setText(QString::number(sumSoFar));
 }
 else {
  sumSoFar = operand;
 }

 pendingAdditiveOperator = clickedOperator;
 waitingForOperand = true;
}

void Calculator::multiplicativeOperatorClicked() {
 Button *clickedButton = qobject_cast<Button *>(sender());
 QString clickedOperator = clickedButton->text();
 double operand = display->text().toDouble();

 if (!pendingMultiplicativeOperator.isEmpty()) {
  if (!calculate(operand, pendingMultiplicativeOperator)) {
   abortOperation();
   return;
  }
  display->setText(QString::number(factorSoFar));
 }
 else {
  factorSoFar = operand;
 }

 pendingMultiplicativeOperator = clickedOperator;
 waitingForOperand = true;
}

void Calculator::equalClicked() {
 double operand = display->text().toDouble();

 if (!pendingMultiplicativeOperator.isEmpty()) {
  if (!calculate(operand, pendingMultiplicativeOperator)) {
   abortOperation();
   return;
  }
  operand = factorSoFar;
  factorSoFar = 0.0;
  pendingMultiplicativeOperator.clear();
 }
 if (!pendingAdditiveOperator.isEmpty()) {
  if (!calculate(operand, pendingAdditiveOperator)) {
   abortOperation();
   return;
  }
  pendingAdditiveOperator.clear();
 }
 else {
  sumSoFar = operand;
 }

 display->setText(QString::number(sumSoFar));
 sumSoFar = 0.0;
 waitingForOperand = true;
}



void Calculator::pointClicked() {
 if (waitingForOperand) display->setText("0");
 if (!display->text().contains(".")) display->setText(display->text() + tr("."));
 waitingForOperand = false;
}

void Calculator::changeSignClicked() {
 QString text = display->text();
 double value = text.toDouble();
 if (value > 0.0) text.prepend(tr("-"));
 else if (value < 0.0) text.remove(0, 1);
 display->setText(text);
}

void Calculator::backspaceClicked() {
 if (waitingForOperand) return;

 QString text = display->text();
 text.chop(1);
 if (text.isEmpty()) {
  text = "0";
  waitingForOperand = true;
 }
 display->setText(text);
}

void Calculator::clear() {
 if (waitingForOperand) return;
 display->setText("0");
 waitingForOperand = true;
}

void Calculator::clearAll() {
 sumSoFar = 0.0;
 factorSoFar = 0.0;
 pendingAdditiveOperator.clear();
 pendingMultiplicativeOperator.clear();
 display->setText("0");
 waitingForOperand = true;
}

void Calculator::clearMemory() {
 sumInMemory = 0.0;
}

void Calculator::readMemory() {
 display->setText(QString::number(sumInMemory));
 waitingForOperand = true;
}

void Calculator::setMemory() {
 equalClicked();
 sumInMemory = display->text().toDouble();
}

void Calculator::addToMemory() {
 equalClicked();
 sumInMemory += display->text().toDouble();
}

Button *Calculator::createButton(const QString &text, const QColor &color, const char *member) {
 Button *button = new Button(text, color);
 connect(button, SIGNAL(clicked()), this, member);
 return button;
}

void Calculator::abortOperation() {
 clearAll();
 display->setText(tr("ERROR"));
}

bool Calculator::calculate(double rightOperand, const QString &pendingOperator) {
 if (pendingOperator == tr("+")) sumSoFar += rightOperand;
 else if (pendingOperator == tr("-")) sumSoFar -= rightOperand;
 else if (pendingOperator == tr("*")) factorSoFar *= rightOperand;
  if (pendingOperator == tr("/")) {
  if (rightOperand == 0.0) return false;
  factorSoFar /= rightOperand;
 }
 else if (pendingOperator == tr("x^y")) {

     factorSoFar = qExp(rightOperand * log(factorSoFar));

 }
 return true;
}




