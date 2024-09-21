#pragma once
#include<iostream>
using namespace std;




class QuadriticHash
{
	struct Data
	{
		int key;
		string data;
		bool empty;
		bool isdelete;

		Data(int k = 0, bool e = true, bool d = false)
		{
			empty = true;
			isdelete = false;
			key = 0;
		}
	};

	Data* HashTable;
	int size;
	int count;

	int searchindex(int key)
	{
		int i = 0;
		int val = HashFunction(key);
		int count = 0;
		while (count != size)
		{
			if (HashTable[val].key == key)
				return val;
			else
			{
				if (HashTable[val].empty == true)
					if (HashTable[val].isdelete == false)
						break;
				val = (HashFunction(key) + (i * i)) % size;
				i++;
				count++;
			}
		}
		return -1;
	}

	int HashFunction(int key)
	{
		return key % size;
	}

public:
	QuadriticHash(int size)
	{
		HashTable = new Data[size]{};
		this->size = size;
		count = 0;
	}

	bool IsFull()
	{
		return count == size;
	}

	bool IsEmpty()
	{
		for (int i = 0; i < size; i++)
		{
			if (HashTable[i].empty == false)
				return false;

		}
		return true;
	}

	bool searchval(int key)
	{
		int i = 0;
		int val = HashFunction(key);
		int count = 0;
		while (count != size)
		{
			if (HashTable[val].key == key)
				return true;
			else
			{
				if (HashTable[val].empty == true)
					if (HashTable[val].isdelete == false)
						break;
				val = (HashFunction(key) + (i * i)) % size;
				i++;
				count++;
			}
		}
		return false;
	}

	void Delete(int key)
	{
		int val = HashFunction(key);
		auto D = searchval(key);
		int index = searchindex(key);
		if (D == true)
		{
			HashTable[index].key = 0;
			HashTable[index].isdelete = true;
			HashTable[index].empty = true;
			HashTable[index].data.clear();
			count--;
		}

	}

	void insert(int key, string data)
	{

		int val = HashFunction(key);
		int i = 1;
		if (IsFull())
			return;
		while (true)
		{
			if (HashTable[val].key == key || HashTable[val].empty)
			{
				HashTable[val].key = key;
				HashTable[val].data = data;
				HashTable[val].empty = false;
				HashTable[val].isdelete = false;
				break;
			}
			else
			{
				val = (HashFunction(key) + (i * i)) % size;
				i++;
			}
		}
		count++;
	}

	void PrintTable()
	{
		cout << "Key\tData" << endl;
		for (int i = 0; i < size; i++)
		{
			cout << HashTable[i].key << "\t" << HashTable[i].data << endl;
		}
	}
};