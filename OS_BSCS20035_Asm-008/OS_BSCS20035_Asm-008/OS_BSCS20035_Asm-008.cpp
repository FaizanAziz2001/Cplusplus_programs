
#include <iostream>
#include<vector>
#include <bitset>
using namespace std;

#define Accessbits 128
#define table_row 3

struct Page
{
	int id;
	bitset<1> p;
	bitset<1> d;
	int a;

	Page(int id = -1, int present = 0, int dirty = 0, int access = 1)
	{
		this->id = id;
		p |= present;
		d |= dirty;
		a = access;
	}

	void print()
	{
		cout << id;
	}
};

int CountTrailingZeros(int n)
{
	// declare bitset of 64 bits
	bitset<Accessbits> bit;
	// set bitset with the value
	bit |= n;
	int zero = 0;
	for (int i = 0; i < Accessbits; i++) {
		if (bit[i] == 0)
			zero++;
		else
			break;
	}
	return zero;
}

void print_Table(vector<vector<Page>>& Table)
{
	for (int i = 0; i < Table.size(); i++)
	{
		for (int j = 0; j < Table[i].size(); j++)
		{
			Table[i][j].print();
			cout << " ";
		}
		cout << endl;
	}
}

bool find_in_table(int col, int val, vector<vector<Page>>& Table)
{
	for (int i = 0; i < Table.size(); i++)
	{
		if (Table[i][col].id == val - 48)
			return true;
	}
	return false;
}

int find_in_table_index(int col, int val, vector<vector<Page>>& Table)
{
	for (int i = 0; i < Table.size(); i++)
	{
		if (Table[i][col].id == val - 48)
			return i;
	}
	return -1;
}

void update_values(int col, vector<vector<Page>>& Table)
{
	for (int i = 0; i < Table.size(); i++)
	{
		if (Table[i][col].p == 1)
		{
			Table[i][col].a = Table[i][col].a << 1;
		}
	}
}

void copy_values(int col, vector<vector<Page>>& Table)
{
	if (col == 0)
		return;
	for (int i = 0; i < Table.size(); i++)
	{
		Table[i][col] = Table[i][col - 1];
	}
}

int find_recent(int col, vector<vector<Page>>& Table)
{
	int max_index = 0;
	int max_zeroes = 0;
	for (int i = 0; i < Table.size(); i++)
	{
		int zeroes = CountTrailingZeros(Table[i][col].a);
		if (zeroes > max_zeroes)
		{
			max_zeroes = zeroes;
			max_index = i;
		}
	}
	return max_index;
}

bool empty(int col, vector<vector<Page>>& Table)
{
	for (int i = 0; i < Table.size(); i++)
	{
		if (Table[i][col].id == -1)
			return true;
	}
	return false;
}

int main()
{
	string ref = "701203042303212";												//reference string
	vector <vector<Page>> Table(table_row, vector<Page>(ref.length()));

	int iterator = 0;
	for (int i = 0; i < Table[0].size(); i++)
	{
		copy_values(i, Table);
		if (empty(i, Table))
		{
			Table[iterator][i].id = ref[i] - 48;								//fill the initial page stream
			Table[iterator][i].p = 1;
			Table[iterator][i].a = 1;

			iterator++;
			if (iterator % Table.size() == 0)
				iterator = 0;

			cout << "Page Fault" << endl;
		}
		else if (find_in_table(i, ref[i], Table) == false)
		{
			int index = find_recent(i, Table);									//find the least recently page and replace it
			Table[index][i].id = ref[i] - 48;
			Table[index][i].p = 1;
			Table[index][i].a = 1;
			cout << "Page Fault" << endl;
		}
		else
		{
			int index = find_in_table_index(i, ref[i], Table);
			Table[index][i].a = 1;												//if the page already exists , recent its access bit
			cout << "Page Hit" << endl;
		}
		update_values(i, Table);
	}
	cout << endl;
	print_Table(Table);

}

