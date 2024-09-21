#pragma once
#include"ForwardList.h"
template<typename T>
class Stack
{
private:
	forwardlist<T> S;
public:
	Stack()
	{

	}

	void Push(T V)
	{
		S.InsertAtBack(V);
	}

	T Pop()
	{
		return S.RemoveFront();
	}

	bool IsEmpty()
	{
		return (S.IsEmpty());
	}

	T Front()
	{
		return S.GetTail();
	}

	T Back()
	{
		return S.GetFront();
	}
};
