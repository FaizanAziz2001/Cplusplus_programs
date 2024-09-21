#pragma once
#include<iostream>
using namespace std;

template<typename Type>
class S_Queue
{
	int front;
	int rear;
	int size;
	int capacity;
	Type* Ds;
public:
	S_Queue(int c = 1)
	{
		capacity = c;
		front = rear=size=0;
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

	bool Enqueue(Type val)
	{
		if (Full())
			return false;

		Ds[rear] = val;
		size++;
		rear = (rear + 1) %capacity;
		return true;
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
