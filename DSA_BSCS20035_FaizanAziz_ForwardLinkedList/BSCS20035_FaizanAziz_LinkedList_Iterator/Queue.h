#pragma once
#include"ForwardList.h"
template<typename T>
class Queue
{
private:
	forwardlist<T> Q;
public:
	Queue()
	{

	}

	void Enqueue(T val)
	{
		Q.InsertAtEnd(val);
	}

	T Dequeue()
	{
		return Q.RemoveFront();
	}

	bool IsEmpty()
	{
		return Q.IsEmpty();
	}

	T Front()
	{
		return Q.GetTail();
	}

	T Back()
	{
		return Q.GetFront();
	}
};

