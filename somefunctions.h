#ifndef SOMEFUNCTIONS_H
#define SOMEFUNCTIONS_H
#include <QErrorMessage>
#include "Matrix.h"
#include <QTableWidgetItem>

void ShowErrorMsg(int msg){//показывает сообщение о неверных входных данных
    QErrorMessage errorMessage;
    switch (msg){
        case 1:errorMessage.showMessage("Incorrect data!");
        break;
        case 2:errorMessage.showMessage("Unacceptable size!");
        break;
        case 3:errorMessage.showMessage("Impossible operation!");
        break;
    }
    errorMessage.exec();
}

Matrix TableToMatrix(QTableWidget *table){
    int rows = table->rowCount();
    int cols = table->columnCount();
    Matrix tmp(rows, cols);
    try{
        for (int i =0; i<rows;i++){
            for (int j=0;j<cols;j++){
                bool ok;//переменная отвечающая за успешное конвертирование строки в число
                long double t = (table->item(i, j)->text()).toDouble(&ok);//извлекаем содержимое ячейки [i][j]
                if (!ok)//если конвертация не удалась, бросить исключение
                    throw 111;
                try{
                    tmp.SetIJ(t, i,j);//записываем значение в таблицу
                }
                catch (int error){//обработка исключения, к-е при данном интерефейсе пользователя возникнуть не может
                    if (error == 123)
                        continue;
                }
            }
        }
        return tmp;
    }
    catch (int error){
        if (error == 111)
            throw;
    }
}


void MatrixToTable(Matrix &matrix, QTableWidget *table){//помещает в таблицу содержимое матрицы
    for (int i = 0; i<table->rowCount(); i++){
        for (int j = 0; j<table->columnCount(); j++){
            QString str = QString::number(matrix.GetIJ(i,j), 'f', 6);
            table->setItem(i, j, new QTableWidgetItem(str));
        }
    }
}

#endif // SOMEFUNCTIONS_H


