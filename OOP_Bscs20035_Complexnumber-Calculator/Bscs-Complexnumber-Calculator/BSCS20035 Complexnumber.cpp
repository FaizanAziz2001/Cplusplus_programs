#pragma once
class Complexnumber
{
	float real;
	float imaginary;

public:
	Complexnumber(float r = 0, float i = 0);
	void Init(float r, float i);
	float getreal();
	float getimaginary();
	Complexnumber operator+(Complexnumber C);
	Complexnumber operator-(Complexnumber C);
	Complexnumber operator*(Complexnumber C);
	Complexnumber operator/(Complexnumber C);
	Complexnumber operator!();
	Complexnumber Inv();
	Complexnumber operator~();
	void operator&();

};



#include "Complexnumber.h"
#include<iostream>
#include<math.h>
using namespace std;

Complexnumber::Complexnumber(float r, float i)
{
	Init(r, i);
}

void Complexnumber::Init(float r, float i)
{
	real = r;
	imaginary = i;
}

float Complexnumber::getreal()
{
	return real;
}

float Complexnumber::getimaginary()
{
	return imaginary;
}


Complexnumber Complexnumber::operator+(Complexnumber C)
{
	float a = this->real;
	float b = this->imaginary;
	Complexnumber R(a + C.real, b + C.imaginary);
	return R;
}

Complexnumber Complexnumber::operator-(Complexnumber C)
{
	float a = this->real;
	float b = this->imaginary;
	Complexnumber R(a - C.real, b - C.imaginary);
	return R;
}

Complexnumber Complexnumber::operator*(Complexnumber C)
{
	float a = this->real;
	float b = this->imaginary;
	Complexnumber R(a * C.real - b * C.imaginary, a * C.imaginary + b * C.real);
	return R;
}

Complexnumber Complexnumber::operator!()
{
	Complexnumber R;
	R.real = -(this->real);
	R.imaginary = -(this->imaginary);
	return R;
}

Complexnumber Complexnumber::Inv()
{
	float a = this->real;
	float b = this->imaginary;
	Complexnumber R(a / (a * a + b * b), -b / (a * a + b * b));
	return R;
}

Complexnumber Complexnumber::operator/(Complexnumber C)
{
	Complexnumber R(0, 0);
	R = (*this) * C.Inv();
	return R;
}

Complexnumber Complexnumber::operator~()
{
	Complexnumber R;
	float x = this->imaginary;
	float y = this->real;
	R.imaginary = -(x);
	R.real = y;
	return R;
}

void Complexnumber:: operator&()
{
	Complexnumber R;
	float sum = 0;
	sum = pow(this->real, 2) + pow(this->imaginary, 2);
	sum = sqrt(sum);
	cout << "Mod is " << sum << endl;

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
#include "complexnumber.h";ne nahi
using namespace std;


#include<fstream>
#include <iostream>
#include "Complexnumber.h";ne nahi
using namespace std;

ostream& operator<<(ostream& console, Complexnumber C)
{
	cout << "(" << C.getreal() << ", " << C.getimaginary() << ")";
	return console;
}
void init(Complexnumber*& data, int& NOCs)
{
	ifstream fin("Cs.txt");
	fin >> NOCs;
	data = new Complexnumber[NOCs];
	for (int i = 0; i < NOCs; i++)
	{
		float a, b;
		fin >> a >> b;
		data[i].Init(a, b);
	}
}

void PrintAlldata(Complexnumber* data, int NOCs)
{
	for (int i = 0; i < NOCs; i++)
	{
		cout << "C" << i + 1 << "=";
		cout << data[i];
		cout << endl;
	}
}


void menuCN()
{
	cout << "+ for Add" << endl
		<< "- for Sub" << endl
		<< "* for Multi" << endl
		<< "/ for div" << endl
		<< "~ for Conj" << endl
		<< "! for Additive inverse" << endl
		<< "& for Mod" << endl;
}

int main()
{
	char cont;
	Complexnumber* data;
	int NOCs;
	init(data, NOCs);
	char opr, ch;
	int input = 0, rinput = 0, iinput = 0;
	do
	{
		system("cls");
		PrintAlldata(data, NOCs);
		cout << "Enter the number to store in:";
		cin >> ch >> input;

		menuCN();
		cout << "Enter the operator:";
		cin >> opr;
		if (opr != '%')
		{
			cout << "Enter the 1 number:";
			cin >> ch >> rinput;

			if (opr != '^' && opr != '%' && opr != '!')
			{
				cout << "Enter the 2 number:";
				cin >> ch >> iinput;
			}
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
		case '^':
			data[input] = ~data[rinput];
			break;
		case '%':
			&data[input];
			system("pause");
			break;
		case '!':
			data[input] = !data[rinput];
			break;
		}
		cout << endl << endl;
		PrintAlldata(data, NOCs);
		cout << "Do you want to continue(Y for yes)";
		cin >> cont;
	} while (cont == 'Y' || cont == 'y');

	return 0;
}





/*


				sample output:

c1=(5, 1)
c2 = (2, 5)
c3 = (3, -3)
c4 = (7, 4)
c5 = (5, 2)
enter the number to store in : c3
+ for add
- for sub
* for multi
/ for div
^ for conj
!for additive inverse
% for mod
enter the operator:^
enter the 1 number : c5


c1 = (5, 1)
c2 = (2, 5)
c3 = (5, -2)
c4 = (7, 4)
c5 = (5, 2)
do you want to continue(y for yes)n




*/