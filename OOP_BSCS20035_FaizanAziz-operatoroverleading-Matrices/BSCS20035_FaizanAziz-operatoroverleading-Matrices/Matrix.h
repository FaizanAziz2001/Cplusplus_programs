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
	const Matrix operator*(int );
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

