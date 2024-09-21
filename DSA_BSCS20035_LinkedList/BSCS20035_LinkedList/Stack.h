#pragma once
#include"LinkedList.h"
template<typename T>
class Stack
{
private:
	LinkedList<T> S;
public:
	Stack()
	{
		
	}

	void Push(T V)
	{
		S.InsertAtTail(V);
	}

	T Pop()
	{
		return S.RemoveTail();
	}

	bool IsEmpty()
	{
		return (S.IsEmpty());
	}
};