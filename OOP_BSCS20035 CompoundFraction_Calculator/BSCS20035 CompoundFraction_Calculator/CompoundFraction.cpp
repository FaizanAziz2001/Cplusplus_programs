#include "CompoundFraction.h"
#include<iostream>
using namespace std;

CompoundFraction::CompoundFraction()
{
	numerator = 0;
	denominator = 1;
	whole = 0;
}

int CompoundFraction::GCD(int num, int den)
{
	int max = 0;
	if (num > den)
	{
		max = num;
	}
	else
		max = den;
	if (max > 0)
	{
		for (int i = max; i >= 1; i--)
		{
			if (num % i == 0 && den % i == 0)
				return i;
		}
	}
	else
	{
		for (int i = max; i < 0; i++)
		{
			if (num % i == 0 && den % i == 0)
				return i;
		}
	}
	return 1;

}

int CompoundFraction::LCM(int num, int den)
{
	int LCM = 0;
	LCM = (num * den) / GCD(num, den);
	return LCM;
}

void CompoundFraction::init(int x, int y, int z)
{
	numerator = y;
	denominator = (z > 0) ? z : 1;
	whole = x;
}

int CompoundFraction::convert(int whole, int numerator, int denominator)
{
	int num = 0;
	num = (denominator * whole) + numerator;
	return num;
}

void CompoundFraction::print()
{
	cout << this->whole << "-(" << this->numerator << "/" << this->denominator << ")";
}

void CompoundFraction::PrintAddress()
{
	cout << &numerator << " (" << numerator << ")  ";
	cout << &denominator << " (" << denominator << ")  ";
	cout << &whole << " (" << whole << ")  ";

}

void CompoundFraction::ImproperTocompound()
{

	whole = numerator / denominator;
	if (numerator >= 0)
		numerator = numerator % denominator;
	else
		numerator = abs(numerator) % denominator;
}

void CompoundFraction::CompoundToImproper(CompoundFraction C, int& a, int& b)
{
	a = convert(this->whole, this->numerator, this->denominator);
	b = convert(C.whole, C.numerator, C.denominator);
}

void CompoundFraction::SingleCompoundToImproper(int& a)
{
	a = convert(this->whole, this->numerator, this->denominator);

}

void CompoundFraction::Simplify()
{
	int gcd = GCD(numerator, denominator);
	numerator /= gcd;
	denominator /= gcd;
}

CompoundFraction CompoundFraction::Add(CompoundFraction C)
{
	CompoundFraction R;
	int N, D;
	R.denominator = LCM(this->denominator, C.denominator);
	CompoundToImproper(C, N, D);
	R.numerator = ((R.denominator / this->denominator) * N) + ((R.denominator / C.denominator) * D);
	R.Simplify();
	R.ImproperTocompound();


	return R;
}

CompoundFraction CompoundFraction::Sub(CompoundFraction C)
{
	CompoundFraction R;
	int N, D;
	R.denominator = LCM(this->denominator, C.denominator);
	CompoundToImproper(C, N, D);
	R.numerator = ((R.denominator / this->denominator) * N) - ((R.denominator / C.denominator) * D);
	R.Simplify();
	R.ImproperTocompound();
	return R;
}

CompoundFraction CompoundFraction::Mult(CompoundFraction C)
{
	CompoundFraction R;
	int N, D;
	CompoundToImproper(C, N, D);

	R.denominator = this->denominator * C.denominator;
	R.numerator = N * D;

	R.Simplify();

	R.ImproperTocompound();
	return R;
}

CompoundFraction CompoundFraction::Div(CompoundFraction C)
{
	CompoundFraction R;
	int N1, N2;
	CompoundToImproper(C, N1, N2);

	R.denominator = this->denominator * N2;
	R.numerator = N1 * C.denominator;

	R.Simplify();

	R.ImproperTocompound();
	return R;
}

CompoundFraction CompoundFraction::MultiInv()
{
	CompoundFraction R;
	int N1;
	SingleCompoundToImproper(N1);

	R.denominator = N1;
	R.numerator = this->denominator;

	R.ImproperTocompound();
	return R;
}

CompoundFraction CompoundFraction::AddInv()
{
	CompoundFraction R;
	if (this->numerator < 0 || this->denominator < 0 || this->whole < 0)
	{
		R.numerator = abs(this->numerator);
		R.denominator = abs(this->denominator);
		R.whole = abs(this->whole);
	}

	else
	{
		R.numerator = this->numerator;
		R.denominator = this->denominator;
		R.whole = -(this->whole);
	}
	return R;

}