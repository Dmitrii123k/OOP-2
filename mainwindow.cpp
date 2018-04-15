#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Matrix.h"
#include "somefunctions.h"
#include <QtGui>
#include <QErrorMessage>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_setAbutton_clicked()//задание столбцов и строк матрицы А
{
    int rows = ui->rowsAspinBox->value();
    int cols = ui->colsAspinBox->value();
    if ((rows!=0) && (cols!=0)){
        Matrix tmp(rows, cols);
        ui->matrixAtable->setRowCount(rows);
        ui->matrixAtable->setColumnCount(cols);
        MatrixToTable(tmp, ui->matrixAtable);
    }

}

void MainWindow::on_setBbutton_clicked()//задание столбцов и строк для матрицы В
{
    int rows = ui->rowsBspinBox->value();
    int cols = ui->colsBspinBox->value();
    if ((rows!=0) && (cols!=0)){
        Matrix tmp(rows, cols);
        ui->matrixBtable->setRowCount(rows);
        ui->matrixBtable->setColumnCount(cols);
        MatrixToTable(tmp, ui->matrixBtable);
    }

}

void MainWindow::on_detAbutton_clicked()//вычисление определителя матрицы А
{
    int rows = ui->matrixAtable->rowCount();
    int cols = ui->matrixAtable->columnCount();
    if ((rows!=0) && (cols!=0)){
        if (rows == cols){//проверка размера матрицы
            try{
                Matrix tmp = TableToMatrix(ui->matrixAtable);
                double det = tmp.Det();//вычисляем определитель
                QString str = QString::number(det, 'f', 5);//перевод в строку вещ.числа
                ui->detAlabel->setText(str);//вывод строки в метку
            }
            catch (int error){//обработка исключения некорректных входных данных
                if (error == 111)
                    ShowErrorMsg(1);
            }
        }
        else{
            ShowErrorMsg(2);
        }
    }

}

void MainWindow::on_detBbutton_clicked()//вычисление определителя матрицы B
{
    int rows = ui->matrixBtable->rowCount();
    int cols = ui->matrixBtable->columnCount();
    if ((rows!=0) && (cols!=0)){
        if (rows == cols){//проверка размера матрицы
            try{
                Matrix tmp = TableToMatrix(ui->matrixBtable);
                double det = tmp.Det();//вычисляем определитель
                QString str = QString::number(det, 'f', 5);//перевод в строку вещ.числа
                ui->detBlabel->setText(str);//вывод строки в метку
            }
            catch (int error){//обработка исключения некорректных входных данных
                if (error == 111)
                    ShowErrorMsg(1);
            }
        }
        else{
            ShowErrorMsg(2);
        }
    }

}

void MainWindow::on_mulbyAbutton_clicked()
{
    int rows = ui->matrixAtable->rowCount();
    int cols = ui->matrixAtable->columnCount();
    if ((rows!=0) && (cols!=0)){
        try{
            Matrix tmp = TableToMatrix(ui->matrixAtable);
            QString s = ui->mulAlineEdit->text();
            bool ok;
            double mul = s.toDouble(&ok);
            if (!ok)
                throw 112;
            tmp = tmp.MultBy(mul);//умножение матрицы на число
            ui->resTable->setRowCount(rows);
            ui->resTable->setColumnCount(cols);
            MatrixToTable(tmp, ui->resTable);
        }
        catch (int error){//обработка исключения некорректных входных данных
            if ((error == 111) || (error = 112))
                ShowErrorMsg(1);
        }
    }

}

void MainWindow::on_mulbyBbutton_clicked()
{
    int rows = ui->matrixBtable->rowCount();
    int cols = ui->matrixBtable->columnCount();
    if ((rows!=0) && (cols!=0)){
        try{
            Matrix tmp = TableToMatrix(ui->matrixBtable);
            QString s = ui->mulBlineEdit->text();
            bool ok;
            double mul = s.toDouble(&ok);
            if (!ok)
                throw 112;
            tmp = tmp.MultBy(mul);//умножение матрицы на число
            ui->resTable->setRowCount(rows);
            ui->resTable->setColumnCount(cols);
            MatrixToTable(tmp, ui->resTable);
        }
        catch (int error){//обработка исключения некорректных входных данных
            if ((error == 111) || (error = 112))
                ShowErrorMsg(1);
        }
    }
}

void MainWindow::on_inverseAbutton_clicked()//обратная матрица для A
{
    int rows = ui->matrixAtable->rowCount();
    int cols = ui->matrixAtable->columnCount();
    if ((rows!=0) && (cols!=0)){
        if (rows == cols){
            Matrix tmp = TableToMatrix(ui->matrixAtable);
            try{
                tmp = tmp.Reverse();
                ui->resTable->setRowCount(rows);
                ui->resTable->setColumnCount(cols);
                MatrixToTable(tmp,ui->resTable);
            }
            catch (int error){
                if (error == 124)
                    ShowErrorMsg(3);
                if (error == 123)
                    ShowErrorMsg(2);
            }
        }
        else{
            ShowErrorMsg(2);
        }
    }
}

void MainWindow::on_inverseBbutton_clicked()//обратная матрица для B
{
    int rows = ui->matrixBtable->rowCount();
    int cols = ui->matrixBtable->columnCount();
    if ((rows!=0) && (cols!=0)){
        if (rows == cols){
            Matrix tmp = TableToMatrix(ui->matrixBtable);
            try{
                tmp = tmp.Reverse();
                ui->resTable->setRowCount(rows);
                ui->resTable->setColumnCount(cols);
                MatrixToTable(tmp,ui->resTable);
            }
            catch (int error){
                if (error == 124)
                    ShowErrorMsg(3);
                if (error == 123)
                    ShowErrorMsg(2);
            }
        }
        else{
            ShowErrorMsg(2);
        }
    }
}

void MainWindow::on_transAbutton_clicked()//транспонирование матрицы A
{
    int rows = ui->matrixAtable->rowCount();
    int cols = ui->matrixAtable->columnCount();
    if ((rows!=0) && (cols!=0)){
        try{
            Matrix tmp = TableToMatrix(ui->matrixAtable);
            tmp = tmp.Trans();
            ui->resTable->setRowCount(cols);
            ui->resTable->setColumnCount(rows);
            MatrixToTable(tmp, ui->resTable);
        }
        catch(int error){
            if (error == 111)
                ShowErrorMsg(1);
        }
    }

}

void MainWindow::on_transBbutton_clicked()
{
    int rows = ui->matrixBtable->rowCount();
    int cols = ui->matrixBtable->columnCount();
    if ((rows!=0) && (cols!=0)){
        try{
            Matrix tmp = TableToMatrix(ui->matrixBtable);
            tmp = tmp.Trans();
            ui->resTable->setRowCount(cols);
            ui->resTable->setColumnCount(rows);
            MatrixToTable(tmp, ui->resTable);
        }
        catch(int error){
            if (error == 111)
                ShowErrorMsg(1);
        }
    }
}

void MainWindow::on_addButton_clicked()//сложение матриц
{
    int rows1 = ui->matrixAtable->rowCount();
    int cols1 = ui->matrixAtable->columnCount();
    int rows2 = ui->matrixBtable->rowCount();
    int cols2 = ui->matrixBtable->columnCount();
    if ((rows1!=0) && (cols1!=0) && (rows2!=0) && (cols2!=0)){
        try{
            Matrix tmp1 = TableToMatrix(ui->matrixAtable);
            Matrix tmp2 = TableToMatrix(ui->matrixBtable);
            Matrix res = tmp1+tmp2;
            ui->resTable->setRowCount(rows1);
            ui->resTable->setColumnCount(cols1);
            MatrixToTable(res, ui->resTable);
        }
        catch(int error){
            if (error == 111)
                ShowErrorMsg(1);
            else
                if(error = 124)
                    ShowErrorMsg(2);
        }
    }
}

void MainWindow::on_subButton_clicked()//вычитание
{
    int rows1 = ui->matrixAtable->rowCount();
    int cols1 = ui->matrixAtable->columnCount();
    int rows2 = ui->matrixBtable->rowCount();
    int cols2 = ui->matrixBtable->columnCount();
    if ((rows1!=0) && (cols1!=0) && (rows2!=0) && (cols2!=0)){
        try{
            Matrix tmp1 = TableToMatrix(ui->matrixAtable);
            Matrix tmp2 = TableToMatrix(ui->matrixBtable);
            Matrix res = tmp1-tmp2;
            ui->resTable->setRowCount(rows1);
            ui->resTable->setColumnCount(cols1);
            MatrixToTable(res, ui->resTable);
        }
        catch(int error){
            if (error == 111)
                ShowErrorMsg(1);
            else
                if(error = 124)
                    ShowErrorMsg(2);
        }
    }

}

void MainWindow::on_multButton_clicked()//умножение
{
    int rows1 = ui->matrixAtable->rowCount();
    int cols1 = ui->matrixAtable->columnCount();
    int rows2 = ui->matrixBtable->rowCount();
    int cols2 = ui->matrixBtable->columnCount();
    if ((rows1!=0) && (cols1!=0) && (rows2!=0) && (cols2!=0)){
        try{
            Matrix tmp1 = TableToMatrix(ui->matrixAtable);
            Matrix tmp2 = TableToMatrix(ui->matrixBtable);
            Matrix res = tmp1*tmp2;
            ui->resTable->setRowCount(rows1);
            ui->resTable->setColumnCount(cols1);
            MatrixToTable(res, ui->resTable);
        }
        catch(int error){
            if (error == 111)
                ShowErrorMsg(1);
            else
                if(error = 125)
                    ShowErrorMsg(2);
        }
    }

}


