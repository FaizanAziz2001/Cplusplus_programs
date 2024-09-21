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
	cout << "data pointer " << &data << " (" << data << ")--->" << endl << endl;
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

