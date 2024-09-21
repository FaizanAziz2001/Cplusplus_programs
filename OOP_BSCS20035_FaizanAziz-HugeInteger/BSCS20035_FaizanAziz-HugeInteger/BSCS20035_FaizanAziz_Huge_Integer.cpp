#pragma once
#include<fstream>
#include<iostream>
using namespace std;

class HugeInteger
{
	int* Ds;
	int size;
	int IsNeg;

public:

	HugeInteger UnitInteger();
	HugeInteger ZeroInteger() const;
	HugeInteger();
	HugeInteger(int);
	HugeInteger(ifstream& fin);
	HugeInteger(const HugeInteger& H);
	void RemoveatEnd();
	void Trim();
	void SetInteger(ifstream& fin);
	void DeepCopy(const HugeInteger& H);

	friend ostream& operator << (ostream&, const HugeInteger&);
	friend ifstream& operator>>(ifstream&, HugeInteger&);

	int operator[](int)const;
	int& operator[](int);

	HugeInteger& operator=(const HugeInteger& HI);
	HugeInteger ADDQuantityWise(const HugeInteger& HI) const;
	HugeInteger SUBQuantityWise(const HugeInteger& HI) const;

	const HugeInteger operator++(int);
	const HugeInteger operator--(int);
	HugeInteger operator+(const HugeInteger& H)const;
	HugeInteger& operator++();
	HugeInteger& operator--();
	HugeInteger operator-(const HugeInteger& H)const;
	HugeInteger operator-() const;
	HugeInteger& operator+=(const HugeInteger& H);
	HugeInteger& operator-=(const HugeInteger& H);

	HugeInteger operator* (const HugeInteger& H) const;
	HugeInteger operator*= (const HugeInteger& H) const;
	HugeInteger operator/ (const HugeInteger& H) const;
	HugeInteger operator& (const HugeInteger& H) const;
	HugeInteger operator&= (const HugeInteger& H) const;
	HugeInteger operator/= (const HugeInteger& H) const;

	bool GreaterThanQuantityWise(const HugeInteger& HI) const;
	bool LessThanQuantityWise(const HugeInteger& HI) const;
	bool EqualQuantityWise(const HugeInteger& HI) const;
	bool operator<(const HugeInteger& H)const;
	bool operator<=(const HugeInteger& H)const;
	bool operator>(const HugeInteger& H)const;
	bool operator>=(const HugeInteger& H)const;
	bool operator==(const HugeInteger& H)const;
	bool operator!=(int)const;
	bool check(const HugeInteger& H)const;
	~HugeInteger();
};







#include "HugeInteger.h"
#include<fstream>
using namespace std;

HugeInteger::HugeInteger()
{
	Ds = nullptr;
	size = 0;
	IsNeg = false;
}
HugeInteger::HugeInteger(int i)
{
	Ds = new int[1]{ i };
	size = 1;
	IsNeg = false;
}
HugeInteger::HugeInteger(ifstream& fin)
{
	SetInteger(fin);
}
HugeInteger HugeInteger::UnitInteger()
{
	HugeInteger R;
	R.Ds = new int[1]{ 1 };
	R.size = 1;
	return R;

}
HugeInteger HugeInteger::ZeroInteger() const
{
	HugeInteger R;
	R.Ds = new int[1]{ 0 };
	R.size = 1;
	return R;

}
HugeInteger::HugeInteger(const HugeInteger& H)
{
	DeepCopy(H);
}
HugeInteger& HugeInteger::operator=(const HugeInteger& HI)
{
	if (this == &HI)
		return  (*this);
	DeepCopy(HI);
	return (*this);
}

void HugeInteger::RemoveatEnd()
{
	int* heap = new int[size - 1];
	for (int i = 0; i < size - 1; i++)
	{
		heap[i] = Ds[i];
	}
	delete[]Ds;
	Ds = heap;
	size--;
}
void HugeInteger::Trim()
{
	if (size != 1)
	{
		for (int i = size - 1; Ds[i] == 0 && i >= 1; i--)
		{
			this->RemoveatEnd();
		}
	}
}
void HugeInteger::SetInteger(ifstream& fin)
{
	char ch;
	string integer;
	fin >> ch;
	if (ch == '+')
		IsNeg = false;
	else if (ch == '-')
		IsNeg = true;
	fin >> integer;
	size = integer.size();
	Ds = new int[size] {};
	for (int i = 0; i < size; i++)
	{
		Ds[i] = integer[size - 1 - i] - 48;
	}
}
void HugeInteger::DeepCopy(const HugeInteger& H)
{
	size = H.size;
	IsNeg = H.IsNeg;
	Ds = new int[size] {};
	for (int i = 0; i < size; i++)
	{
		Ds[i] = H.Ds[i];
	}
}

ostream& operator << (ostream& console, const HugeInteger& HI)
{
	cout << (HI.IsNeg ? '-' : '+');
	for (int i = 0; i < HI.size; i++)
	{
		cout << HI.Ds[HI.size - 1 - i];
	}
	return console;
}
ifstream& operator>>(ifstream& fin, HugeInteger& HI)
{
	HI.SetInteger(fin);
	HI.Trim();
	return fin;
}


int HugeInteger::operator[](int i)const
{

	return ((i >= size) ? 0 : Ds[i]);
}
int& HugeInteger::operator[](int i)
{
	return Ds[i];
}

bool HugeInteger::GreaterThanQuantityWise(const HugeInteger& HI) const
{
	if (size > HI.size)
		return true;
	else if (size < HI.size)
		return false;

	for (int i = size - 1; i >= 0; i--)
	{
		if ((*this)[i] > HI[i])
			return true;
		else if ((*this)[i] < HI[i])
			return false;
	}
	return false;
}
bool HugeInteger::LessThanQuantityWise(const HugeInteger& HI) const
{
	return (HI.GreaterThanQuantityWise(*this));
}
bool HugeInteger::EqualQuantityWise(const HugeInteger& HI) const
{
	return (!this->GreaterThanQuantityWise(HI) && !this->LessThanQuantityWise(HI));
}
bool HugeInteger::check(const HugeInteger& H)const
{
	if (IsNeg == true && H.IsNeg == true)
		return false;
	else if (IsNeg == false && H.IsNeg == false)
		return false;
	return true;
}

HugeInteger HugeInteger::ADDQuantityWise(const HugeInteger& HI) const
{
	int carry = 0;
	HugeInteger R;
	R.size = size + 1;
	R.Ds = new int[R.size]{};
	for (int i = 0; i < R.size; i++)
	{
		R[i] = ((*this)[i] + HI[i] + carry) % 10;
		carry = ((*this)[i] + HI[i] + carry) / 10;
	}
	R.Trim();
	return R;
}
HugeInteger HugeInteger::SUBQuantityWise(const HugeInteger& HI) const
{
	int carry = 0;
	HugeInteger R;
	R.size = size;
	R.Ds = new int[R.size]{};
	for (int i = 0; i < R.size; i++)
	{
		R.Ds[i] = ((*this)[i] - HI[i] - carry);
		if (R.Ds[i] < 0)
		{
			R.Ds[i] += 10;
			carry = 1;
		}
		else
			carry = 0;
	}
	R.Trim();
	return R;
}


HugeInteger HugeInteger::operator+(const HugeInteger& H) const
{
	HugeInteger R;
	if (IsNeg == H.IsNeg)
	{
		if (this->GreaterThanQuantityWise(H))
			R = this->ADDQuantityWise(H);
		else
			R = H.ADDQuantityWise(*this);
		R.IsNeg = IsNeg;
	}
	else
	{
		if (this->GreaterThanQuantityWise(H))
		{
			R = this->SUBQuantityWise(H);
			R.IsNeg = IsNeg;
		}
		else
		{
			R = H.SUBQuantityWise(*this);
			R.IsNeg = H.IsNeg;
		}

	}

	return R;
}
HugeInteger& HugeInteger::operator++()
{
	*this = *this + UnitInteger();
	return *this;
}
HugeInteger& HugeInteger::operator--()
{
	*this = *this - UnitInteger();
	return *this;
}
HugeInteger HugeInteger::operator-() const
{
	HugeInteger R = *this;
	R.IsNeg = !IsNeg;
	return R;
}
HugeInteger HugeInteger::operator-(const HugeInteger& H)const
{
	HugeInteger R;
	R = *this + (-H);
	if (R != 0)
		return R;
	else
	{
		R.IsNeg = false;
		return R;
	}
}

const HugeInteger HugeInteger::operator--(int i)
{
	HugeInteger temp = *this;
	*this = *this - UnitInteger();
	return temp;
}
const HugeInteger HugeInteger::operator++(int i)
{
	HugeInteger temp = *this;
	*this = *this + UnitInteger();
	return temp;
}

HugeInteger HugeInteger::operator* (const HugeInteger& H) const
{
	HugeInteger R;
	HugeInteger A = *this, B = H;
	A.IsNeg = false;
	B.IsNeg = false;

	for (HugeInteger I(1); I <= B; I++)
	{
		R = R + (A);
	}

	R.IsNeg = this->check(H);
	return R;
}
HugeInteger HugeInteger::operator/ (const HugeInteger& H) const
{
	HugeInteger A = *this, B = H;
	A.IsNeg = false;
	B.IsNeg = false;
	HugeInteger I(0);
	if (A >= B && A != 0 && B != 0)
	{
		do
		{
			A = A - (B);
			I++;
		} while (A >= B);
	}

	I.IsNeg = this->check(H);
	return I;
}
HugeInteger HugeInteger::operator& (const HugeInteger& H) const
{
	HugeInteger A = *this, B = H;
	A.IsNeg = false;
	B.IsNeg = false;
	HugeInteger I(0);
	if (A >= B && A != 0 && B != 0)
	{
		do
		{
			A = A - (B);
			I++;
		} while (A >= B);
	}

	A.IsNeg = this->check(H);
	return A;
}
HugeInteger HugeInteger::operator&= (const HugeInteger& H) const
{
	HugeInteger R = H, Total;
	HugeInteger A = *this, B = H;
	HugeInteger I(1);

	A.IsNeg = false;
	B.IsNeg = false;

	if (B != 0 && A != 0)
	{
		if (*this < H)
		{
			do
			{
				R.IsNeg = false;

				while (R + R <= A)
				{
					R += R;
					I += I;
				}
				A = A - R;
				Total = Total + I;
				I = 1;
				R = H;
			} while (B < A);
		}
	}
	else
	{
		cout << "Undefined" << endl;
		A = 0;
		return A;
	}

	A.IsNeg = this->check(H);
	return A;
}
HugeInteger HugeInteger::operator*= (const HugeInteger& H) const
{
	HugeInteger R = *this, B = H, Total, I(1);
	do
	{
		R.IsNeg = false;
		B.IsNeg = false;
		while (I + I <= B)
		{
			R += R;
			I += I;
		}
		Total += R;
		B = B - I;
		R = *this;
		I = 1;
	} while (B != 0);

	Total.IsNeg = this->check(H);
	return Total;
}
HugeInteger HugeInteger::operator/= (const HugeInteger& H) const
{

	HugeInteger R = H, Total;
	HugeInteger A = *this, B = H;
	HugeInteger I(1);

	A.IsNeg = false;
	B.IsNeg = false;

	if (A != 0 && B != 0 && A >= B)
	{
		do
		{
			R.IsNeg = false;

			while (R + R <= A)
			{
				R += R;
				I += I;
			}
			A = A - R;
			Total = Total + I;
			I = 1;
			R = H;
		} while (B < A);
	}
	else
		return 0;

	Total.IsNeg = this->check(H);
	return Total;
}
HugeInteger& HugeInteger::operator+=(const HugeInteger& H)
{
	*this = *this + H;
	return *this;
}
HugeInteger& HugeInteger::operator-=(const HugeInteger& H)
{
	*this = *this - H;
	return *this;
}

bool HugeInteger::operator<(const HugeInteger& H)const
{
	if (IsNeg == false && H.IsNeg == true)
	{
		return false;
	}
	else if (IsNeg == true && H.IsNeg == false)
	{
		return true;
	}
	else if (IsNeg == false)
	{
		if (this->GreaterThanQuantityWise(H))
			return false;
		else if (H.GreaterThanQuantityWise(*this))
			return true;
		else
			return false;
	}
	else if (IsNeg == true)
	{
		if (this->GreaterThanQuantityWise(H))
			return true;
		else if (H.GreaterThanQuantityWise(*this))
			return false;
		else
			return true;
	}
}
bool HugeInteger::operator<=(const HugeInteger& H)const
{
	if (*this < H)
		return true;
	else if (H < *this)
		return false;
	else
		return true;

}
bool HugeInteger::operator>(const HugeInteger& H)const
{
	return H < *this;
}
bool HugeInteger::operator>=(const HugeInteger& H)const
{
	return (H <= *this);
}
bool HugeInteger::operator!=(int i) const
{
	return !(size == 1 && Ds[0] == i);
}
bool HugeInteger::operator==(const HugeInteger& H)const
{
	return (!(*this < H) && !(H < *this));
}

HugeInteger::~HugeInteger()
{
	delete[] Ds;
	Ds = nullptr;
}





/*

8
+0000000000000000
-827373873738273
+7472929376482918
+827351719278273
-719273577393764
+628273387282938
+1237472929363728
+0




*/







#include<fstream>
#include <iostream>
#include"HugeInteger.h"
using namespace std;


void Load(HugeInteger*& H, int& Size)
{
	ifstream fin("Ds.txt");
	fin >> Size;
	H = new HugeInteger[Size];
	for (int i = 0; i < Size; i++)
	{
		fin >> H[i];
	}
}

void Printall(HugeInteger* H, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		cout << "Quantity " << i + 1 << " : " << H[i] << endl;
	}
}

void Binary(HugeInteger* H, int size)
{
	char opr{}, dummy{}, cont;
	int rsi{}, loi{}, roi{};

	do
	{
		Printall(H, size);
		cout << endl;
		cout << "Example Format: F2 + F3" << endl;
		cout << "Example Format: F2 - F3" << endl;
		cout << "Example Format: F2 * F3" << endl;
		cout << "Example Format: F2 / F3" << endl;
		cout << "Example Format: F2 % F3" << endl;
		cout << "Example Format: F2 < F3" << endl;
		cout << "Example Format: F2 > F3" << endl;
		cout << "Input: ";
		cin >> dummy >> loi >> opr >> dummy >> roi;
		rsi--; loi--; roi--;

		switch (opr)
		{
		case '+':
			cout << (H[loi] + H[roi]) << endl;
			break;

		case '-':
			cout << (H[loi] - H[roi]) << endl;
			break;

		case '*':
			cout << (H[loi] * H[roi]) << endl;
			break;
		case '/':
			cout << (H[loi] / H[roi]) << endl;
			break;
		case '%':
			cout << (H[loi] & H[roi]) << endl;
			break;
		case '<':
			cout << (H[loi] < H[roi]) << endl;
			break;
		case '>':
			cout << (H[loi] > H[roi]) << endl;
			break;
		}

		cout << endl << endl;
		cout << endl << " Do You Want To Continue?(Y for yes) ";
		cin >> cont;
		system("cls");
	} while (cont == 'Y' || cont == 'y');
}

void AccumulateSet(HugeInteger* H, int size)
{

	char opr{}, dummy{}, cont;
	int loi{}, roi{};

	do
	{
		Printall(H, size);
		cout << endl;
		cout << "Example Format: F1 + F2 (for +=)" << endl;
		cout << "Example Format: F1 - F2 (for+-)" << endl;
		cout << "Example Format: F1 * F2 (fast product)" << endl;
		cout << "Example Format: F1 / F2 (fast division)" << endl;
		cout << "Example Format: F1 % F2 (fast mod)" << endl;
		cout << "Example Format: F1 = F2 (for checking quantities)" << endl;
		cout << "Example Format: F1 < F2 (for <=)" << endl;
		cout << "Example Format: F1 > F2 (for >=)" << endl;
		cout << "Input: ";
		cin >> dummy >> loi >> opr >> dummy >> roi;
		loi--; roi--;

		switch (opr)
		{
		case '+':
			cout << (H[loi] += H[roi]) << endl;
			break;

		case '-':
			cout << (H[loi] -= H[roi]) << endl;
			break;
		case '*':
			cout << (H[loi] *= H[roi]) << endl;
			break;
		case '/':
			cout << (H[loi] /= H[roi]) << endl;
			break;
		case '%':
			cout << (H[loi] &= H[roi]) << endl;
			break;
		case '<':
			cout << (H[loi] <= H[roi]) << endl;
			break;
		case '>':
			cout << (H[loi] >= H[roi]) << endl;
			break;
		case '=':
			if (H[loi] == H[roi])
				cout << "Quantities are equal" << endl;
			else
				cout << "Quantities are not equal" << endl;
			break;
		}

		cout << endl << endl;
		cout << endl << " Do You Want To Continue?(Y) ";
		cin >> cont;
		system("cls");
	} while (cont == 'Y' || cont == 'y');

}

int main()
{
	HugeInteger* H{};
	int Size = 0, input;
	Load(H, Size);
	char cont;
	do
	{
		system("cls");
		cout << "Enter task number: " << endl
			<< "1. Multiple Set Operations" << endl
			<< "2. Accumulate Set Operations" << endl;
		cin >> input;

		switch (input)
		{
		case 1:
			Binary(H, Size);
			break;

		case 2:
			AccumulateSet(H, Size);
			break;
		}

		cout << "Do you want to continue(Y for yes)";
		cin >> cont;

	} while (cont == 'Y' || cont == 'y');

}