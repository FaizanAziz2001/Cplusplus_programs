#pragma once
#include<iostream>
#include<fstream>
using namespace std;

class Vector3D
{
    double x, y, z;

public:
    Vector3D(double tx = 0, double ty = 0, double tz = 0);
    void print();
    void ReadValues(ifstream& Rdr); // should read from file
    void init(double a, double b, double c);
    void PrintAddress();
    double Magnitude();   // sqrt(x*x + y*y + z*z)
    Vector3D UnitVector(); // x /mag , y/mag , z/mag
    Vector3D Add(Vector3D V);
    Vector3D Subtract(Vector3D V);
    Vector3D CrossProduct(Vector3D V);
    double DotProduct(Vector3D V);
    static Vector3D UnitX();   // return (1,0,0) 
    static Vector3D UnitY();   // return (0,1,0)
    static Vector3D UnitZ();   // return (0,0,1)
    Vector3D ProjectionAtV(Vector3D V);
    double Area_Parrallelogram(Vector3D V);
    double Area_Traingle(Vector3D V);
    ~Vector3D();
};



#include "Vector3D.h"
#include<iostream>
#include<fstream>
using namespace std;

Vector3D::Vector3D(double a, double b, double c)
{
	init(a, b, c);
}

void Vector3D::init(double a, double b, double c)
{
	x = a;
	y = b;
	z = c;
}
void Vector3D::ReadValues(ifstream& Rdr)
{
	Rdr >> x >> y >> z;
}

void Vector3D::PrintAddress()
{
	cout << &x << " (" << x << ")  ";
	cout << &y << " (" << y << ")  ";
	cout << &z << " (" << z << ")  ";

}

void Vector3D::print()
{
	cout << "(" << x << " , " << y << " , " << z << ")";
}

double Vector3D::Magnitude()
{
	double magnitude;
	magnitude = sqrt(x * x + y * y + z * z);
	return magnitude;
}

Vector3D Vector3D::UnitVector()
{
	Vector3D R;
	R.x = x / this->Magnitude();
	R.y = y / this->Magnitude();
	R.z = z / this->Magnitude();
	return R;
}

Vector3D Vector3D::Add(Vector3D V)
{
	Vector3D R;
	R.x = this->x + V.x;
	R.y = this->y + V.y;
	R.z = this->z + V.z;
	return R;
}

Vector3D Vector3D::Subtract(Vector3D V)
{
	Vector3D R;
	R.x = this->x - V.x;
	R.y = this->y - V.y;
	R.z = this->z - V.z;
	return R;
}

Vector3D Vector3D::CrossProduct(Vector3D V)
{
	Vector3D R;
	R.x = y * V.z - z * V.y;
	R.y = -(x * V.z - z * V.x);
	R.z = x * V.y - y * V.x;
	return R;
}

double Vector3D::DotProduct(Vector3D V)
{
	double DP = 0;
	Vector3D R;
	R.x = this->x * V.x;
	R.y = this->y * V.y;
	R.z = this->z * V.z;
	DP = R.x + R.y + R.z;
	return DP;
}

Vector3D Vector3D::UnitX()
{
	return (1, 0, 0);
}

Vector3D Vector3D::UnitY()
{

	return (0, 1, 0);
}

Vector3D Vector3D::UnitZ()
{
	return (0, 0, 1);
}

Vector3D Vector3D::ProjectionAtV(Vector3D V)
{
	Vector3D R;
	double a = this->DotProduct(V);
	double b = V.DotProduct(V);
	R.x = (a / b) * V.x;
	R.y = (a / b) * V.y;
	R.z = (a / b) * V.z;
	return R;
}

double Vector3D::Area_Parrallelogram(Vector3D V)
{
	Vector3D R;
	double Area;
	R = this->CrossProduct(V);
	Area = R.Magnitude();
	return Area;

}

double Vector3D::Area_Traingle(Vector3D V)
{
	Vector3D R;
	double Area;
	R = this->CrossProduct(V);
	Area = R.Magnitude() / 2;
	return Area;

}

Vector3D::~Vector3D()
{
	cout << "I am destroyed" << endl;
}



/*

5
2 -3 5
3 6 -4
7 8 9
1 2 3
3 2 1


*/




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




/*

			Sample output:

V1:     (2 , -3 , 5)
V2:     (3 , 6 , -4)
V3:     (7 , 8 , 9)
V4:     (1 , 2 , 3)
V5:     (3 , 2 , 1)

+ for Add
- for Sub
x for Cross Product
. for Dot Product
| for Magnitude
^ for Unit Vector
> for Projection
P for Area of parallelogram
T for Area of parallelogram


Enter the operator:+
Enter the number to store in:V1
Enter the 1 number:V2
Enter the 2 number:V3
I am destroyed
I am destroyed
I am destroyed


V1:     (10 , 14 , 5)
V2:     (3 , 6 , -4)
V3:     (7 , 8 , 9)
V4:     (1 , 2 , 3)
V5:     (3 , 2 , 1)


data pointer 001EFB24 (00A2C1A4)--->

        00A2C1A4-->     00A2C1A4 (10)  00A2C1AC (14)  00A2C1B4 (5)

        00A2C1BC-->     00A2C1BC (3)  00A2C1C4 (6)  00A2C1CC (-4)

        00A2C1D4-->     00A2C1D4 (7)  00A2C1DC (8)  00A2C1E4 (9)

        00A2C1EC-->     00A2C1EC (1)  00A2C1F4 (2)  00A2C1FC (3)

        00A2C204-->     00A2C204 (3)  00A2C20C (2)  00A2C214 (1)

Do you want to continue(Y for yes)n

*/
