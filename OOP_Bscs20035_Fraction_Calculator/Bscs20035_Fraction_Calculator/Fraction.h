#pragma once
class Fraction
{
	int Num;
	int Den;
	int GCD(int Num, int Den);
	int LCM(int Num, int Den);
public:
	Fraction(int A = 0, int B = 0);
	void Init(int Num, int Den);
	Fraction operator+(Fraction C);
	Fraction operator-(Fraction C);
	Fraction operator*(Fraction C);
	Fraction operator/(Fraction C);
	Fraction operator!();
	Fraction operator&();
	int getnum();
	int getden();
	/*void print();*/
};

