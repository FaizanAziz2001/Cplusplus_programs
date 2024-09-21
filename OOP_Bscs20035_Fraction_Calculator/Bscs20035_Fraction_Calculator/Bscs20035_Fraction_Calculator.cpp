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


ostream& operator<<(ostream& console,Fraction R)
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
			data[input] = data[rinput]+data[iinput];
			break;
		case '-':
			data[input] = data[rinput]-data[iinput];
			break;
		case '*':
			data[input] = data[rinput]*data[iinput];
			break;
		case '/':
			data[input] = data[rinput]/data[iinput];
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

