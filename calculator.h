#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDialog>

class QLineEdit;
class Button;

class Calculator : public QDialog {
 Q_OBJECT
public:
 Calculator(QWidget *parent = 0);
protected:
 bool eventFilter(QObject *target, QEvent *event);
private slots:
 void digitClicked();
 void unaryOperatorClicked();
 void additiveOperatorClicked();
 void multiplicativeOperatorClicked();
 void equalClicked();
 void pointClicked();
 void changeSignClicked();
 void backspaceClicked();
 void clear();
 void clearAll();
 void clearMemory();
 void readMemory();
 void setMemory();
 void addToMemory();
 void FClicked();
private:
 Button *createButton (const QString &text, const QColor &color, const char *member);
 void abortOperation();
 bool calculate (double rightOperand, const QString &pendingOperator);

 double sumInMemory;
 double sumSoFar;
 double factorSoFar;
 QString pendingAdditiveOperator;
 QString pendingMultiplicativeOperator;
 bool waitingForOperand;

 QLineEdit *display;

 enum { NumDigitButtons = 10 };
 Button *digitButtons[NumDigitButtons];

 Button *pointButton;
 Button *changeSignButton;
 Button *backspaceButton;
 Button *clearButton;
 Button *clearAllButton;
 Button *clearMemoryButton;
 Button *readMemoryButton;
 Button *setMemoryButton;
 Button *addToMemoryButton;

 Button *divisionButton;
 Button *timesButton;
 Button *minusButton;
 Button *plusButton;
 Button *squareRootButton;
 Button *powerButton;
 Button *reciprocalButton;
 Button *equalButton;
 Button *FButton;
};

#endif
