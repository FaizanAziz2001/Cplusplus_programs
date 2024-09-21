#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class HugeInt
{
	int* Ds;
	int size;
	bool isNeg;
	void DeAllocate();
	void removeAtEnd(int*&,int&);
	
	const HugeInt ABS()const;

public:
	HugeInt();
	HugeInt(ifstream& rdr);
	HugeInt(const HugeInt&);
	HugeInt(const char* num);
	HugeInt(int num);

	void TRIM();
	void SetInteger(ifstream&);
	void SetInteger(const HugeInt&);
	void SetInteger(const char*);
	void SetInteger(istream&);
	void SetIntegerpost(string num);
	void SetIntegerpre(string num);

	friend ifstream& operator>>(ifstream&, HugeInt&);
	friend istream& operator>>(istream&, HugeInt&);
	friend ostream& operator<<(ostream&, const HugeInt&);
	

	const HugeInt operator=(const HugeInt&);
	const HugeInt operator=(const char* num);

	int& operator[](int);
	int operator[](int)const;

	const HugeInt ADDQWise(const HugeInt& H)const;
	const HugeInt SUBQWise(const HugeInt& H)const;

	bool QWiseGT(const HugeInt& H)const;
	bool QWiseLT(const HugeInt& H)const;
	bool QWiseET(const HugeInt& H)const;


	const HugeInt operator-()const;
	const HugeInt operator++();
	const HugeInt operator++(int);
	const HugeInt operator--();
	const HugeInt operator--(int);


	const HugeInt operator+(const HugeInt&)const;
	const HugeInt operator-(const HugeInt&)const;
	const HugeInt operator*(const HugeInt&)const;
	const HugeInt operator/(const HugeInt&)const;
	const HugeInt operator%(const HugeInt&)const;


	const HugeInt operator+=(const HugeInt&);
	const HugeInt operator-=(const HugeInt&);
	const HugeInt operator*=(const HugeInt&);
	const HugeInt operator/=(const HugeInt&);
	const HugeInt operator%=(const HugeInt&);
	
	bool operator==(const HugeInt&)const;
	bool operator!=(const HugeInt&)const;

	bool operator<(const HugeInt&)const;
	bool operator>(const HugeInt&)const;

	bool operator<=(const HugeInt&)const;
	bool operator>=(const HugeInt&)const;


	
	~HugeInt();

};

