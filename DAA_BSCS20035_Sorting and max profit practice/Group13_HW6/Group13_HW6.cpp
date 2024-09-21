#include <iostream>
#include <vector>
#include<queue>
#include<fstream>
using namespace std;

struct Node
{
	int val;
	int i;
	int j;
};

struct Comparator {
	bool operator()(Node const& p1, Node const& p2)
	{
		return p1.val > p2.val;
	}
};

void print_vector(vector<int> data)
{
	for (int i = 0; i < data.size(); i++)
	{
		cout << data[i] << " ";
	}

	cout << endl;
}

void find_difference(vector<int>& nums, vector<int>& prices)
{
	for (int i = 0; i + 1 < prices.size(); i++)
	{
		nums.push_back(prices[i + 1] - prices[i]);
	}
}

//BSCS20035
#pragma region

void printmatrix(vector<vector<int>>& m)
{
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m[i].size(); j++)
		{
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}

vector <vector<int>> subarray(vector<vector<int>>& matrix, int ci, int size)
{
	vector < vector<int>> m(size, vector<int>(size));

	int mr = 0, mc = 0;

	for (int i = 1; i <= size; i++)
	{
		mc = 0;
		for (int j = 0; j <= size; j++)
		{
			if (j == ci)
				continue;
			m[mr][mc++] = matrix[i][j];
		}
		mr++;
	}

	return m;
}

int determinant(vector<vector<int>>& m, int size)
{

	if (size == 2)
	{
		return (m[0][0] * m[1][1]) - (m[0][1] * m[1][0]);
	}

	int product = 0;
	int sign = 1;

	for (int i = 0; i < size; i++)
	{
		vector<vector<int>>temp = subarray(m, i, size - 1);
		product += sign * m[0][i] * determinant(temp, size - 1);

		sign = -sign;

	}

	return product;
}

#pragma endregion Q1


//BSCS20035
#pragma region

//a
//if the given array is sorted descendingly, it will generate the maximum entropy which can be determined using n(n-1)/2 or NC2
//for 8 elements, maximum entorpy is (8-1)(8)/2 -> 28

//b
int merge(vector<int>& x, int si, int mid, int ei)
{
	int count = 0;
	int j = mid + 1;
	for (int i = si; i <= mid; i++)                             //O(N)
	{
		while (j <= ei && x[i] > x[j])
		{
			j++;
		}
		count += j - (mid + 1);
	}

	vector<int>res(ei - si + 1);
	int i = si;
	j = mid + 1;
	for (int k = 0; k < res.size(); k++)						//O(N)
	{
		if (i > mid)
			res[k] = x[j++];
		else if (j > ei)
			res[k] = x[i++];
		else if (x[i] < x[j])
			res[k] = x[i++];
		else
			res[k] = x[j++];
	}

	for (int i = 0; i < res.size(); i++)						//O(N)
	{
		x[i + si] = res[i];
	}

	return count;												//O(n)+O(n)+O(n)=O(n)
}

int entropy(vector<int>& x, int si, int ei)
{
	if (si >= ei)
		return 0;
	int count = 0;
	int mid = si + (ei - si) / 2;
	count += entropy(x, si, mid);
	count += entropy(x, mid + 1, ei);
	count += merge(x, si, mid, ei);
	return count;
}

#pragma endregion Q2

//BSCS20027
#pragma region
//1
void partition(vector<int>& data, int val)
{
	int si = 0;
	int i = 0;
	while (true)
	{
		while (i < data.size() && data[i] != val)
			i++;

		if (i >= data.size())
			break;
		swap(data[i++], data[si++]);
	}

	int smallpi = si, greaterpi = data.size() - 1;

	while (true)
	{
		while (smallpi < greaterpi && data[smallpi] < val)
			smallpi++;

		while (smallpi<greaterpi && data[greaterpi] >val)
			greaterpi--;

		if (smallpi >= greaterpi)
			break;
		swap(data[smallpi], data[greaterpi]);
	}


	while (si > 0)
	{
		si--;
		smallpi--;
		swap(data[smallpi], data[si]);
	}
	return;

}


//2
void read(vector<int>& m)
{
	ifstream fin("input.txt");
	int input;
	while (true)
	{
		fin >> input;
		if (input == -1)
			break;
		m.push_back(input);
	}

}

void segregation(vector<int>& nums)
{
	int lp = 0, rp = nums.size() - 1;
	while (lp < rp)
	{
		while (lp < rp && nums[lp] == 0)
			lp++;
		while (lp < rp && nums[rp] == 1)
			rp--;
		swap(nums[lp], nums[rp]);
	}
}


//3
void segregate_on_index(vector<int>& data, int li, int ri, int val)
{
	int si = li;
	int i = li;
	while (true)
	{
		while (i < ri && data[i] != val)
			i++;

		if (i >= ri)
			break;
		swap(data[i++], data[si++]);
	}

	int smallpi = si, greaterpi = ri;

	while (true)
	{
		while (smallpi < greaterpi && data[smallpi] < val)
			smallpi++;

		while (smallpi<greaterpi && data[greaterpi] >val)
			greaterpi--;

		if (smallpi >= greaterpi)
			break;
		swap(data[smallpi], data[greaterpi]);
	}


	while (si > li)
	{
		si--;
		smallpi--;
		swap(data[smallpi], data[si]);
	}
	return;
}

//4
void segregate4(vector<int>& data, int n)
{
	int li = 0;
	int ri;

	for (int i = 0; i < n; i++)
	{
		ri = data.size() - 1;
		while (true)
		{
			while (li < ri && data[li] == i)
				li++;
			while (li < ri && data[ri] != i)
				ri--;

			if (li >= ri)
				break;

			swap(data[li], data[ri]);
		}
	}

	return;
}

//5
void segregate_e_o(vector<int>& m)
{
	int li = 0;
	int ri = m.size() - 1;

	while (true)
	{
		while (li < ri && m[li] % 2 == 0)
			li++;

		while (li < ri && m[ri] % 2 != 0)
			ri--;

		if (li >= ri)
			break;
		swap(m[li], m[ri]);
	}
}
#pragma endregion Q3


//BSCS20035
#pragma region


//a
int binarysearch(vector<int>& nums, int si, int ei)
{
	if (si > ei)
		return -1;

	int mid = si + (ei - si) / 2;
	if (nums[mid] == mid)
		return mid;
	if (nums[mid] < mid)
		binarysearch(nums, mid + 1, ei);
	else if (nums[mid] > mid)
		binarysearch(nums, si, mid - 1);
}


//b (i)
vector<int> merge(vector<int>a, vector<int> b)
{
	vector<int>nums(a.size() + b.size());
	int i = 0;
	int j = 0;
	for (int k = 0; k < nums.size(); k++)
	{
		if (i == a.size())
			nums[k] = b[j++];
		else if (j == b.size())
			nums[k] = a[i++];
		else if (a[i] < b[j])
			nums[k] = a[i++];
		else
			nums[k] = b[j++];
	}

	return nums;
}

vector<int> merge2d(vector<vector<int>> data)
{
	vector<int>res{};

	for (int i = 0; i < data.size(); i++)
	{
		res = merge(res, data[i]);
	}

	return res;
}


//b (ii)
vector<int> merge2dpq(vector<vector<int>> data)
{
	priority_queue<Node, vector<Node>, Comparator> pq;
	vector<int> res;
	Node temp;

	for (int i = 0; i < data.size(); i++)
	{
		temp.val = data[i][0];
		temp.i = i;
		temp.j = 1;

		pq.push(temp);

	}


	while(true)
	{
		temp = pq.top();
		res.push_back(temp.val);
		pq.pop();

		
		if (temp.j < data[temp.i].size())
		{
			temp.val = data[temp.i][temp.j];
			temp.j++;
			pq.push(temp);
		}

		if (pq.empty())
			break;

	}

	return res;						//O(TNLOGT)
}
#pragma endregion Q4

//BSCS20035
#pragma region

#pragma region

int findsum1(vector<int>& nums, int si, int ei)
{
	int sum = 0;
	for (int i = si; i <= ei; i++)
	{
		sum += nums[i];
	}
	return sum;
}

vector<int> maxSubArray1(vector<int>& prices) {
	vector<int> res;
	vector<int> nums;


	find_difference(nums, prices);

	int sum = 0, si = 0, ei = 0, maxsum = 0;

	for (int i = 0; i < nums.size(); i++)
	{

		for (int j = nums.size() - 1; j >= i; j--)
		{
			sum = findsum1(nums, i, j);
			if (sum > maxsum)
			{
				maxsum = sum;
				si = i;
				ei = j;
			}
		}
	}

	if (maxsum <= 0)
		return res;
	for (int i = si; i <= ei + 1; i++)
	{
		res.push_back(prices[i]);
	}
	return res;
}

#pragma endregion N^3

#pragma region

vector<int> maxSubArray2(vector<int>& prices) {
	vector<int> res;
	vector<int> nums;

	find_difference(nums, prices);

	int sum = 0, si = 0, ei = 0, maxsum = 0;

	for (int i = 0; i < nums.size(); i++)
	{
		int sum = 0;
		for (int j = i; j < nums.size(); j++)
		{
			sum += nums[j];
			if (sum > maxsum)
			{
				maxsum = sum;
				ei = j;
				si = i;
			}
		}
	}

	if (maxsum <= 0)
		return res;

	for (int i = si; i <= ei + 1; i++)
	{
		res.push_back(prices[i]);
	}
	return res;
}

#pragma endregion N^2

#pragma region

int cross(vector<int>& nums, int si, int mid, int ei, int& li, int& ri)
{
	int rightmax = INT_MIN, leftmax = INT_MIN;
	int sum = 0;
	for (int i = mid; i >= si; i--)
	{
		sum += nums[i];
		if (sum > leftmax)
		{
			leftmax = sum;
			li = i;
		}
	}

	sum = 0;
	for (int i = mid + 1; i <= ei; i++)
	{
		sum += nums[i];
		if (sum > rightmax)
		{
			rightmax = sum;
			ri = i;
		}
	}

	return (leftmax + rightmax);

}

int max3(vector<int>& nums, int si, int ei, int& li, int& ri)
{
	if (si >= ei)
		return nums[si];
	int mid = si + (ei - si) / 2;
	int leftmax = max3(nums, si, mid, li, ri);
	int rightmax = max3(nums, mid + 1, ei, li, ri);
	int crossmax = cross(nums, si, mid, ei, li, ri);

	if (leftmax >= rightmax && leftmax >= crossmax)
		return leftmax;
	else if (rightmax >= leftmax && rightmax >= crossmax)
		return rightmax;
	else
		return crossmax;

	return max(max(leftmax, rightmax), crossmax);
}

vector<int> maxSubArray3(vector<int>& prices) {
	vector<int>res;
	vector<int> nums;

	if (prices.size() == 1)
		return res;
	find_difference(nums, prices);


	int li = 0, ri = 0;
	int sum = max3(nums, 0, nums.size() - 1, li, ri);

	if (sum <= 0)
		return res;

	for (int i = li; i <= ri + 1; i++)
	{
		res.push_back(prices[i]);
	}

	return res;

}

#pragma endregion nlogn

#pragma region

vector<int> maxSubArray4(vector<int>& prices)
{

	vector<int> res;
	vector<int> nums;


	find_difference(nums, prices);

	int sum = 0, maxsum = 0;
	int si = 0, ei = 0;

	for (int i = 0; i < nums.size(); i++)
	{
		sum += nums[i];

		if (sum > maxsum)
		{
			maxsum = sum;
			ei = i;
		}
		if (sum < 0)
		{
			sum = 0;
			si = i + 1;
		}
	}

	if (maxsum <= 0)
		return res;
	for (int i = si; i <= ei + 1; i++)
	{
		res.push_back(prices[i]);
	}
	return res;
}

#pragma endregion N

#pragma endregion Q5


void task1()
{
	vector<vector<int>> matrix{
		{5, 2, 6, 1, 2},
		{ 3 , 2 , 7 , 5 , 9 },
		{ 7 , 4 , 1 , 2 , 9 },
		{ 1 , 2 , 3 , 8 , 7 },
		{ 7 , 5 , 1 , 3 , 5 }
	};
	printmatrix(matrix);
	cout << determinant(matrix, matrix.size());
}

void task2()
{
	vector<int> v3{ 1,5,2,10,15,7 };
	cout << entropy(v3, 0, v3.size() - 1);
}

void task3()
{
	vector<int> v2{ 1,55,2,-5,11,3,23,-65,2,6,2,0,12 };
	vector<int>b;
	vector<int> c{ 0,1,2,1,2,2,2,0,0,1,1,1,2,2,0,0,1,0,0,2 };
	read(b);
	//i)
	partition(v2, 2);

	//ii)
	segregation(b);

	//iii)
	//segregate_on_index(v2, 5, v2.size() - 1,2);

	//iv)
	segregate4(c, 2);

	//v)
	//segregate_e_o(v2);

	print_vector(v2);
	print_vector(b);
	print_vector(c);
}

void task4()
{
	vector<int> f{ -100,-20,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,12 };
	vector<vector<int>> data{ {1}, { -2,1,4,8,100,150,200 }, { -10,-5,-3,10 } };
	vector <int> res;

	//i)
	cout << binarysearch(f, 0, f.size() - 1) << endl;

	//ii)
	//res = merge2d(data);

	//iii)
	res=merge2dpq(data);

	print_vector(res);
}

void task5()
{
	vector<int> prices{ 7,1,5,3,4,6 };
	vector<int> res;
	vector<int> v3;


	res = maxSubArray1(prices);

	//res = maxSubArray2(prices);

	//res = maxSubArray3(prices);

	//res = maxSubArray4(prices);

	print_vector(res);
}


int main()
{
	task4();
	return 0;

}

