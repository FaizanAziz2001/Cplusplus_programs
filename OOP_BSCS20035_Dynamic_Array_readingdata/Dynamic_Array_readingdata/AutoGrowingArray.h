#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <chrono>
using namespace std;

int N_grow = 0;
template<typename Type>

class AutoGrowingArray
{
private:
	Type* Ds;
	int size;

public:
	AutoGrowingArray()
	{
		size = 0;
		Ds = new Type[size];
	}

	void Read_file(string fname)
	{
		ifstream fin(fname);	//Read the file
		while (fin)
		{
			Type v;
			fin >> v;
			if (fin)
				push_back(v);
		}
	}

	void push_back(Type data)
	{

		Type* heap = new Type[size+1];
		for (int i = 0; i < size; i++)
		{
			N_grow++;
			heap[i] = Ds[i];
		}
		
		N_grow++;
		heap[size] = data;
		delete[] Ds;
		Ds = heap;
		size++;
	}

	Type operator[](int i) const
	{
		return Ds[i];
	}

	Type& operator[](int i)
	{
		return Ds[i];
	}

	friend ostream& operator<<(ostream& cout, AutoGrowingArray<Type>& DA)
	{
		cout << "{ ";			//operator overloading to print dynamic array
		for (int i = 0; i < DA.size; i++)
		{
			cout << DA.Ds[i] << " ";
		}
		cout << "}";
		return cout;
	}

};