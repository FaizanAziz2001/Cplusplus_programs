#include <iostream>
#include<vector>
using namespace std;

struct mult
{
	int val;
	int count;
};

//BSCS20027
#pragma region

//i
int recursive_fib(int num)
{
	if (num == 0 || num == 1)
		return num;

	return recursive_fib(num - 2) + recursive_fib(num - 1);
}
//ii
int iterative_fib(int num)
{
	int x = 0, y = 1, z = 0;
	while (y < num)
	{
		z = x + y;
		x = y;
		y = z;
	}

	return z;

}

//ii
void q3()
{
	/*
	In recursive code, we are calculating the same number multiple times which results in greater complexity, i.e F(2) + F(3), in F(3) call F(2) will be calulated again resulting in redundancy.
	In iterative,we calculate for fixed iterations which reduces number of operations required.*/
}

//iv
int fast_fib(vector<int>& data, int num)
{
	if (data[num] != -1)
		return data[num];
	data[num] = fast_fib(data, num - 1) + fast_fib(data, num - 2);
	return data[num];

}

int memoization_fib(int num)
{
	vector<int> data(num + 1, { -1 });
	data[0] = 0;
	data[1] = 1;
	return fast_fib(data, num);
}
#pragma endregion Q1

//BSCS20027
#pragma region

//i
int recursive_trisum(int num)
{
	if (num <= 2)
		return num;
	return recursive_trisum(num - 1) + recursive_trisum(num - 2) + recursive_trisum(num - 3);
}

void trisum_generator(int num)
{
	if (num == 0)
		return;
	trisum_generator(num - 1);
	cout << recursive_trisum(num) << " ";

}

//ii
int fast_trisum(vector<int>& data, int num)
{
	if (data[num] != -1)
		return data[num];
	return data[num] = fast_trisum(data, num - 1) + fast_trisum(data, num - 2) + fast_trisum(data, num - 3);
}

int memoization_trisum(int num)
{
	vector<int> data(num + 2, { -1 });
	data[0] = 0, data[1] = 1, data[2] = 2;
	return fast_trisum(data, num);
}

#pragma endregion Q2

//BSCS20027
#pragma region
//i
int combination(int num, int r)
{
	if (num < r)
		return -1;

	if (r == 0 || num == r)
		return 1;
	return combination(num - 1, r - 1) + combination(num - 1, r);
}

//ii
int permutation(int num, int r)
{
	if (num < r)
		return -1;

	if (r == 1)
		return num;
	else if (r == 0)
		return 1;

	return num * permutation(num - 1, r - 1);
}
#pragma endregion Q3

//BSCS20035
#pragma region
//i
int ADD(int x, int y)
{
	return x + y;
}

int MULT_recursion(int x, int y, int sum)
{
	if (y == 0)
		return sum;
	sum = ADD(x, sum);
	return MULT_recursion(x, y - 1, sum);
}

int MULT(int x, int y)
{
	return MULT_recursion(x, y, 0);
}

//ii
int Fast_Mult_recursion(vector<mult>& data, int x, int y, int& sum)
{
	if (y == 0)
		return sum;
	int index = log2(y);
	sum = ADD(sum, data[index].val);
	return Fast_Mult_recursion(data, x, y - data[index].count, sum);
}

int Fast_Mult(int x, int y)
{
	int size = log2(y) + 1;
	vector<mult> data(size);

	int total = x;
	int count = 1, index = 0;

	data[index].count = 1;
	data[index++].val = x;

	while (count + count <= y)			//Log(y)
	{
		total += total;
		count += count;
		data[index].count = count;
		data[index++].val = total;
	}

	index--;
	return Fast_Mult_recursion(data, x, y - data[index].count, data[size - 1].val); //log(y)
	//Logy + Logy = O(Logy)
}
#pragma endregion Q4

//BSCS20035
#pragma region

//i
int mod(int x, int y)
{
	if (x < y)
		return x;

	return mod(x - y, y);		//O(x/y)
}

//ii
int Fast_mod_recursion(int& A, int B,int Z)
{
	if (B + B <= A)
		Fast_mod_recursion(A, B + B, Z);
	if (B<= A)
		A = A - B;
	else if (A < Z)
		return A;
}

int Fast_mod(int A, int B)
{
	if (A < B)
		return A;
	return Fast_mod_recursion(A, B, A);
}


#pragma endregion Q5

//BSCS20035
#pragma region
//i
bool bubbleup(int data[], int size, int i, bool& swapflag)
{

	if (i + 1 == size)
		return false;
	if (data[i] > data[i + 1])
	{
		swap(data[i], data[i + 1]);
		swapflag = true;
	}
	bubbleup(data, size, ++i, swapflag);
	return swapflag;

}

void BubbleSort_recursion(int data[], int size)
{
	bool swapflag = false;
	if (bubbleup(data, size, 0, swapflag) == true)
	{
		BubbleSort_recursion(data, size);
	}
}

//ii
bool bubbleup_vector(vector<int>& data, int i, bool& swapflag)
{

	if (i + 1 == data.size())
		return false;
	if (data[i] > data[i + 1])
	{
		swap(data[i], data[i + 1]);
		swapflag = true;
	}
	bubbleup_vector(data, ++i, swapflag);
	return swapflag;

}

void BubbleSort_vector(vector<int>& data)
{
	bool swapflag = false;
	if (bubbleup_vector(data, 0, swapflag) == true)
	{
		BubbleSort_vector(data);
	}
}
#pragma endregion Q6

//BSCS20035
#pragma region
//i
int RangeSearch(int data[], int size, int si, int ei, int min_index)
{
	if (si == ei)
		return min_index;

	if (data[si] < data[min_index])
		min_index = si;
	return RangeSearch(data, size, si + 1, ei, min_index);

}

//ii
void Selection_Sort(int data[], int size, int si)
{
	if (si == size - 1)
		return;
	int index = RangeSearch(data, size, si, size, si);
	swap(data[index], data[si]);
	Selection_Sort(data, size, ++si);
}
#pragma endregion Q7

//BSCS20035
#pragma region 

void insertion_in_sortedarray(int data[], int size, int j, int key)
{

	if (j < 0 || data[j] <= key)
	{
		data[j + 1] = key;
		return;
	}

	data[j + 1] = data[j];
	insertion_in_sortedarray(data, size, j - 1, key);
}

void insertion_sort(int data[], int size, int si)
{
	if (si == size)
		return;
	insertion_in_sortedarray(data, size, si - 1, data[si]);

	insertion_sort(data, size, si + 1);
}

#pragma endregion Q8



int main()
{
	/*vector<int> v{ 1, 5, 8, -3, 22, 66, 43, 2 };
	int data[8] = { 1, 5, 8, -3, 55, 66, 43, -10 };

	BubbleSort_recursion(data, 8);

	BubbleSort_vector(v);

	Selection_Sort(data, 8, 0);

	insertion_sort(data, 8, 1);


	for (int i = 0; i < 8; i++)
		cout << data[i] << " ";*/

	cout << Fast_mod(25,25);

	return 0;
}
