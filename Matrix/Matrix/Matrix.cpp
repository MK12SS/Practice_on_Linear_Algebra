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
	line = origin.line;
	col = origin.col;
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
			throw exception("");
		Matrix temp(this->diagonalize());
		float determinant = 1;
		for (int i = 0; i < line; i++)
		{
			determinant *= this->headP[i][i];
		}
		return determinant;
	}
	catch (const std::exception& msg)
	{
		cout << msg.what() << endl;
	}

}

Matrix Matrix::diagonalize()
{
	try
	{
		if (this->col < this->line)throw exception();
		Matrix temp(*this);
		for (int i = 0; i < temp.line; i++)
		{
			for (int j = 0; j < temp.line - 1 - i; j++)
			{
				float coeffitient = temp.headP[i + j + 1][i] / temp.headP[i][i];
				float originCoe = 1 / coeffitient;
				temp = 
					temp.lineMul(coeffitient, i)
					.lineMinus(i + j + 1, i)
					.lineMul(originCoe, i);
				cout << temp << endl;
			}
		}
		return temp;
	}
	catch (const std::exception& msg)
	{
		cout << msg.what() << endl;
	}
}

Matrix Matrix::lineMinus(int line_1, int line_2)
{
	try
	{
		if (line_1<0 || line_1>=line || line_2<0 || line_2>=line)
			throw exception();
		Matrix temp(*this);
		for (int i = 0; i < col; i++)
		{
			temp.headP[line_1][i] -= temp.headP[line_2][i];
		}
		return temp;
	}
	catch (const std::exception& msg)
	{
		cout << msg.what() << endl;
	}
}

Matrix Matrix::colMinus(int col_1, int col_2)
{
	try
	{
		if (col_1<0 || col_1>=col || col_2<0 || col_2>=col)
			throw exception();
		Matrix temp(*this);
		for (int i = 0; i < line; i++)
		{
			temp.headP[i][col_1] -= temp.headP[i][col_1];
		}
		return temp;
	}
	catch (const std::exception& msg)
	{
		cout << msg.what() << endl;
	}
}

Matrix Matrix::invert()//---------------------------
{
	try
	{
		if (!this->determinant()||!this->isSqure())
			throw exception("");


		return Matrix(*this);
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

Matrix Matrix::cramerRule(Matrix & rightmost)
{
	try
	{
		if (!this->isSqure() || rightmost.col != this->col)
			throw exception();
		
	}
	catch (const std::exception& msg)
	{
		cout << msg.what() << endl;
	}
}

Matrix Matrix::distractLU()
{
	try
	{
		if (!this->isSqure())
			throw exception();

	}
	catch (const std::exception& msg)
	{
		cout << msg.what() << endl;
	}
}

bool Matrix::isSpan()
{
	return false;
}

Matrix Matrix::getLine(int line_1)
{
	try
	{
		if (line_1<0 || line_1>line)
			throw exception();
		Matrix vec(1, col);
		for (int i = 0; i < col; i++)
		{
			vec.headP[0][i] = this->headP[line_1][i];
		}
		return vec;
	}
	catch (const std::exception& msg)
	{
		cout << msg.what() << endl;
	}
}

Matrix Matrix::getCol(int col_1)
{
	try
	{
		if (col_1<0 || col_1 >= col)
			throw exception();
		Matrix vec(line, 1);
		for (int i = 0; i < line; i++)
		{
			vec.headP[i][0] = this->headP[i][col_1];
		}
		return vec;
	}
	catch (const std::exception& msg)
	{
		cout << msg.what() << endl;
	}
}

Matrix Matrix::lineSwap(int line_1, int line_2)
{
	try
	{
		if (line_1<0 || line_1>line || line_2<0 || line_2>line)
			throw exception();
		Matrix result(*this);
		Matrix temp(1, this->col);
		for (int i = 0; i < this->col; i++)
		{
			temp.headP[0][i] = result.headP[line_1][i];
			temp.headP[line_1][i] = result.headP[line_2][i];
			result.headP[line_2][i] = temp.headP[0][i];
		}
		return result;
	}
	catch (const std::exception& msg)
	{
		cout << msg.what() << endl;
	}
}

Matrix Matrix::colSwap(int col_1, int col_2)
{
	try
	{
		if (col_1<0 || col_1>=col || col_2<0 || col_2>=col)
			throw exception();
		Matrix result(*this);
		Matrix temp(this->line, 1);
		for (int i = 0; i < this->line; i++)
		{
			temp.headP[i][0] = result.headP[i][col_1];
			result.headP[i][col_1] = result.headP[i][col_2];
			result.headP[i][col_2] = temp.headP[i][0];
		}
		return result;
	}
	catch (const std::exception& msg)
	{
		cout << msg.what() << endl;
	}
}

bool Matrix::isSqure()
{
	if (col == line)return true;
	return false;
}

Matrix Matrix::lineMul(float coefficient, int line_1)
{
	try
	{
		if (line_1<0 || line_1>line)
			throw exception();
		Matrix temp(*this);
		for (int i = 0; i < this->col; i++)
		{
			temp.headP[line_1][i] *= coefficient;
		}
		return temp;
	}
	catch (const std::exception& msg)
	{
		cout << msg.what() << endl;
	}
}

Matrix Matrix::colMul(float coefficient, int col_1)
{
	try
	{
		if (col_1<0 || col_1 >= col)
			throw exception();
		Matrix temp(*this);
		for (int i = 0; i < line; i++)
		{
			temp.headP[i][col_1] *= coefficient;
		}
		return temp;
	}
	catch (const std::exception& msg)
	{
		cout << msg.what() << endl;
	}
}

void Matrix::operator=(const Matrix & a)
{
	try
	{
		if (a.col != this->col || a.line != this->line)throw exception();
		for (int i = 0; i < this->line; i++)
		{
			for (int j = 0; j < this->col; j++)
			{
				this->headP[i][j] = a.headP[i][j];
			}
		}
	}
	catch (const std::exception& msg)
	{
		cout << msg.what() << endl;
	}
}

Matrix operator+(Matrix & a, Matrix &b)
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

Matrix operator*(Matrix & a, Matrix &b)
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
