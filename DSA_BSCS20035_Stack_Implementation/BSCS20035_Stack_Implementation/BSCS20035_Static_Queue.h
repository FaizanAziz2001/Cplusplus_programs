#pragma once

#include<iostream>
using namespace std;

template<typename Type>
class Queue
{
	int front;
	int rear;
	int capacity;
	Type* Ds;

public:

	Queue(int c = 1)
	{
		capacity = c;
		front = -1;
		rear = -1;
		Ds = new Type[capacity];
	}

	bool IsEmpty()
	{
		return (rear == -1 && front == -1);
	}

	bool IsFull()
	{
		return (rear+1)%capacity == front;
	}

	bool Enqueue(Type& x)
	{

		if (Full())
			return false;
		else if (Empty())
		{
			front = 0;
			rear = 0;
		}
		else if (rear == capacity-1 && front != 0)
			rear = 0;
		else
			rear++;


		Ds[rear] = x;
		return true;
	}

	bool Dequeue()
	{
		if (Empty())
			return false;
		else if (front == capacity-1 && rear < front)
			front = 0;
		else if (front == rear)
		{
			front = -1, rear = -1;
			return true;
		}
		else
			front++;
		
		return true;
	}

	bool Front(Type& value)
	{
		if (Empty())
			return false;
		value = Ds[front];
		return true;

	}

	bool Back(Type& value)
	{
		if (Empty())
			return false;
		value = Ds[rear];
		return true;

	}

	friend ostream& operator<<(ostream& cout, Queue<Type> Q)
	{
		for (int i = 0; i < Q.capacity; i++)
		{
			cout << Q.Ds[i] << " ";
		}

		cout << endl;
		return cout;
	}
};
