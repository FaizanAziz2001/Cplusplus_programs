#include<fstream>
#include <iostream>
#include "Complexnumber.h";ne nahi
using namespace std;

ostream& operator<<(ostream& console,Complexnumber C)
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


