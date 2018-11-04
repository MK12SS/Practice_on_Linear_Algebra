#include "Matrix.h"

using namespace std;

Matrix::Matrix()
{
	col = line = 0;
	headP = NULL;
}

Matrix::Matrix(float line, float col):line(line), col(col)
{
	if (!line || !col)
	{
		this->line = this->col = 0;
		headP = NULL;
	}
	else
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
				headP[i][j] = 0.0;
			}
		}
	}
}
Matrix::Matrix(const Matrix & origin)
{
	line = origin.line;
	col = origin.col;
	if (origin.headP)
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
	else
	{
		headP = NULL;
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
		if (!this->isSqure()||!headP)
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
		if (this->col < this->line||!headP)
			throw exception();
		Matrix temp(*this);
		for (int i = 0; i < temp.line; i++)
		{
			if (!temp.headP[i][i])
			{
				int found = 0;
				for (int j = i + 1; j < line; j++)
				{
					if (temp.headP[j][i])
					{
						temp = temp.lineSwap(i, j);
						found = 1;
						break;
					}
				}
				if (!found)
				{
					continue;
				}
			}
			for (int j = 0; j < temp.line - 1 - i; j++)
			{
				if (!temp.headP[i + j + 1][i])continue;
				float coeffitient = temp.headP[i + j + 1][i] / temp.headP[i][i];
				float originCoe = 1 / coeffitient;
				temp = 
					temp.lineMul(coeffitient, i)
					.lineReduction(i + j + 1, i)
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

Matrix Matrix::lineReduction(int line_1, int line_2)
{
	try
	{
		if (line_1 < 0 || line_1 >= line || line_2 < 0 || line_2 >= line)
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

Matrix Matrix::colReduction(int col_1, int col_2)
{
	try
	{
		if (col_1 < 0 || col_1 >= col || col_2 < 0 || col_2 >= col)
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

void Matrix::addCol(Matrix & a)
{
	try
	{
		if (this->line != a.line || !this->line)
			throw exception();
		float **head = new float*[this->line];
		for (int i = 0; i < this->line; i++)
		{
			head[i] = new float[this->col + a.col];
		}
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < this->col; j++)
			{
				head[i][j] = this->headP[i][j];
			}
			for (int j = 0; j < a.col; j++)
			{
				head[i][j + this->col] = a.headP[i][j];
			}
		}
		delete[] this->headP;
		this->headP = head;
		this->col += a.col;
	}
	catch (const std::exception& msg)
	{
		cout << msg.what() << endl;
	}
}

void Matrix::addLine(Matrix & a)
{
	try
	{
		if (this->col != a.col || !this->col)
			throw exception();
		float **head = new float*[this->line + a.line];
		for (int i = 0; i < this->line + a.line; i++)
		{
			head[i] = new float[this->col];
		}
		for (int i = 0; i < this->line; i++)
		{
			for (int j = 0; j < this->col; j++)
			{
				head[i][j] = this->headP[i][j];
			}
		}
		for (int i = 0; i < a.line; i++)
		{	
			for (int j = 0; j < a.col; j++)
			{
				head[i + this->line][j] = a.headP[i][j];
			}
		}
		delete[] this->headP;
		this->headP = head;
		this->line += a.line;
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
		int det = this->determinant();
		if (!det||!this->isSqure())
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
	try
	{
		if (!headP)
			throw exception();
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
	catch (const std::exception& msg)
	{
		cout << msg.what() << endl;
	}
}

Matrix Matrix::cramerRule(Matrix & rightmost)//----------------
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

Matrix Matrix::distractLU()//--------------------
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

Matrix Matrix::solve()//-----------------
{
	try
	{
		if (this->col <= this->line||!headP)
			throw exception();
		Matrix temp = this->diagonalize();
		



	}
	catch (const std::exception& msg)
	{
		cout << msg.what() << endl;
	}
}

Matrix Matrix::getLine(int line_1)
{
	try
	{
		if (line_1 < 0 || line_1 >= line || !headP);
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
		if (col_1 < 0 || col_1 >= col || !headP)
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
		if (line_1<0 || line_1>line || line_2<0 || line_2>line || !headP)
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
		if (col_1 < 0 || col_1 >= col || col_2 < 0 || col_2 >= col || !headP)
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
	if (!headP)return false;
	if (col == line)return true;
	return false;
}

Matrix Matrix::lineMul(float coefficient, int line_1)
{
	try
	{
		if (line_1<0 || line_1>line || !headP)
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
		if (col_1 < 0 || col_1 >= col || !headP)
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
	if (!this->headP)
	{
		for (int i = 0; i < this->line; i++)
		{
			delete[] this->headP[i];
		}
		delete[] this->headP;
	}
	this->col = a.col;
	this->line = a.line;
	if (!a.headP)
	{
		this->headP = new float*[this->line];
		for (int i = 0; i < line; i++)
		{
			headP[i] = new float[col];
			for (int j = 0; j < col; j++)
			{
				headP[i][j] = a.headP[i][j];
			}
		}
	}
}

bool Matrix::operator==(const Matrix & a)
{
	if (this->line != a.line || this->col != a.col)return false;
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (this->headP[i][j] != a.headP[i][j])return false;
		}
	}
	return true;
}

bool Matrix::operator!=(const Matrix & a)
{
	if (this->operator==(a))return false;
	return true;
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
	Matrix temp(a);
	for (int i = 0; i < temp.line; i++)
	{
		temp = temp.lineMul(coefficient, i);
	}
	return temp;
}

Matrix unitMat(int n)
{
	Matrix temp(n, n);
	for (int i = 0; i < n; i++)
	{
		temp.headP[i][i] = 1;
	}
	return temp;
}