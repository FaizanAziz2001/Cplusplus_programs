#include "HugeInt.h"

//UTILITY FUNCs
void HugeInt::DeAllocate()
{
	delete[]Ds;
	size = 0;
	isNeg = false;
}
void HugeInt::removeAtEnd(int*& D, int& size)
{
	size--;
	int* NH = new int[size];
	for (int i = 0; i < size; i++)
		NH[i] = D[i];

	delete[]D;
	D = NH;
}
void HugeInt::TRIM()
{
	while (Ds[size - 1] == 0 && size > 1)
		removeAtEnd(Ds, size);
}
const HugeInt HugeInt::ABS()const
{
	HugeInt R = *this;
	R.isNeg = false;
	return R;
}

//CONSTRUCTORS
HugeInt::HugeInt()
{
	this->Ds = nullptr;
	this->size = 0;
	this->isNeg = false;
}
HugeInt::HugeInt(int n)
{

	this->size = 1;
	Ds = new int[size] {abs(n)};
	if (n > 0)
		this->isNeg = false;
	else
		isNeg = true;
}
HugeInt::HugeInt(ifstream& rdr)
{
	SetInteger(rdr);
}
HugeInt::HugeInt(const HugeInt& H)
{
	SetInteger(H);
}
HugeInt::HugeInt(const char* num)
{
	SetInteger(num);
}


//SET INTEGER FUNCs (INITIALIZERS)
void HugeInt::SetInteger(ifstream& rdr)
{
	string aline;
	char sign;

	rdr >> sign >> aline;

	if (sign == '-')
		this->isNeg = true;
	else
		this->isNeg = false;

	this->size = aline.size();
	this->Ds = new int[size];
	for (int i = 0; i < this->size; i++)
		this->Ds[this->size - 1 - i] = aline[i] - '0';

	TRIM();
}
void HugeInt::SetInteger(const HugeInt& H)
{
	this->size = H.size;
	this->isNeg = H.isNeg;

	this->Ds = new int[this->size];
	for (int i = 0; i < this->size; i++)
	{
		this->Ds[i] = H.Ds[i];
	}

	TRIM();

}
void HugeInt::SetInteger(const char* num)
{
	if (num[0] == '-')
		this->isNeg = true;
	else
		this->isNeg = false;

	this->size = strlen(num) - 1;

	this->Ds = new int[this->size];
	for (int i = 0; i < this->size; i++)
	{
		this->Ds[size - i - 1] = num[i + 1] - '0';
	}
	TRIM();
}
void HugeInt::SetIntegerpost(string num)
{
	if (num[0] == '-')
		this->isNeg = true;
	else
		this->isNeg = false;

	this->size = num.length();

	this->Ds = new int[this->size];
	for (int i = 0; i < this->size; i++)
	{
		this->Ds[size - i - 1] = num[i] - '0';
	}
	TRIM();
}
void HugeInt::SetIntegerpre(string num)
{
	if (num[0] == '-')
		this->isNeg = true;
	else
		this->isNeg = false;

	this->size = num.length();

	this->Ds = new int[this->size];
	for (int i = 0; i < this->size; i++)
	{
		this->Ds[size - i - 1] = num[i] - '0';
	}


}
void HugeInt::SetInteger(istream&)
{
	string aline;
	cin >> aline;

	if (aline[0] == '-')
		this->isNeg = true;
	else
		this->isNeg = false;

	this->size = aline.size() - 1;
	this->Ds = new int[size];
	for (int i = 0; i < this->size; i++)
		this->Ds[this->size - 1 - i] = aline[i + 1] - '0';
	TRIM();
}

//SUBSCRIPT OPERATORS
int& HugeInt::operator[](int i)
{
	return this->Ds[i];
}
int HugeInt::operator[](int i) const
{
	if (i >= this->size)
		return 0;

	return this->Ds[i];
}

//QTY WISE OPERATIONS
const HugeInt HugeInt::ADDQWise(const HugeInt& H)const
{
	HugeInt NH;
	NH.size = this->size + 1;
	NH.Ds = new int[NH.size];
	int carry = 0;
	for (int i = 0; i < NH.size; i++)
	{
		NH[i] = ((*this)[i] + H[i] + carry) % 10;
		carry = ((*this)[i] + H[i] + carry) / 10;
	}
	NH.TRIM();
	return NH;
}
const HugeInt HugeInt::SUBQWise(const HugeInt& H)const
{
	HugeInt NH;
	NH.size = this->size;
	NH.Ds = new int[NH.size];
	int carry = 0;
	for (int i = 0; i < NH.size; i++)
	{
		NH[i] = ((*this)[i] - H[i] - carry);
		if (NH[i] < 0)
		{
			carry = 1;
			NH[i] += 10;
		}
		else
			carry = 0;
	}
	NH.TRIM();
	return NH;
}


//booleans
bool HugeInt::QWiseGT(const HugeInt& H) const
{
	if (this->size < H.size)
		return false;
	else if (this->size > H.size)
		return true;
	else
		for (int i = size - 1; i >= 0; i--)
		{
			if (this->Ds[i] > H.Ds[i])
				return true;
			else if (this->Ds[i] < H.Ds[i])
				return false;
		}
	return false;
}
bool HugeInt::QWiseLT(const HugeInt& H) const
{
	return H.QWiseGT(*this);
}
bool HugeInt::QWiseET(const HugeInt& H) const
{
	return (!this->QWiseGT(H) && !this->QWiseLT(H));
}

//SIGN CHANGE
const HugeInt HugeInt::operator-()const
{

	HugeInt R = *this;
	if (!this->QWiseET("+0"))
		R.isNeg = !isNeg;

	return R;
}

//INCREMENT/DECREMENT
const HugeInt HugeInt::operator++()
{
	*this = *this + "+1";
	return *this;
}
const HugeInt HugeInt::operator++(int)
{
	HugeInt R = *this;
	*this += "+1";
	return R;
}
const HugeInt HugeInt::operator--()
{
	*this = *this - "+1";
	return *this;
}
const HugeInt HugeInt::operator--(int)
{
	HugeInt R = *this;
	*this = *this - "+1";
	return R;
}

//ARITHMETIC
const HugeInt HugeInt::operator+(const HugeInt& H) const
{
	HugeInt R = "0";
	if (isNeg == H.isNeg)
	{
		if (this->QWiseGT(H))
			R = this->ADDQWise(H);
		else
			R = H.ADDQWise(*this);
		R.isNeg = this->isNeg;
	}
	else
	{

		if (this->QWiseGT(H))
		{
			R = this->SUBQWise(H);
			R.isNeg = this->isNeg;
		}
		else
		{
			R = H.SUBQWise(*this);
			R.isNeg = H.isNeg;
		}
	}
	if (R.QWiseET("+0"))
		R.isNeg = false;
	return R;

}
const HugeInt HugeInt::operator-(const HugeInt& H) const
{
	return *this + (-H);


}

//slow multiply
/*
const HugeInt HugeInt::operator*(const HugeInt&H) const
{
	HugeInt R,
	for(HugeInt i = "+0"; i <= H; i++)
	{
		R += *this;
	}

	return R;
}
*/

const HugeInt HugeInt::operator*(const HugeInt& H) const
{
	if (*this == "+0" || H == "+0")
		return "+0";

	HugeInt R = this->ABS();
	HugeInt C = "+1", B = H.ABS();
	HugeInt Total = "+0";

	do
	{
		while (C + C <= B)
		{
			R += R;
			C += C;
		}
		B -= C;
		Total += R;
		R = this->ABS();
		C = "+1";

	} while (B != "+0");


	if (isNeg == H.isNeg)
		Total.isNeg = false;
	else
		Total.isNeg = true;

	if (R.QWiseET("+0"))
		R.isNeg = false;
	return Total;

}
const HugeInt HugeInt::operator/(const HugeInt& H)const
{
	if (H == "+0")
	{
		system("cls");
		cout << "DIVISION BY ZERO\n\n Program Ended";
		int i = 1;
		i--;
		i /= i;
	}
	else if (*this == "+0")
	{
		return "+0";
	}
	if (*this < H)
	{
		HugeInt temp = "+0";
		return temp;
	}
	HugeInt R = H.ABS();
	HugeInt C = "+1";
	HugeInt Remainder = this->ABS(), Quotient = "+0";


	do
	{
		while (R + R <= Remainder)
		{
			R += R;
			C += C;
		}
		Remainder -= R;
		Quotient += C;
		C = "+1";
		R = H.ABS();
	} while (Remainder >= H.ABS());

	if (isNeg == H.isNeg)
		Quotient.isNeg = false;
	else
		Quotient.isNeg = true;

	if (R.QWiseET("+0"))
		R.isNeg = false;
	return Quotient;
}
const HugeInt HugeInt::operator%(const HugeInt& H)const
{
	if (this->ABS() < H.ABS())
		return "+0";

	HugeInt R = H.ABS();
	HugeInt C = "+1";
	HugeInt Remainder = this->ABS(), Quotient = "+0";

	do
	{
		while (R + R <= Remainder)
		{
			R += R;
			C += C;
		}
		Remainder -= R;
		Quotient += C;
		C = "+1";
		R = H.ABS();
	} while (Remainder >= H.ABS());

	//HugeInt Div = *this / H;
	//HugeInt Remainder = (*this - (Div * H));

	if (isNeg)
		Remainder.isNeg = true;
	else
		Remainder.isNeg = false;

	if (R.QWiseET("+0"))
		R.isNeg = false;
	return Remainder;

}

//ASSIGN ACCUMULATE
const HugeInt HugeInt::operator+=(const HugeInt& H)
{
	*this = *this + H;
	return *this;
}
const HugeInt HugeInt::operator-=(const HugeInt& H)
{
	*this = *this - H;
	return *this;
}
const HugeInt HugeInt::operator*=(const HugeInt& H)
{
	*this = *this * H;
	return *this;
}
const HugeInt HugeInt::operator/=(const HugeInt& H)
{
	*this = *this / H;
	return *this;
}
const HugeInt HugeInt::operator%=(const HugeInt& H)
{
	*this = *this % H;
	return *this;
}

//COMPARISON OPERATORs
bool HugeInt::operator==(const HugeInt& H) const
{
	if (isNeg != H.isNeg)
		return false;
	else
		return this->QWiseET(H);
}
bool HugeInt::operator!=(const HugeInt& H) const
{
	return !(*this == H);
}

bool HugeInt::operator<(const HugeInt& H) const
{
	if (isNeg && !H.isNeg)
		return true;
	else if (!isNeg && H.isNeg)
		return false;
	else
	{
		if (isNeg == false)
			return this->QWiseLT(H);
		else
			return H.QWiseLT(*this);
	}
}
bool HugeInt::operator>(const HugeInt& H) const
{
	return H < *this;
}
bool HugeInt::operator<=(const HugeInt& H) const
{
	return (*this < H || *this == H);
}
bool HugeInt::operator>=(const HugeInt& H) const
{
	return H <= *this;
}

//ASSIGNMENT OPERATORS
const HugeInt HugeInt::operator=(const HugeInt& H)
{
	this->DeAllocate();
	this->SetInteger(H);
	return *this;
}
const HugeInt HugeInt::operator=(const char* num)
{
	this->DeAllocate();
	this->SetInteger(num);
	return *this;
}

// I/O FUNCs
ifstream& operator>>(ifstream& rdr, HugeInt& H)
{
	H.SetInteger(rdr);
	return rdr;
}
istream& operator>>(istream& cin, HugeInt& H)
{
	H.SetInteger(cin);
	return cin;
}
ostream& operator<<(ostream&, const HugeInt& H)
{
	if (!H.QWiseET("+0"))
		cout << (H.isNeg ? '-' : '+');

	for (int i = 0; i < H.size; i++)
		cout << H.Ds[H.size - 1 - i];
	return cout;
}

HugeInt::~HugeInt()
{
	DeAllocate();
}

