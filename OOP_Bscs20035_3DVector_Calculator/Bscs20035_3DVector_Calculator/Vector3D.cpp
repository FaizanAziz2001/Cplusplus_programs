#include "Vector3D.h"
#include<iostream>
#include<fstream>
using namespace std;

Vector3D::Vector3D(double a,double b,double c)
{
	init(a, b, c);
}

void Vector3D::init(double a,double b,double c)
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
	cout << "("<< x << " , " << y << " , " << z << ")";
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
	return (1,0,0);
}

Vector3D Vector3D::UnitY()
{
	
	return (0,1,0);
}

Vector3D Vector3D::UnitZ()
{
	return (0, 0, 1);
}

Vector3D Vector3D::ProjectionAtV(Vector3D V)
{
	Vector3D R;
	double a=this->DotProduct(V);
	double b=V.DotProduct(V);
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
	Area = R.Magnitude()/2;
	return Area;

}

Vector3D::~Vector3D()
{
	cout << "I am destroyed" << endl;
}