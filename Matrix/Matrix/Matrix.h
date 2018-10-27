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
	Matrix invert();
	Matrix transpose();
	Matrix getLine(int line);
	Matrix getCol(int col);
	bool isSqure();
	Matrix lineMul(float coefficient, int line);
	Matrix colMul(float coefficient, int col);

	friend Matrix operator+(Matrix &a, Matrix b);
	friend Matrix operator*(Matrix &a, Matrix b);
	friend Matrix operator*(Matrix &a, float &coefficient);
	friend std::ostream &operator<<(std::ostream &outp, Matrix &target)
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
	friend std::istream &operator>>(std::istream &inp, Matrix &target)
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

