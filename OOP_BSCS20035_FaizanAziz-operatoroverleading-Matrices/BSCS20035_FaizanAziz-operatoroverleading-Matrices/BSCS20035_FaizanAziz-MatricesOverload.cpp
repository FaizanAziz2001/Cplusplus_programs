#pragma once
#include<string>
#include <fstream>
#include<iostream>
using namespace std;
class Matrix
{
	string name;
	int Rows;
	int Cols;
	int** Vs;
	void Deepcopy(const Matrix& M);
	void AllocateMatrix();
	void DeAllocateMatrix();
	static const Matrix Unit(int Rows, int Cols);

public:
	Matrix();
	Matrix(int R, int C);
	Matrix(ifstream& fin);
	Matrix(const Matrix& M);
	void init(ifstream& fin);
	const Matrix& operator=(const Matrix& M);
	const Matrix operator+(const Matrix& M) const;
	const Matrix operator-(const Matrix& M) const;
	const Matrix operator*(const Matrix& M) const;
	bool operator==(const Matrix& M) const;
	const Matrix operator*(int);
	const Matrix operator-();
	const Matrix operator~();
	const Matrix operator^(int);
	const Matrix operator>(int);
	const Matrix operator-(int num);
	const Matrix& operator+=(const Matrix& M);
	const Matrix& operator-=(const Matrix& M);
	const Matrix& operator*=(const Matrix& M);
	Matrix& operator++();
	const Matrix& operator++(int);
	Matrix& operator--();
	const Matrix& operator--(int);

	friend ostream& operator<<(ostream&, const Matrix& M);

	ostream& operator<<(ostream&); //M1<<cout
	~Matrix();

};







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
	if (this->Cols == M.Rows)
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
			Vs[ri][ci] = Vs[ri][ci] * -1;
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
			R.Vs[ci][ri] = this->Vs[ri][ci];
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


/*
2
3 4
1 2 3 4
5 6 7 8
9 10 11 12

3 4
10  3    2    1
2   2    11   7
1   6    5    9

*/




#include "Matrix.h"
#include <iostream>
using namespace std;

void init_Matrix(Matrix*& M, int& NOM)
{
	ifstream fin("Input.txt");
	fin >> NOM;
	M = new Matrix[NOM];
	for (int i = 0; i < NOM; i++)
	{
		M[i].init(fin);
	}
}
void Print_All(Matrix* M, int NOM)
{
	for (int i = 0; i < NOM; i++)
	{
		cout << M[i] << endl;
	}
}
void menu()
{
	cout << "1. + for Add" << endl
		<< "2. - for Sub" << endl
		<< "3. * for Multi" << endl
		<< "4. pre increment" << endl
		<< "5. post increment" << endl
		<< "6. += for AddAccumulate" << endl
		<< "7. -= for SubAccumulate" << endl
		<< "8. *= for MultiAccumulate" << endl
		<< "9. for Scaler Subtraction" << endl
		<< "10. for Scalar Multiplication" << endl
		<< "11. == for equal matrix" << endl
		<< "12. - for Mimic" << endl
		<< "13. ~ for Transpose" << endl
		<< "14. ^ for Clockwise rotation" << endl
		<< "15. > for Anti-Clockwise rotation" << endl;
}
void Matrices(Matrix* M, int NOM)
{

	Print_All(M, NOM);

	char opr{}, dummy{}, cont;
	int rsi{}, loi{}, roi{};

	do
	{
		cout << "Example Format: F1 = F2 + F3" << endl;
		cout << "Example Format: F1 = F2 - F3" << endl;
		cout << "Example Format: F1 = F2 * F3" << endl;
		cout << "Input: ";
		cin >> dummy >> rsi >> dummy >> dummy >> loi >> opr >> dummy >> roi;
		rsi--; loi--; roi--;

		switch (opr)
		{
		case '+':
			M[rsi] = M[loi] + (M[roi]);
			break;

		case '-':
			M[rsi] = M[loi] - (M[roi]);
			break;

		case '*':
			M[rsi] = M[loi] * (M[roi]);
			break;
		}
		Print_All(M, NOM);

		cout << endl << " Do You Want To Continue?(Y for yes): ";
		cin >> cont;
		system("cls");
	} while (cont == 'Y' || cont == 'y');
	system("pause");

}
void AccumulateMatrices(Matrix* M, int NOM)
{

	Print_All(M, NOM);

	char opr{}, dummy{}, cont;
	int loi{}, roi{};

	do
	{

		cout << "Example Format: F1 + F2" << endl;
		cout << "Example Format: F1 - F2" << endl;
		cout << "Example Format: F1 * F2" << endl;
		cout << "Example Format: F1 = F2" << endl;
		cout << "Input: ";
		cin >> dummy >> loi >> opr >> dummy >> roi;
		loi--; roi--;

		switch (opr)
		{
		case '+':
			M[loi] += (M[roi]);
			break;

		case '-':
			M[loi] -= (M[roi]);
			break;

		case '*':
			M[loi] *= (M[roi]);
			break;
		case '=':
			if (M[loi] == M[roi])
				cout << "Matrix are equal" << endl;
			else;
			cout << "Matrix are not equal" << endl;
			break;
		}
		Print_All(M, NOM);

		cout << endl << " Do You Want To Continue?(Y): ";
		cin >> cont;
		system("cls");
	} while (cont == 'Y' || cont == 'y');
	system("pause");

}
void SingleMatrix(Matrix* M, int NOM)
{
	Print_All(M, NOM);

	int ind;
	char d, op, cont;

	do
	{

		cout << "Format: -M1 (Mimic)" << endl;
		cout << "Format: ~M1 (transpose)" << endl;
		cout << "Format: pM1 (pre increment)" << endl;
		cout << "Format: oM1 (post increment) " << endl;
		cout << "Format: cM1 (clockwise rotation) " << endl;
		cout << "Format: aM1 (anticlockwise rotation) " << endl;
		cout << "Input: ";
		cin >> op >> d >> ind;
		ind--;
		int rotation;

		switch (op)
		{
		case '-':
			M[ind] = -M[ind];
			break;

		case '~':
			M[ind] = ~M[ind];
			break;
		case'p':
			M[ind]++;
			break;
		case 'o':
			++M[ind];
			break;
		case 'c':
			cout << "Enter clockwise rotation degree: ";
			cin >> rotation;
			M[ind] = (M[ind] ^ rotation / 90);
			break;
		case 'a':
			cout << "Enter anti clockwise rotation degree: ";
			cin >> rotation;
			M[ind] = (M[ind] > rotation / 90);
			break;
		}
		Print_All(M, NOM);

		cout << endl << " Do You Want To Continue?(Y for yes): ";
		cin >> cont;
		system("cls");

	} while (cont == 'Y' || cont == 'y');
	system("pause");
}
void ScalarMatrix(Matrix* M, int NOM)
{
	Print_All(M, NOM);

	char opr{}, dummy{}, cont;
	int rsi, ind, scalar;

	do
	{
		cout << "Example Format: F1 = F2 - 5" << endl;
		cout << "Example Format: F1 = F2 * 5" << endl;
		cout << "Input: ";
		cin >> dummy >> rsi >> dummy >> dummy >> ind >> opr >> scalar;
		ind--;

		switch (opr)
		{
		case '-':
			M[rsi] = M[ind] - scalar;
			break;

		case '*':
			M[rsi] = M[ind] * scalar;
			break;
		}
		Print_All(M, NOM);

		cout << endl << " Do You Want To Continue?(Y for yes) ";
		cin >> cont;

		system("cls");

	} while (cont == 'Y' || cont == 'y');
	system("pause");

}

int main()
{
	int input, cont;
	Matrix* M{};
	int NOM = 0;
	init_Matrix(M, NOM);

	do
	{
		system("cls");
		cout << "Enter task number: " << endl
			<< "1. Multiple Matrix Operations" << endl
			<< "2. Single Matrix Operations" << endl
			<< "3. Accumulate Matrix Operations" << endl
			<< "4. Scaler Matrix Operations" << endl;
		cin >> input;

		switch (input)
		{
		case 1:
			Matrices(M, NOM);
			break;

		case 2:
			SingleMatrix(M, NOM);
			break;
		case 3:
			AccumulateMatrices(M, NOM);
			break;
		case 4:
			ScalarMatrix(M, NOM);
			break;
		}

		cout << "Do you want to continue(Y for yes)";
		cin >> cont;

	} while (cont == 'Y' || cont == 'y');
}
