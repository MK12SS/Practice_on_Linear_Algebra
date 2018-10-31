#pragma once

#include<iostream>
#include<string>

class Matrix
{
public:
	Matrix(float line, float col);
	Matrix(const Matrix &origin);
	~Matrix();
	float determinant();
	Matrix diagonalize();
	Matrix lineMinus(int line_1, int line_2);
	Matrix colMinus(int col_1, int col_2);

	Matrix invert();
	Matrix transpose();
	Matrix cramerRule(Matrix &rightmost);
	Matrix distractLU();
	bool isSpan();

	float getElement(int i, int j) { return this->headP[i][j]; }
	Matrix getLine(int line_1);
	Matrix getCol(int col_1);
	Matrix lineSwap(int line_1, int line_2);
	Matrix colSwap(int col_1,int col_2);
	bool isSqure();
	Matrix lineMul(float coefficient, int line_1);
	Matrix colMul(float coefficient, int col_1);

	void operator=(const Matrix &a);
	friend Matrix operator+(Matrix &a, Matrix &b);
	friend Matrix operator*(Matrix &a, Matrix &b);
	friend Matrix operator*(Matrix &a, float &coefficient);
	friend std::ostream &operator<<(std::ostream &outp,const Matrix &target)
	{
		for (int i = 0; i < target.line; i++)
		{
			for (int j = 0; j < target.col; j++)
			{
				outp << target.headP[i][j] << " ";
			}
			outp << std::endl;
		}
		return outp;
	}
	friend std::istream &operator>>(std::istream &inp,const Matrix &target)
	{
		for (int i = 0; i < target.line; i++)
		{
			for (int j = 0; j < target.col; j++)
			{
				inp >> target.headP[i][j];
			}
		}
		return inp;
	}

private:
	float** headP;
	int line;
	int col;
};