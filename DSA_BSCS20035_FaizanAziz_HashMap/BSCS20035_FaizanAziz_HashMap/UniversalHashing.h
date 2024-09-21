#pragma once
#include<iostream>
using namespace std;


class Unihash
{
	struct Data
	{
		int key;
		string data;
	};
	int size,u,b;
	Data* Hashtable;
	int** matrix;

	string decimal_to_binary(int in)
	{
		string temp = "";
		string result = "";
		while (in)
		{
			temp += ('0' + in % 2);
			in /= 2;
		}

		result.append(u - temp.size(), '0');
		for (int i = temp.size() - 1; i >= 0; i--)
		{
			result += temp[i];
		}
		return result;
	}

	int binary_to_decimal(string in)
	{
		int result = 0;
		for (int i = 0; i < in.size(); i++)
			result = result * 2 + in[i] - '0';
		return result;
	}

	void GenerateMatrix()
	{
		u = 4 * 8;
		b = log2(size);

		matrix = new int* [b];

		for (int i = 0; i < b; i++)
		{
			matrix[i] = new int[u];
		}

		for (int i = 0; i < b; i++)
		{
			for (int k = 0; k < u; k++)
			{
				matrix[i][k] = rand() % 2;
			}
		}
	}

	bool searchindex(int key)
	{
		int val = HashFunction(key);
		if (Hashtable[val].key == key)
			return true;
		return false;
	}

public:
	Unihash(int size)
	{
		Hashtable = new Data[size]{};
		this->size = size;
		srand(time(NULL));
		GenerateMatrix();

	}

	int HashFunction(int key)
	{
		string input = decimal_to_binary(key);
		string output;

		int sum = 0;
		int index;
		for (int i = 0; i < b; ++i)
		{
			for (int k = 0; k < u; ++k)
			{
				sum = (sum + matrix[i][k] * input[k]);
			}
			output.push_back((sum % 2) + 48);
			sum = 0;
		}

		index = binary_to_decimal(output);
		return index;
	}

	Data& Search(int key)
	{
		int val = HashFunction(key);
		return Hashtable[val];
	}

	void Delete(int key)
	{
		int val = HashFunction(key);
		if (searchindex(key))
		{
			Hashtable[val].data.clear();
			Hashtable[val].key = 0;
		}
	}

	void insert(int key, string data)
	{
		int val = HashFunction(key);
		Hashtable[val].key = key;
		Hashtable[val].data = data;
	}

	void Print()
	{
		for (int i = 0; i < size; i++)
		{
			cout << Hashtable[i].key << "\t" << Hashtable[i].data << endl;
		}
	}
};