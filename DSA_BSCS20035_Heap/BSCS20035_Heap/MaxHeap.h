#pragma once
#include<iostream>
using namespace std;

template<typename T>
class MaxHeap
{
	vector<T> heap;

	int Left(int i)
	{
		return 2 * i + 1;
	}
	int Right(int i)
	{
		return 2 * i + 2;
	}

	int Parent(int i)
	{
		return (i - 1) / 2;
	}

	void HeapifyUp(int i)
	{
		if (Parent(i) >= 0 && heap[i] > heap[Parent(i)])
		{
			swap(heap[i], heap[Parent(i)]);
			HeapifyUp(Parent(i));
		}
	}

	void HeapifyDown(int i)
	{
		int max = i;
		int L = Left(i);
		int R = Right(i);

		if (L >= heap.size() && R >= heap.size())
			return;

		if (L >= heap.size() && R < heap.size())
			max = R;
		else if (R >= heap.size() && L < heap.size())
			max = L;
		else if (heap[L] < heap[R])
			max= R;
		else
			min = L;

		swap(heap[min], heap[i]);
		HeapifyDown(min);

	}

	void BuildHeap()
	{
		for (int i = 0; i < heap.size(); i++)
		{
			HeapifyUp(i);
		}
	}

public:
	MaxHeap()
	{

	}

	MaxHeap(vector<T> V)
	{
		heap = V;
		BuildHeap();
	}

	void Insert(T val)
	{
		heap.push_back(val);
		HeapifyUp(heap.size() - 1);
	}

	
	T Extract()
	{
		T val;
		if (heap.size() == 1)
		{
			val = heap[0];
		}
		else if (heap.size() > 2)
		{
			val = heap[0];
			swap(heap[0], heap[heap.size() - 1]);
		}
		else
			val = heap[1];
		heap.pop_back();
		HeapifyDown(0);
		return val;
	}

	void Sort(vector<T>& v)
	{
		MaxHeap temp(v);
		v.clear();
		while (temp.heap.size() != 0)
		{
			v.push_back(temp.Extract());
		}
	}
	friend ostream& operator << (ostream& cout, MaxHeap<T> v)
	{
		for (int i = 0; i < v.heap.size(); i++)
		{
			cout << v.heap[i] << " ";
		}

		return cout;
	}


};