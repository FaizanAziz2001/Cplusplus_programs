#pragma once
#include<iostream>
#include<list>
using namespace std;

static const int HashGroups = 10;

class ChainHash {
	
	list<pair<int, string>> HashTable[HashGroups];

public:
	
	bool isEmpty()
	{
		for (auto t : HashTable)
		{
			if (t.size() != 0)
				return false;
		}
		return true;
	}

	int HashFunction(int key)
	{
		return key % HashGroups;
	}

	void Insert(int key,string val)
	{
		int Hashval = HashFunction(key);
		bool isExist = false;

		for (auto t : HashTable[Hashval])
		{
			if (t.first == key)
			{
				isExist = true;
				t.second = val;
				cout << "Value has been overwritten" << endl;
				break;
			}
		}

		if (!isExist)
		{
			HashTable[Hashval].emplace_back(key, val);
			cout << "Value has been inserted" << endl;
		}
	}

	void Remove(int key)
	{
		int Hashval = HashFunction(key);
		bool isExist = false;

		for(auto t=HashTable[Hashval].begin();t!=HashTable[Hashval].end();t++)
		{
			if (t->first == key)
			{
				isExist = true;
				HashTable[Hashval].erase(t);
				cout << "Value has been removed" << endl;
				break;
			}
		}

		if (!isExist)
		{
			cout << "Value does not exist" << endl;
		}
	}

	void Print()
	{
		for (auto t : HashTable)
		{
			if (t.size() != 0)
			{
				for (auto i : t)
				{
					cout << "Key: " << i.first << "\t\tValue: " << i.second << endl;
				}
			}
		}
	}
};
