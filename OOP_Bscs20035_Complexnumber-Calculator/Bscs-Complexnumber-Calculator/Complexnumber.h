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

