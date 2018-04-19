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
 bool eventFilter(QObject *target, QEvent *event);//Фильтр событий
private slots:
 void digitClicked();//Нажатие цифры
 void unaryOperatorClicked();//унарный оператор щелчка
 void additiveOperatorClicked();//сложение оператор нажатия
 void multiplicativeOperatorClicked();//умножение оператор нажатия
 void equalClicked();//нажатие равно
 void pointClicked();//нажатие точки
 void changeSignClicked();//нажатие изменения знака
 void backspaceClicked();//нажатие backspace
 void clear();//удаление
 void clearAll();//очистить все
 void clearMemory();//Очистка данных из ячейки памяти
 void readMemory();//Считать число из памяти
 void setMemory();//сохранение числа на дисплее в память
 void addToMemory();//добавить к числу в памяти число

private:
 Button *createButton (const QString &text, const QColor &color, const char *member);
 void abortOperation();//прерывание операции
 bool calculate (double rightOperand, const QString &pendingOperator);

 double sumInMemory;//сумма в памяти
 double sumSoFar;
 double factorSoFar;
 QString pendingAdditiveOperator;
 QString pendingMultiplicativeOperator;
 bool waitingForOperand;

 QLineEdit *display;

 enum { NumDigitButtons = 10 };
 Button *digitButtons[NumDigitButtons];

 Button *pointButton;//нажатие точки
 Button *changeSignButton;//изменение знака
 Button *backspaceButton;
 Button *clearButton;//нажатие очистки
 Button *clearAllButton;//нажатие удаление всего
 Button *clearMemoryButton;//нажатие MC удаление из памяти
 Button *readMemoryButton;//нажатие MR считывание из памяти
 Button *setMemoryButton;//нажатие MS сохранение числа в память
 Button *addToMemoryButton;//нажатие M+

 Button *divisionButton;//нажатие /
 Button *timesButton;//
 Button *minusButton;//нажатие -
 Button *plusButton;//нажатие +
 Button *squareRootButton;//нажатие sqrt
 Button *powerButton;
 Button *reciprocalButton;
 Button *equalButton;//нажатие равно
 Button *sinButton;
 Button *cosButton;
 Button *tanButton;
 Button *logButton;
 Button *expButton;
 Button *powButton;

};

#endif
