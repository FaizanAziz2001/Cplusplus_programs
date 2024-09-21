#pragma once

#pragma once
#include<iostream>
using namespace std;

template<typename Type>
class D_Queue
{
	int front;
	int rear;
	int size;
	int capacity;
	Type* Ds;
public:
	D_Queue(int c = 2)
	{
		capacity = c;
		front = rear = size = 0;
		Ds = new Type[capacity];
	}

	bool Empty()
	{
		return size == 0;
	}

	Type Front()
	{
		if (size == 0)
			return false;
		return Ds[front];
	}

	bool Full()
	{
		return size == capacity;
	}

	bool Size()
	{
		return size;
	}

	void Enqueue(Type val)
	{
		if (Full())
		{
			capacity = capacity * 2;
			Type* heap = new Type[capacity];
			for (int c = 1, i = front; c <= size; c++, i++)
			{
				if (i == size)
					i = 0;
				heap[c - 1] = Ds[i];
			}
			front = 0;
			rear = size;
			delete [] Ds;
			Ds = heap;
		}

		Ds[rear] = val;
		size++;
		rear = (rear + 1) % capacity;
	}

	bool Dequeue()
	{
		if (Empty())
			return false;
		front = (front + 1) % capacity;
		size--;
		return true;
	}
};

