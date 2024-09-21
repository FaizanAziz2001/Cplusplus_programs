#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <chrono>
using namespace std;

int N_arraylist = 0;
template<typename Type>

class ArrayList
{
private:
	Type* Ds;
	int size;
	int capacity;

public:
	ArrayList()
	{
		size = 0;
		capacity = 2;
		Ds = new Type[capacity];
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
		if (size == capacity)
		{
			capacity = capacity * 1.5;					//double the capacity of dynamic array if size becomes equal to capacity
			Type* heap = new Type[capacity];
			for (int i = 0; i < size; i++)
			{
				N_arraylist++;
				heap[i] = Ds[i];
			}
			delete[] Ds;
			Ds = heap;
		}

		N_arraylist++;
		Ds[size] = data;
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

	friend ostream& operator<<(ostream& cout, ArrayList<Type>& DA)
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
