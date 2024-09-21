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
	R = (*this)*C.Inv();
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