#pragma once
#include<fstream>
using namespace std;

struct Pair
{
	int x;
	int y;
};
class Set
{
	int size;
	int* Vs;
	static Set Uset;
	void insertatend(int i);
	void removeatend(int i);
	bool belongTo(int i) const;

public:

	static void LoadUSet(string filename);
	Set(int size);
	Set(ifstream& fin);
	Set(const Set&);
	Set();
	void Deallocate();
	void Deepcopy(const Set&);
	void init(ifstream& fin);
	friend ostream& operator << (ostream&,const Set&);
	friend istream& operator>>(istream&, Set&);
	friend ofstream& operator << (ofstream&,Set&);
	friend ifstream& operator>> (ifstream&, Set&);
	friend istream& inputfromsize(istream& console, Set& S);
	friend istream& inputtill_1(istream& console, Set& S);
	const Set& operator=(const Set&);
	const Set operator+(const Set& S)const;
	const Set operator-(const Set& S)const;
	const Set operator^(const Set& S)const;
	bool operator|(const Set& S)const;
	const Set& operator+=(int num);
	const Set& operator-=(int num);
	const Set& operator+=(const Set& S);
	const Set& operator-=(const Set& S);
	bool operator==(const Set& S)const;
	const Set& operator~();
	int operator[](int i) const;
	int& operator[](int i);
	void Loadpair(Pair*, const Set& S) const;
	void operator*(const Set& S)const;

};

