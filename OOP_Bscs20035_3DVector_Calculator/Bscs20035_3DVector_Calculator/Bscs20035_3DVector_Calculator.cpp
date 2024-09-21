#include<fstream>
#include <iostream>
#include "Vector3D.h"
using namespace std;


void init(Vector3D*& data, int& size)
{
	ifstream fin("Vs.txt");
	fin >> size;
	data = new Vector3D[size]{};
	for (int i = 0; i < size; i++)
	{
		data[i].ReadValues(fin);
	}
}

void printall(Vector3D* data, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << "V" << i + 1 << ":\t"; data[i].print();
		cout << endl;
	}
}

void menu()
{
	cout << endl << "+ for Add" << endl
		<< "- for Sub" << endl
		<< "x for Cross Product" << endl
		<< ". for Dot Product" << endl
		<< "| for Magnitude" << endl
		<< "^ for Unit Vector" << endl
		<< "> for Projection" << endl
		<< "P for Area of parallelogram" << endl
		<< "T for Area of parallelogram" << endl;

	cout << endl << endl;

}

void PrintAddress(Vector3D* data, int size)
{
		cout << "data pointer " << &data << " (" << data << ")--->" << endl << endl;
		for (int i = 0; i < size; i++)
		{
			cout << "\t" << &data[i] << "-->\t";
			data[i].PrintAddress();
			cout << endl << endl;
		}
}

void calculator(Vector3D* data, int size)
{

	char opr, ch;
	int input = 0, rinput = 0, iinput = 0;

	system("cls");
	printall(data, size);
	menu();
	cout << "Enter the operator:";
	cin >> opr;

	if (opr != '.' && opr != '|' && opr != 'P' && opr != 'T')
	{
		cout << "Enter the number to store in:";
		cin >> ch >> input;
	}

	cout << "Enter the 1 number:";
	cin >> ch >> rinput;

	if (opr != '|' && opr != '^')
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
		data[input] = data[rinput].Subtract(data[iinput]);
		break;
	case 'x':
		data[input] = data[rinput].CrossProduct(data[iinput]);
		break;
	case '.':
		cout << "Dot product" << data[rinput].DotProduct(data[iinput]);
		break;
	case '|':
		cout << "Magnitude " << data[rinput].Magnitude();
		break;
	case '^':
		data[input] = data[rinput].UnitVector();
		break;
	case '>':
		data[input] = data[rinput].ProjectionAtV(data[iinput]);
		break;
	case 'P':
		cout << "Area of paralellogram " << data[rinput].Area_Parrallelogram(data[iinput]);
		break;
	case 'T':
		cout << "Area of triangle " << data[rinput].Area_Traingle(data[iinput]);
		break;
	}
	cout << endl << endl;
	printall(data, size);
	cout << endl << endl;
	PrintAddress(data, size);

}

int main()
{
	Vector3D* data;
	int size = 0;
	init(data, size);

	char cont;

	do
	{
		calculator(data, size);
		cout << "Do you want to continue(Y for yes)";
		cin >> cont;
	} while (cont == 'Y' || cont == 'y');

	return 0;
}
	