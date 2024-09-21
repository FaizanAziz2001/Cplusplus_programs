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


/*
5
5 1
2 5
3 -3
7 4
5 2
*/


#include<fstream>
#include <iostream>
#include "Fraction.h";
using namespace std;



void initfraction(Fraction*& data, int& NOCs)
{
	ifstream fin("Fraction.txt");
	fin >> NOCs;
	data = new Fraction[NOCs];
	for (int i = 0; i < NOCs; i++)
	{
		int a, b;
		fin >> a >> b;
		data[i].Init(a, b);
	}
}


ostream& operator<<(ostream& console, Fraction R)
{
	cout << "(" << R.getnum() << ", " << R.getden() << ")";
	return console;
}

void PrintAllFraction(Fraction* data, int NOCs)
{
	for (int i = 0; i < NOCs; i++)
	{
		cout << "C" << i + 1 << "=";
		cout << data[i];
		cout << endl;
	}
}


void menu()
{
	cout << "+ for Add" << endl
		<< "- for Sub" << endl
		<< "* for Multi" << endl
		<< "/ for div" << endl
		<< "! for Multi Inverse" << endl
		<< "^ for Additive inverse" << endl;
}

int main()
{
	char cont;
	Fraction* data;
	int NOCs;
	initfraction(data, NOCs);
	char opr, ch;
	int input = 0, rinput = 0, iinput = 0;
	do
	{

		system("cls");
		PrintAllFraction(data, NOCs);
		cout << "Enter the number to store in:";
		cin >> ch >> input;

		menu();
		cout << "Enter the operator:";
		cin >> opr;
		cout << "Enter the 1 number:";
		cin >> ch >> rinput;

		if (opr != '!' && opr != '^')
		{
			cout << "Enter the 2 number:";
			cin >> ch >> iinput;
		}


		input--;
		rinput--;
		iinput--;
		switch (opr)
		{
		case '+':
			data[input] = data[rinput] + data[iinput];
			break;
		case '-':
			data[input] = data[rinput] - data[iinput];
			break;
		case '*':
			data[input] = data[rinput] * data[iinput];
			break;
		case '/':
			data[input] = data[rinput] / data[iinput];
			break;
		case '!':
			data[input] = !data[rinput];
			break;
		case '^':
			data[input] = &data[rinput];
			break;
		}
		cout << endl << endl;
		PrintAllFraction(data, NOCs);
		cout << "Do you want to continue(Y for yes)";
		cin >> cont;
	} while (cont == 'Y' || cont == 'y');

	return 0;
}




/*

					Sample Output:

C1=(5, 1)
C2 = (2, 5)
C3 = (3, -3)
C4 = (7, 4)
C5 = (5, 2)
Enter the number to store in : C5
+ for Add
- for Sub
* for Multi
/ for div
!for Multi Inverse
^ for Additive inverse
Enter the operator:*
Enter the 1 number : C3
Enter the 2 number : C4


C1 = (5, 1)
C2 = (2, 5)
C3 = (3, -3)
C4 = (7, 4)
C5 = (7, -4)
Do you want to continue(Y for yes)n



*/
