#pragma once
class CompoundFraction
{
private:
	int numerator;
	int denominator;
	int whole;
	int GCD(int num, int den);
	int LCM(int num, int den);
	static int convert(int x, int y, int z);
	void Simplify();


public:
	CompoundFraction();
	void init(int x, int y, int z);
	void print();
	void CompoundToImproper(CompoundFraction C, int& a, int& b);
	void SingleCompoundToImproper(int& a);
	void ImproperTocompound();
	void PrintAddress();
	CompoundFraction Add(CompoundFraction C);
	CompoundFraction Sub(CompoundFraction C);
	CompoundFraction Mult(CompoundFraction C);
	CompoundFraction Div(CompoundFraction C);
	CompoundFraction MultiInv();
	CompoundFraction AddInv();
};


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

/*

4
2 2 3
5 3 2
-8 5 7
6 3 7


*/


#include<fstream>
#include <iostream>
using namespace std;
#include "CompoundFraction.h";


void init(CompoundFraction*& data, int& size)
{
	ifstream fin("Input.txt");
	fin >> size;
	data = new CompoundFraction[size];
	int input1, input2, input3;
	for (int i = 0; i < size; i++)
	{
		fin >> input1 >> input2 >> input3;
		data[i].init(input1, input2, input3);
	}
}

void printall(CompoundFraction* data, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << "F" << i + 1 << ":\t"; data[i].print();
		cout << endl;
	}
}

void printAddress(CompoundFraction* data, int size)
{
	cout << &data << " (" << data << ")--->" << endl << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "\t" << &data[i] << "-->\t";
		data[i].PrintAddress();
		cout << endl << endl;
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
	CompoundFraction* data;
	int size = 0;
	init(data, size);
	printall(data, size);
	cout << endl << endl;



	char opr, ch, cont;
	int input = 0, rinput = 0, iinput = 0;
	do
	{

		system("cls");
		printall(data, size);
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
			data[input] = data[rinput].Add(data[iinput]);
			break;
		case '-':
			data[input] = data[rinput].Sub(data[iinput]);
			break;
		case '*':
			data[input] = data[rinput].Mult(data[iinput]);
			break;
		case '/':
			data[input] = data[rinput].Div(data[iinput]);
			break;
		case '!':
			data[input] = data[rinput].MultiInv();
			break;
		case '^':
			data[input] = data[rinput].AddInv();
			break;
		}
		cout << endl;
		printall(data, size);
		cout << endl << endl;
		printAddress(data, size);
		cout << "Do you want to continue(Y for yes)";
		cin >> cont;
	} while (cont == 'Y' || cont == 'y');


}



/*


				Sample Output:

F1:     2-(2/3)
F2:     5-(3/2)
F3:     -8-(5/7)
F4:     6-(3/7)
Enter the number to store in:F1
+ for Add
- for Sub
* for Multi
/ for div
! for Multi Inverse
^ for Additive inverse
Enter the operator:-
Enter the 1 number:F3
Enter the 2 number:F2

F1:     -13-(11/14)
F2:     5-(3/2)
F3:     -8-(5/7)
F4:     6-(3/7)


data pointer 00FEFCF8 (01464B60)--->

		01464B60-->     01464B60 (11)  01464B64 (14)  01464B68 (-13)

		01464B6C-->     01464B6C (3)  01464B70 (2)  01464B74 (5)

		01464B78-->     01464B78 (5)  01464B7C (7)  01464B80 (-8)

		01464B84-->     01464B84 (3)  01464B88 (7)  01464B8C (6)

Do you want to continue(Y for yes)







*/