#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_setAbutton_clicked();//задание столбцов и строк матрицы А

    void on_setBbutton_clicked();//задание столбцов и строк для матрицы В

    void on_detAbutton_clicked();//вычисление определителя матрицы А

    void on_detBbutton_clicked();//вычисление определителя матрицы B

    void on_mulbyAbutton_clicked();//умножение матрицы А на число

    void on_mulbyBbutton_clicked();//умножение матрицы В на число

    void on_inverseAbutton_clicked();//Обратная матрица А

    void on_inverseBbutton_clicked();//Обратная матрица В

    void on_transAbutton_clicked();//Транспонированная матрица А

    void on_transBbutton_clicked();//Транспонированная матрица А

    void on_addButton_clicked();//Сложение матриц

    void on_subButton_clicked();//Вычитание матриц

    void on_multButton_clicked();//Умножение матриц


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
