//Vector implementation
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <chrono>
using namespace std;

int N_vector = 0;

template<typename Type>

class Vector
{
private:
	Type* Ds;
	int size;
	int capacity;

public:
	Vector()
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

			capacity = capacity * 2;					//double the capacity of dynamic array if size becomes equal to capacity
			Type* heap = new Type[capacity];
			for (int i = 0; i < size; i++)
			{

				heap[i] = Ds[i];
				N_vector++;
			}
			delete[] Ds;
			Ds = heap;

		}
		N_vector++;
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

	friend ostream& operator<<(ostream& cout, Vector<Type>& DA)
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




//ArrayList implementation
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



//AutoGrowingArray implementation

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

		Type* heap = new Type[size + 1];
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


//main.cpp


#include"vector.h"
#include"ArrayList.h"
#include"AutoGrowingArray.h"
#include<string>
using namespace std;



void Generate_file(string fname, int size)
{
	srand(time(0));		// Generate a file of 1 mb
	ofstream fout(fname);
	for (int i = 0; i < size * 1024 * 1024; i++)
	{
		fout << rand() % 1000 << endl;
	}
}


void task1(int size)
{
	Vector<int> data;
	ofstream fout("OutputVector.txt");
	auto start = chrono::steady_clock::now();
	data.Read_file("Ds.txt");
	auto stop = chrono::steady_clock::now();

	auto diff = stop - start;
	/*cout << data << endl;*/
	cout << "For a " << size << "MB file: " << endl;
	cout << "Time taken: " << chrono::duration <double, milli>(diff).count() / 1000 << " s" << endl;
	cout << "Time taken: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;
	fout << "Time taken: " << chrono::duration <double, milli>(diff).count() / 1000 << " s" << endl;
	fout << "Time taken: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;
	fout << "For a " << size << "MB file: " << endl;
	cout << "Number of operations: " << N_vector << endl;
	fout << "Number of operations: " << N_vector << endl;
}

void task2(int size)
{
	ArrayList<int> data;
	ofstream fout("OutputArrayList.txt");
	auto start = chrono::steady_clock::now();
	data.Read_file("Ds.txt");
	auto stop = chrono::steady_clock::now();


	auto diff = stop - start;
	/*cout << data << endl;*/
	cout << "For a " << size << "MB file: " << endl;
	cout << "Time taken: " << chrono::duration <double, milli>(diff).count() / 1000 << " s" << endl;
	cout << "Time taken: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;
	fout << "Time taken: " << chrono::duration <double, milli>(diff).count() / 1000 << " s" << endl;
	fout << "Time taken: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;
	fout << "For a " << size << "MB file: " << endl;
	cout << "Number of operations: " << N_arraylist << endl;
	fout << "Number of operations: " << N_arraylist << endl;
}

void task3(int size)
{
	AutoGrowingArray<int> data;
	ofstream fout("OutputGA.txt");
	auto start = chrono::steady_clock::now();
	data.Read_file("Ds.txt");
	auto stop = chrono::steady_clock::now();


	auto diff = stop - start;
	/*cout << data << endl;*/
	cout << "For a " << size << "MB file: " << endl;
	cout << "Time taken: " << chrono::duration <double, milli>(diff).count() / 1000 << " s" << endl;
	cout << "Time taken: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;
	fout << "Time taken: " << chrono::duration <double, milli>(diff).count() / 1000 << " s" << endl;
	fout << "Time taken: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;
	fout << "For a " << size << "MB file: " << endl;
	cout << "Number of operations: " << N_grow << endl;

}

int main()
{
	int choice;
	int size = 2;
	cout << "1. Vector \n"
		<< "2. ArrayList \n"
		<< "3. Growable array" << endl;
	cin >> choice;
	if (choice == 1)
		task1(size);
	else if (choice == 2)
		task2(size);
	else if (choice == 3)
		task3(size);

	//Generate_file("Ds.txt", size);
	return 0;

}

