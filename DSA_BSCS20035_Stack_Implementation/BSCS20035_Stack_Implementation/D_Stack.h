#pragma once
#pragma once
#include<iostream>
using namespace std;

template <typename Type>

class D_Stack
{
	int capacity;
	int size;
	Type* Ds;

public:
	D_Stack(int c = 2)
	{
		capacity = c;
		size = 0;
		Ds = new Type[capacity];
	}

	D_Stack(const D_Stack& S)
	{
		capacity = S.capacity;
		size = S.size;
		Ds = new Type[capacity];
		for (int i = 0; i < size; i++)
		{
			Ds[i] = S.Ds[i];
		}
	}

	bool empty()
	{
		return size == 0;
	}

	bool Full()
	{
		if (size == capacity)
			return true;
		return false;
	}

	void push(Type& value)
	{
		if (size == capacity)
		{
			capacity = capacity * 2;
			Type* Heap = new Type[capacity];
			for (int i = 0; i < size; i++)
			{
				Heap[i] = Ds[i];
			}
			delete Ds[];
			Ds = Heap;
		}

		Ds[size] = value;
		size++;

	}

	bool Size()
	{
		return size;
	}

	bool pop()
	{
		if (size == 0)
			return false;
		size--;
		return true;
	}

	bool top(Type& value)
	{
		if (size == 0)
			return false;
		value = Ds[size - 1];
		return true;

	}

	friend ostream& operator<<(ostream& cout, D_Stack<Type> S)
	{
		for (int i = 0; i < S.size; i++)
		{
			cout << S.Ds[i] << " ";
		}

		cout << endl;
		return cout;
	}
};
