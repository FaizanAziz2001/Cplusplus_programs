#pragma once
#include<iostream>
using namespace std; 

template <typename Type>

class S_Stack
{
	int capacity;
	int size;
	Type* Ds;

public:
	S_Stack(int c = 1)
	{
		capacity = c;
		size = 0;
		Ds = new Type[capacity];
	}

	S_Stack(const S_Stack& S)
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

	bool Size()
	{
		return size;
	}

	bool push(Type& value)
	{
		if (size == capacity)
			return false;
		Ds[size] = value;
		size++;
		return true;
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
		value = Ds[size-1];
		return true;
		
	}

	friend ostream& operator<<(ostream& cout, S_Stack<Type> S)
	{
		for (int i = 0; i < S.size; i++)
		{
			cout << S.Ds[i] << " ";
		}

		cout << endl;
		return cout;
	}
};
