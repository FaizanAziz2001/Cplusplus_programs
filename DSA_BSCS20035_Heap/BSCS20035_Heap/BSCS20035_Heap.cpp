#include <vector>
#include <iostream>
#include"Heap.h"
#include"MaxHeap.h"
using namespace std;

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

void HeapUp(vector<int>& H, int i)
{
	if (Parent(i) >= 0 && H[i] < H[Parent(i)])
	{
		swap(H[i], H[Parent(i)]);
		HeapUp(H, Parent(i));
	}
}

void HeapDown(vector<int>& H, int i)
{
	int l = Left(i);
	int r = Right(i);
	int min = i;

	if (l >= H.size() && r >= H.size())
		return;


	if (l >= H.size() && r < H.size())
		min = r;
	else if (r >= H.size() && l < H.size())
		min = l;
	else if (H[l] < H[r])
		min = l;
	else if (H[r] < H[l])
		min = r;

	swap(H[i], H[min]);
	HeapDown(H, min);
}

void Insert(vector<int>& H, int val)
{
	H.push_back(val);
	HeapUp(H, H.size() - 1);
}

void BuildHeap(vector<int>& H)
{
	for (int i = 0; i < H.size(); i++)
	{
		HeapUp(H, i);
	}
}

int Extraction(vector<int>& H)
{
	int extract = H.front();
	swap(H[0], H[H.size() - 1]);
	H.pop_back();
	HeapDown(H, 0);
	return extract;

}

void Sort(vector<int>& H)
{
	auto C = H;
	BuildHeap(C);
	H.clear();
	while (C.size() != 0)
	{
		H.push_back(Extraction(C));
	}

}

//int main()
//{
//	vector<int> v;
//	/*Insert(v,5);
//	Insert(v, 55);
//	Insert(v, 35);
//	Insert(v, 85);
//	Insert(v, 9);
//	Insert(v, 25);*/
//	v.push_back(5);
//	v.push_back(45);
//	v.push_back(25);
//	v.push_back(58);
//	v.push_back(15);
//	v.push_back(75);
//	Sort(v);
//
//}

int main()
{


	MaxHeap<int> S;
	S.Insert(55);
	S.Insert(155);
	S.Insert(5);
	S.Insert(555);
	S.Insert(755);
	cout << S;

}


