#pragma once
class CompoundFraction
{
private:
	int numerator;
	int denominator;
	int whole;
	int GCD(int num, int den);
	int LCM(int num, int den);
	int convert(int x, int y, int z);
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

