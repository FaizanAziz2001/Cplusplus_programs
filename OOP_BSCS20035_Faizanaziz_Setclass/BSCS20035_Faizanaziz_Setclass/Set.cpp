#include "Set.h"
#include<iostream>
#include<fstream>
#include<conio.h>
using namespace std;

ostream& operator << (ostream& console, const Set& S)
{
	cout << "{ ";
	for (int i = 0; i < S.size; i++)
	{
		if (i == S.size - 1)
			cout << S.Vs[i] << " } ";
		else
			cout << S.Vs[i] << ", ";
	}

	if (S.size == 0)
		cout << " }";
	cout << endl;
	return console;
}
istream& inputfromsize(istream& console, Set& S)
{
	cout << "Enter size: " << endl;
	cin >> S.size;
	S.Vs = new int[S.size];
	cout << "Enter values" << endl;
	for (int i = 0; i < S.size; i++)
	{
		cin >> S.Vs[i];
	}
	return console;
}
istream& operator>> (istream& console, Set& S)
{
	int input = 0;
	cout << "Enter 1 to enter size or 2 to enter while value is not -1: ";
	cin >> input;
	if (input == 1)
		inputfromsize(console, S);
	else if (input == 2)
		inputtill_1(console, S);
	return console;
}
istream& inputtill_1(istream& console, Set& S)
{
	int ch;
	S.size = 0;
	do
	{
		cin >> ch;
		if (ch != -1)
		{
			S.insertatend(ch);
		}


	} while (ch != -1);
	return console;
}
ofstream& operator << (ofstream& fout,Set& S)
{
	fout << S.size << " ";
	for (int i = 0; i < S.size; i++)
	{
		fout << S.Vs[i] << " ";
	}
	cout << endl;
	return fout;
}
ifstream& operator>>(ifstream& fin, Set& S)
{
	fin >> S.size;
	S.Vs = new int[S.size]{};
	for (int i = 0; i < S.size; i++)
	{
		fin >> S.Vs[i];
	}
	return fin;
}
void Set::insertatend(int i)
{
	int* heap = new int[size + 1];
	for (int i = 0; i < size; i++)
	{
		heap[i] = Vs[i];
	}
	heap[size] = i;
	delete[]Vs;
	Vs = heap;
	size++;
}
void Set::removeatend(int num)
{
	Set heap(0);
	for (int i = 0; i < size; i++)
	{
		if (Vs[i] != num)
			heap.insertatend(Vs[i]);
	}
	this->Deallocate();
	*this = heap;

}
bool Set::belongTo(int x) const
{
	for (int i = 0; i < size; i++)
	{
		if (x == Vs[i])
			return true;
	}
	return false;
}
void Set::Deepcopy(const Set& S)
{
	this->size = S.size;
	this->Vs = new int[this->size];
	for (int i = 0; i < this->size; i++)
	{
		this->Vs[i] = S.Vs[i];
	}
}
void Set::Deallocate()
{
	delete[] Vs;
	Vs = nullptr;
	size = 0;
}

Set Set::Uset;
void Set::LoadUSet(string filename)
{
	ifstream fin(filename);
	fin >> Uset;
}

Set::Set(int size)
{
	this->size = size;
	Vs = nullptr;

}

Set::Set()
{
	this->size = 0;
	this->Vs = nullptr;
}

Set::Set(ifstream& fin)
{

	fin >> (*this);
}

Set::Set(const Set& S)
{
	Deepcopy(S);
}

const Set& Set::operator=(const Set& S)
{
	Deallocate();
	Deepcopy(S);
	return *this;
}

const Set Set:: operator+(const Set& S)const
{
	Set R(0);
	for (int i = 0; i < this->size; i++)
	{
		R.insertatend(Vs[i]);
	}
	for (int i = 0; i < S.size; i++)
	{
		if (!R.belongTo(S.Vs[i]))
			R.insertatend(S.Vs[i]);
	}
	return R;
}

const Set Set::operator-(const Set& S)const
{
	Set R(0);

	for (int i = 0; i < this->size; i++)
	{
		if (!S.belongTo(Vs[i]))
		{
			if (!R.belongTo(Vs[i]))
				R.insertatend(Vs[i]);
		}
	}

	return R;
}

const Set Set::operator^(const Set& S)const
{
	Set R(0);
	if (this->size > S.size)
	{
		for (int i = 0; i < this->size; i++)
		{
			if (S.belongTo(Vs[i]))
			{
				if (!R.belongTo(Vs[i]))
					R.insertatend(Vs[i]);
			}
		}
	}
	else
	{
		for (int i = 0; i < S.size; i++)
		{
			if (R.belongTo(S.Vs[i]))
			{
				if (!R.belongTo(S.Vs[i]))
					R.insertatend(S.Vs[i]);
			}
		}
	}
	return R;


}

bool Set::operator|(const Set& S)const
{
	Set R = (*this) ^ S;
	if (R.size == 0)
		return true;
	else
		return false;
}

const Set& Set::operator+=(int num)
{
	if (!this->belongTo(num))
		this->insertatend(num);
	else
		cout << num << " is already present" << endl;
	return *this;
}

const Set& Set::operator-=(int num)
{
	if (this->belongTo(num))
		this->removeatend(num);
	else
		cout << num << "is not present";

	return *this;
}

const Set& Set::operator+=(const Set& S)
{
	*this = *this + S;
	return *this;
}

const Set& Set::operator-=(const Set& S)
{
	*this = *this - S;
	return *this;
}

bool Set::operator==(const Set& S)const
{
	if (this->size != S.size)
		return false;
	for (int i = 0; i < size; i++)
	{
		if (!S.belongTo(Vs[i]))
			return false;
	}
	return true;
}

const Set& Set::operator~()
{
	Uset.LoadUSet("U.txt");
	*this = Uset - *this;
	return *this;
}

int Set::operator[](int i) const
{
	if (i > 0 && i < size)
		return Vs[i];
	else
	{
		cout << "Out of range (returning 1 element) " << endl;
		return Vs[0];
	}
}

int& Set::operator[](int i)
{
	if (i > 0 && i < size)
		return Vs[i];
	else
	{
		cout << "Out of range (returning 1 element)" << endl;
		return Vs[0];
	}
}


void Set::Loadpair(Pair* P, const Set& S) const
{
	int index = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < S.size; j++)
		{
			P[index].x = Vs[i];
			P[index++].y = S.Vs[j];
		}
	}
}

void Set::operator*(const Set& S) const
{
	Pair* P = new Pair[size * S.size];
	this->Loadpair(P, S);
	cout << "Cartesian product is: { ";
	for (int i = 0; i < size * S.size; i++)
	{
		if (i != size * S.size - 1)
			cout << "( " << P[i].x << ", " << P[i].y << " ), ";
		else
			cout << "( " << P[i].x << ", " << P[i].y << " ) }";
	}
}




