#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

class Matrix
{
private:
	int rows, cols;//колличесвто строк и столбцов
    vector <vector <long double> > matrix;


public:
	Matrix(int r, int c) { //создание матрицы с r строк и c столбцов
		try {
			if ((r <= 0) || (c <= 0))
				throw 123;
			else {
				rows = r;
				cols = c;
				matrix.reserve(r);
				vector <long double> tmp(c);
				for (int i = 0; i < r; i++)
					matrix.push_back(tmp);
			}
		}
        catch(int error){throw;}
    }


	~Matrix() { //удаление матрицы
		for (int i = 0; i < rows; i++)
			this->matrix[i].clear();
		this->matrix.clear();
    };

	//методы


    void SetIJ(long double val, int i, int j) {
		try {
			if ((i < 0) || (i >= matrix.size()) || (j < 0) || (j >= matrix[0].size()))
				throw 123;
			else {
				matrix[i][j] = val;
			}
		}
        catch(int error){throw;}
	}

	long double GetIJ(int i, int j) {
		try {
			if ((i < 0) || (i >= matrix.size()) || (j < 0) || (j >= matrix[0].size()))
				throw 123;
			else {
				return matrix[i][j];
			}
		}
        catch(int error){throw;}
    }

	void FillRand(int max = 100, int min = -100) { //заполнение случайными занчениями
		try {
			if (max < min)
				throw 123;
			else {
				srand(time(NULL));
				for (int i = 0; i < rows; i++)
					for (int j = 0; j < cols; j++)
						matrix[i][j] = rand() % (max - min + 1) + min;
			}
		}
        catch(int error){throw;}
	}

	void FillUnitMatrix() { //заполнение единичной матрицы
		try {
			if (this->rows != this->cols)
				throw 123;
			else {
				for (int i = 0; i < rows; i++)
					for (int j = 0; j < cols; j++)
						if (i == j)
							matrix[i][j] = 1;
						else
							matrix[i][j] = 0;
			}
		}
        catch(int error){throw;}
	}


	Matrix Minor(int r, int c) { //вычисление минора 
		try {
            if (this->rows != this->cols)
                throw 128;
            if ((this->rows == 1) && (this->cols == 1))
                throw 129;
			else {
				if ((r >= this->rows) || (c >= this->cols))
					throw 234;
				else {
					Matrix tmp(this->rows, this->cols);
					tmp.matrix = this->matrix;
					for (int i = 0; i<tmp.rows; i++)
						tmp.matrix[i].erase(tmp.matrix[i].begin() + c);
					tmp.matrix.erase(tmp.matrix.begin() + r);
					tmp.rows--;
					tmp.cols--;
					return tmp;
				}
			}
		}
        catch(int error){throw;}
	}



	float Det() {//определитель
		try {
			if (this->rows != this->cols)
                throw 123;
			else {
				long double det = 0;
				if (this->rows == 1)
					det = this->matrix[0][0];
				else {
					if (this->rows == 2)
						det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
					else {
						if (this->rows == 3)
							det = (matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0] + matrix[0][2] * matrix[1][0] * matrix[2][1]) -
							(matrix[0][2] * matrix[1][1] * matrix[2][0] + matrix[1][0] * matrix[0][1] * matrix[2][2] + matrix[0][0] * matrix[2][1] * matrix[1][2]);
						else {
							for (int i = 0; i < this->matrix[0].size(); i++) {
								if (i % 2 == 0)
									det = det + matrix[0][i] * this->Minor(0, i).Det();
								else
									det = det - matrix[0][i] * this->Minor(0, i).Det();
							}
						}
					}
				}
				return det;
			}
		}
        catch(int error){throw;}
	}


	Matrix Trans() {//транспонирование матрицы
		Matrix tmp(this->cols, this->rows);
		for (int i = 0; i < tmp.rows; i++)
			for (int j = 0; j < tmp.cols; j++)
				tmp.matrix[i][j] = this->matrix[j][i];
		return tmp;
	}



	Matrix MultBy(long double n) {//умножение на число
		Matrix tmp(this->rows, this->cols);
		for (int i = 0; i < tmp.rows; i++)
			for (int j = 0; j < tmp.cols; j++)
				tmp.matrix[i][j] = n * this->matrix[i][j];
		return tmp;
	}


	Matrix Reverse() {//обратная матрица
		Matrix tmp(this->rows, this->cols);
		try {
			long double det = this->Det();
			if (det == 0)
                throw 124;
			else {
                if ((this->rows == 1) && (this->cols == 1)){
                    tmp.SetIJ(this->GetIJ(0,0), 0, 0);
                }
                else{
                    for (int i = 0; i<this->rows; i++)
                        for (int j = 0; j < this->cols; j++) {
                            if ((i + j) % 2 == 0)
                                tmp.matrix[i][j] = (this->Minor(i, j)).Det();
                            else
                                tmp.matrix[i][j] = (-1)*(this->Minor(i, j)).Det();
                        }
                }
				tmp = tmp.Trans();
				tmp = tmp.MultBy(1 / det);
				return tmp;
			}
		}
        catch(int error){throw;}
	}



	Matrix operator+(const Matrix &right) {//сложение, перегрузка оператора +
		try {
			if ((this->rows != right.rows) || (this->cols != right.cols))
                throw 124;
			else {
				Matrix tmp(rows, cols);
				for (int i = 0; i < tmp.rows; i++)
					for (int j = 0; j < tmp.cols; j++)
						tmp.matrix[i][j] = this->matrix[i][j] + right.matrix[i][j];
				return tmp;
			}
		}
        catch(int error){throw;}
	}

	Matrix operator-(const Matrix &right) {//вычитание, перегрузка оператора -
		try {
			if ((this->rows != right.rows) || (this->cols != right.cols))
                throw 124;
			else {
				Matrix tmp(rows, cols);
				for (int i = 0; i < tmp.rows; i++)
					for (int j = 0; j < tmp.cols; j++)
						tmp.matrix[i][j] = this->matrix[i][j] - right.matrix[i][j];
				return tmp;
			}
		}
        catch(int error){throw;}
	}


	Matrix operator*(const Matrix &right) {
		try {
			if (this->cols != right.rows)
                throw 125;
			else {
				Matrix tmp(this->rows, right.cols);
				for (int i = 0; i<tmp.rows; i++)
					for (int j = 0; j<tmp.cols; j++) {
						for (int k = 0; k < right.rows; k++)
							tmp.matrix[i][j] += this->matrix[i][k] * right.matrix[k][j];
					}
				return tmp;
			}
		}
        catch(int error){throw;}
	}


};
