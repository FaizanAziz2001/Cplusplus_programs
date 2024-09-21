#include "Fraction.h"
#include <iostream>
using namespace std;

int Fraction::GCD(int A, int B)
{
	int max;
	if (A > B)
		max = A;
	else
		max = B;
	if (max > 0)
		for (int i = max; i >= 1; i--)
		{
			if (A % i == 0 && B % i == 0)
			{
				return i;
			}
		}
	else
	{
		for (int i = max; i < 0; i++)
		{
			if (A % i == 0 && B % i == 0)
			{
				return i;
			}
		}
	}
	return 1;
}

int Fraction::LCM(int A, int B)
{
	int LCM = 0;
	LCM = (A * B) / GCD(A, B);
	return LCM;
}

//void Fraction::print()
//{
//	cout << "(" << this->Num << ", " << this->Den << ")";
//}

int Fraction::getnum()
{
	return Num;
}

int Fraction::getden()
{
	return Den;
}
Fraction::Fraction(int A, int B)
{
	Init(A, B);
}

void Fraction::Init(int n, int d)
{
	this->Num = n;
	this->Den = d;
}

Fraction Fraction::operator+(Fraction C)
{

	int n = this->Num;
	int d = this->Den;
	Fraction R;


	R.Den = LCM(d, C.Den);
	int sum = ((R.Den / d) * n) + ((R.Den / C.Den) * C.Num);
	R.Num = sum;

	R.Init(R.Num / GCD(R.Num, R.Den), R.Den / GCD(R.Num, R.Den));
	return R;
}

Fraction Fraction::operator-(Fraction C)
{
	Fraction R;
	int n = this->Num;
	int d = this->Den;


	R.Den = LCM(d, C.Den);
	int sum = ((R.Den / d) * n) - ((R.Den / C.Den) * C.Num);
	R.Num = sum;

	R.Init(R.Num / GCD(R.Num, R.Den), R.Den / GCD(R.Num, R.Den));
	return R;
}

Fraction Fraction::operator*(Fraction C)
{
	Fraction R;
	int n = this->Num * C.Num;
	int d = this->Den * C.Den;

	R.Num = (n) / GCD(n, d);
	R.Den = (d) / GCD(n, d);

	return R;
}

Fraction Fraction::operator/(Fraction C)
{
	Fraction R;
	int n = this->Num * C.Den;
	int d = this->Den * C.Num;

	R.Num = (n) / GCD(n, d);
	R.Den = (d) / GCD(n, d);
	return R;
}

Fraction Fraction::operator!()
{
	Fraction R;
	int d = this->Num;
	int n = this->Den;


	R.Num = (n) / GCD(n, d);
	R.Den = (d) / GCD(n, d);

	return R;
}

Fraction Fraction::operator&()
{
	Fraction R;
	int n = this->Num;
	int d = this->Den;

	if (n > 0 && d < 0)
	{
		R.Num = n;
		R.Den = -(d);
	}
	else if (n < 0 && d>0)
	{
		R.Num = -(n);
		R.Den = d;
	}
	else if (d > 0 && n > 0)
	{
		R.Num = -(n);
		R.Den = d;
	}
	else
	{
		R.Num = -(n);
		R.Den = d;
	}


	R.Num = (R.Num) / GCD(n, d);
	R.Den = (R.Den) / GCD(n, d);

	return R;
}
