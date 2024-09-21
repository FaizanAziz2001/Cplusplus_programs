#pragma once
#include"LinkedList.h"
template<typename T>
class Queue
{
private:
	LinkedList<T> Q;
public:
	Queue()
	{

	}

	void Enqueue(T val)
	{
		Q.InsertAtTail(val);
	}

	T Dequeue()
	{
		return Q.RemoveFront();
	}

	bool IsEmpty()
	{
		return Q.IsEmpty();
	}
};
