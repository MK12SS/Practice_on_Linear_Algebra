#include "Matrix.h"

using namespace std;

Matrix::Matrix(float line, float col):line(line), col(col)
{
	headP = new float*[line];
	for (int i = 0; i < line; i++)
	{
		headP[i] = new float[col];
	}
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < col; j++)
		{
			headP[i][j] = 0;
		}
	}
}
Matrix::Matrix(const Matrix & origin)
{
	headP = new float*[line];
	for (int i = 0; i < line; i++)
	{
		headP[i] = new float[col];
	}
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < col; j++)
		{
			headP[i][j] = origin.headP[i][j];
		}
	}
}

Matrix::~Matrix()
{
	for (int i = 0; i < line; i++)
	{
		delete[] headP[i];
	}
	delete[] headP;
	headP = nullptr;
}

float Matrix::determinant()
{
	try
	{
		if (!this->isSqure())
			throw exception();
		Matrix temp(this->diagonalize());
		float determinant = 1;

	}
	catch (const std::exception& msg)
	{

	}

}

Matrix Matrix::diagonalize()
{
	
}

Matrix Matrix::invert()
{
	try
	{
		if (!this->determinant()||this->col!=this->line)
			throw exception("");

	}
	catch (const std::exception& msg)
	{
		cout << msg.what() << endl;
	}
}

Matrix Matrix::transpose()
{
	Matrix temp(col, line);
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < col; j++)
		{
			temp.headP[j][i] = this->headP[i][j];
		}
	}
	return temp;
}

Matrix Matrix::getLine(int line)
{
	Matrix vec(1, col);
	for (int i = 0; i < col; i++)
	{
		vec.headP[0][i] = this->headP[line][i];
	}
	return vec;
}

Matrix Matrix::getCol(int col)
{
	Matrix vec(line, 1);
	for (int i = 0; i < line; i++)
	{
		vec.headP[i][0] = this->headP[i][col];
	}
	return vec;
}

bool Matrix::isSqure()
{
	if (col == line)return true;
	return false;
}

Matrix Matrix::lineMul(float coefficient, int line)
{
	
}

Matrix Matrix::colMul(float coefficient, int col)
{
	Matrix temp(*this);
	for (int i = 0; i < line; i++)
	{
		temp.headP[i][col] *= temp.headP[i][col] * coefficient;
	}
	return temp;
}

Matrix operator+(Matrix & a, Matrix b)
{
	try
	{
		if (a.line != b.line || a.col != b.col)
			throw exception("Sum error.");
		Matrix temp(a.line, a.col);
		for (int i = 0; i < a.line; i++)
		{
			for (int j = 0; j < a.col; j++)
			{
				temp.headP[i][j] = a.headP[i][j] + b.headP[i][j];
			}
		}
		return temp;
	}
	catch (const std::exception& msg)
	{
		cout << msg.what() << endl;
	}
}

Matrix operator*(Matrix & a, Matrix b)
{
	try
	{
		if (a.col != b.line)
			throw exception("Multiply error.");
		Matrix temp(a.line, b.col);
		for (int i = 0; i < a.line; i++)
		{
			for (int j = 0; j < b.col; j++)
			{
				float tempSum = 0;
				for (int k = 0; k < a.col; k++)
				{
					tempSum += a.headP[i][k] * b.headP[k][j];
				}
				temp.headP[i][j] = tempSum;
			}
		}
		return temp;
	}
	catch (const std::exception& msg)
	{
		cout << msg.what() << endl;
	}
}

Matrix operator*(Matrix & a, float & coefficient)
{
	Matrix temp(a.line, a.col);
	for (int i = 0; i < a.line; i++)
	{
		for (int j = 0; j < a.col; j++)
		{
			temp.headP[i][j] = a.headP[i][j] * coefficient;
		}
	}
	return temp;
}


