#include "Matrix.h"

Matrix::Matrix()
{
	Vs = nullptr;
	Rows = Cols = 0;
}
void Matrix::init(ifstream& fin)
{
	fin >> Rows >> Cols;
	AllocateMatrix();
	for (int ri = 0; ri < Rows; ri++)
	{
		for (int ci = 0; ci < Cols; ci++)
		{
			fin >> Vs[ri][ci];
		}
	}
}
void Matrix::Deepcopy(const Matrix& M)
{
	this->Rows = M.Rows;
	this->Cols = M.Cols;
	this->AllocateMatrix();
	for (int ri = 0; ri < Rows; ri++)
	{
		for (int ci = 0; ci < Cols; ci++)
		{
			Vs[ri][ci] = M.Vs[ri][ci];
		}
	}
}
void Matrix::AllocateMatrix()
{
	Vs = new int* [Rows];
	for (int ri = 0; ri < Rows; ri++)
	{
		Vs[ri] = new int[Cols] {};
	}
}
const Matrix Matrix::Unit(int Rows, int Cols)
{
	Matrix R(Rows, Cols);
	for (int ri = 0; ri < Rows; ri++)
	{
		for (int ci = 0; ci < Cols; ci++)
		{
			R.Vs[ri][ci] = 1;
		}
	}
	return R;
}
void Matrix::DeAllocateMatrix()
{
	if (Vs != nullptr)
	{
		for (int ri = 0; ri < Rows; ri++)
		{
			delete[] Vs[ri];
		}
		delete[] Vs;
	}
	Rows = 0;
	Cols = 0;
}
Matrix::Matrix(int R, int C)
{
	Rows = R;
	Cols = C;
	Vs = nullptr;


}
Matrix::Matrix(ifstream& fin)
{
	init(fin);
}
Matrix::Matrix(const Matrix& M)
{
	Deepcopy(M);
}
const Matrix& Matrix::operator=(const Matrix& M)
{
	DeAllocateMatrix();
	Deepcopy(M);
	return *this;
}
const Matrix Matrix::operator+(const Matrix& M) const
{
	Matrix R;
	if (this->Rows == M.Rows && this->Cols == M.Cols)
	{
		R.Rows = Rows;
		R.Cols = Cols;
		R.AllocateMatrix();
		for (int ri = 0; ri < Rows; ri++)
		{
			for (int ci = 0; ci < Cols; ci++)
			{
				R.Vs[ri][ci] = Vs[ri][ci] + M.Vs[ri][ci];
			}
		}
	}
	return R;

}
const Matrix Matrix::operator-(const Matrix& M) const
{
	Matrix R;
	if (this->Rows == M.Rows && this->Cols == M.Cols)
	{
		R.Rows = Rows;
		R.Cols = Cols;
		R.AllocateMatrix();
		for (int ri = 0; ri < Rows; ri++)
		{
			for (int ci = 0; ci < Cols; ci++)
			{
				R.Vs[ri][ci] = Vs[ri][ci] - M.Vs[ri][ci];
			}
		}
	}
	return R;

}
const Matrix Matrix::operator*(const Matrix& M) const
{
	Matrix R;
	int sum = 0;
	if (this->Cols== M.Rows)
	{
		R.Rows = this->Rows;
		R.Cols = M.Cols;
		R.AllocateMatrix();
		for (int ri = 0; ri < this->Rows; ri++)
		{
			for (int r = 0; r < M.Cols; r++)
			{
				sum = 0;
				for (int ci = 0; ci < M.Rows; ci++)
				{
					sum = sum + (this->Vs[ri][ci] * M.Vs[ci][r]);
				}
				R.Vs[ri][r] = sum;
			}

		}
	}
	
	
	return R;

}
const Matrix Matrix::operator*(int num)
{
	for (int ri = 0; ri < Rows; ri++)
	{
		for (int ci = 0; ci < Cols; ci++)
		{
			Vs[ri][ci] = Vs[ri][ci] * num;
		}
	}

	return *this;

}
const Matrix Matrix::operator-()
{
	for (int ri = 0; ri < Rows; ri++)
	{
		for (int ci = 0; ci < Cols; ci++)
		{
			Vs[ri][ci] = Vs[ri][ci] *-1;
		}
	}
	return *this;
}

const Matrix Matrix::operator~()
{
	Matrix R;
	R.Rows = this->Cols;
	R.Cols = this->Rows;
	R.AllocateMatrix();
	for (int ci = 0; ci < R.Rows; ci++)
	{
		for (int ri = 0; ri < R.Cols; ri++)
		{
			R.Vs[ci][ri]=this->Vs[ri][ci];
		}
	}
	this->DeAllocateMatrix();
	this->Deepcopy(R);
	return *this;
}
const Matrix Matrix::operator^(int angle)
{
	Matrix R;
	for (int i = 0; i < angle; i++)
	{
		R.Rows = Cols;
		R.Cols = Rows;
		R.AllocateMatrix();
		for (int ri = 0; ri < R.Rows; ri++)
		{

			for (int ci = 0; ci < R.Cols; ci++)
			{
				R.Vs[ri][R.Cols - (ci + 1)] = Vs[ci][ri];
			}
		}
		this->DeAllocateMatrix();
		this->Deepcopy(R);
	}
	return *this;
}
const Matrix Matrix::operator>(int angle)
{
	Matrix R;
	for (int i = 0; i < angle; i++)
	{
		R.Rows = Cols;
		R.Cols = Rows;
		R.AllocateMatrix();
		for (int ri = 0; ri < R.Rows; ri++)
		{
			for (int ci = 0; ci < R.Cols; ci++)
			{
				R.Vs[R.Rows - (ri + 1)][ci] = this->Vs[ci][ri];
			}
		}
		this->DeAllocateMatrix();
		this->Deepcopy(R);
	}
	return *this;
}
const Matrix Matrix::operator-(int num)
{
	for (int ri = 0; ri < Rows; ri++)
	{
		for (int ci = 0; ci < Cols; ci++)
		{
			Vs[ri][ci] = Vs[ri][ci] - num;
		}
	}

	return *this;

}
const Matrix& Matrix::operator+=(const Matrix& M)
{
	(*this) = *this + M;
	return *this;
}
const Matrix& Matrix::operator-=(const Matrix& M)
{
	(*this) = *this - M;
	return *this;
}
const Matrix& Matrix::operator*=(const Matrix& M)
{
	(*this) = *this * M;
	return *this;
}
Matrix& Matrix::operator++()
{
	*this = *this + Matrix::Unit(this->Rows, this->Cols);
	return *this;
}
const Matrix& Matrix::operator++(int r)
{
	Matrix Temp = *this;
	*this = *this + Matrix::Unit(this->Rows, this->Cols);
	return Temp;
}
Matrix& Matrix::operator--()
{
	*this = *this - Matrix::Unit(this->Rows, this->Cols);
	return *this;
}
const Matrix& Matrix::operator--(int r)
{
	Matrix Temp = *this;
	*this = *this - Matrix::Unit(this->Rows, this->Cols);
	return Temp;
}
bool Matrix::operator==(const Matrix& M) const
{
	if ((this->Rows != M.Cols) && (this->Cols != M.Cols))
		return false;
	for (int ri = 0; ri < Rows; ri++)
	{
		for (int ci = 0; ci < Cols; ci++)
		{
			if (Vs[ri][ci] != M.Vs[ri][ci])
				return false;
		}
	}
	return true;
}


ostream& operator<<(ostream& Console, const Matrix& M)
{
	cout << "Matrix [" << M.Rows << "][" << M.Cols << "]" << endl;
	for (int ri = 0; ri < M.Rows; ri++)
	{
		for (int ci = 0; ci < M.Cols; ci++)
		{
			cout << M.Vs[ri][ci] << "\t";
		}
		cout << endl;
	}
	return Console;
}
ostream& Matrix::operator<<(ostream&)
{
	cout << "Matrix [" << Rows << "][" << Cols << "]" << endl;
	for (int ri = 0; ri < Rows; ri++)
	{
		for (int ci = 0; ci < Cols; ci++)
		{
			cout << Vs[ri][ci] << "\t";
		}
		cout << endl;
	}

	return cout;
}
Matrix::~Matrix()
{
	DeAllocateMatrix();
}