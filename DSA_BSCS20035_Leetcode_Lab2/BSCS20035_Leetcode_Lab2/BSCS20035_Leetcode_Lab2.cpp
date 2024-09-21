
#include <iostream>
#include<stack>
#include<vector>
#include<queue>
using namespace std;

//Valid parenthesis
bool isValid(string s) {

	stack <char> S;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '(' || s[i] == '{' || s[i] == '[')
		{
			S.push(s[i]);
			continue;

		}
		else
		{
			if (S.empty())
				return false;
			if (S.top() == '(' && s[i] == ')' || S.top() == '[' && s[i] == ']' || S.top() == '{' && s[i] == '}')
				S.pop();
			else
				return false;
		}

	}

	if (S.empty())
		return true;
	else
		return false;
}


//Minstack
class MinStack {
private:
	stack<int> s1;
	stack<int> s2;
public:
	MinStack() {

	}

	void push(int val) {
		s1.push(val);
		if (s2.empty())
			s2.push(val);
		else if (val <= s2.top())
			s2.push(val);
	}

	void pop() {
		if (s1.top() == s2.top())
			s2.pop();
		s1.pop();
	}

	int top() {
		return s1.top();
	}

	int getMin() {

		return s2.top();
	}
};

//Trap Rainwater
int trap(vector<int>& height) {
	int li = 0, ri = height.size() - 1;
	int maxl = height[li], maxr = height[ri];
	int sum = 0, total;
	while (li < ri)
	{
		if (maxl <= maxr)
		{
			li++;
			total = (maxl - height[li]);
			if (total > 0)
				sum = sum + total;
		}
		else if (maxl > maxr)
		{
			ri--;
			total = (maxr - height[ri]);
			if (total > 0)
				sum = sum + total;
		}

		if (height[li] > maxl)
			maxl = height[li];
		if (height[ri] > maxr)
			maxr = height[ri];
	}
	return sum;
}

//Decode string
class Solution {
public:
	string decode(string s, stack<int>& digit, stack<string>& ch, int& i)
	{

		int num = 0;
		string word = "";
		for (; i < s.length(); i++)
		{

			if (isdigit(s[i]))
				num = num * 10 + (s[i] - 48);
			else if (isalpha(s[i]))
				word = word + s[i];
			else if (s[i] == '[')
			{
				digit.push(num);
				decode(s, digit, ch, ++i);
				for (int k = 0; k < digit.top(); k++)
				{
					word = word + ch.top();
				}
				digit.pop();
				ch.pop();
				num = 0;
			}
			else if (s[i] == ']')
			{
				ch.push(word);
				return word;
			}


		}
		return word;
	}

	string decodeString(string s) {

		string data;
		stack<int> digit;
		stack<string> ch;
		int i = 0;
		return decode(s, digit, ch, i);
	}
};

//Container with most water
int maxArea(vector<int>& height) {
	int j = height.size() - 1;
	int min_width = height[0];
	int max_width = height[j];
	int area = 0, max_area = 0;

	for (int i = 0; i < j; i++)
	{

		int distance = j - i;
		area = min(min_width, max_width) * distance;
		if (area >= max_area)
			max_area = area;

		if (height[j] <= min_width)
		{
			j--;
			i--;
			max_width = height[j];

		}
		if (height[i + 1] >= min_width)
		{
			min_width = height[i + 1];
		}

	}
	return max_area;
}

//Implement stack using queues
class MyStack {
private:
	queue<int> q1;

public:
	void push(int x) {
		q1.push(x);
	}

	int pop() {
		int value;
		queue<int> q2;

		if (q1.size() == 1)
		{
			value = q1.front();
			q1.pop();
			return value;

		}
		while (q1.size() != 1)
		{
			q2.push(q1.front());
			q1.pop();
		}

		value = q1.front();
		q1 = q2;
		return value;
	}

	int top() {
		return q1.back();
	}

	bool empty() {
		return q1.empty();
	}
};

//Number of studnets unable to eat lunch
class Sol {
public:
	bool check(vector<int>& q, vector<int>& sandwiches)
	{
		for (int i = 0; i < q.size(); i++)
		{
			if (q[i] == sandwiches[0])
				return true;
		}
		return false;
	}

	int countStudents(vector<int>& students, vector<int>& sandwiches) {
		int count = 0;

		while (true)
		{
			if (students.front() != sandwiches.front())
			{
				int temp = students.front();
				students.erase(students.begin());
				students.push_back(temp);
			}
			else
			{
				sandwiches.erase(sandwiches.begin());
				students.erase(students.begin());
			}

			if (!check(students, sandwiches))
			{
				count = students.size();
				break;
			}
		}
		return count;
	}
};


//Front Middle Back Queue
class FrontMiddleBackQueue {
private:
	queue<int>q1;

public:
	FrontMiddleBackQueue() {

	}

	void pushFront(int val) {
		queue<int>q2;

		if (q1.empty())
		{
			q1.push(val);
			return;
		}
		q2.push(val);
		while (!q1.empty())
		{
			q2.push(q1.front());
			q1.pop();
		}
		q1 = q2;
	}

	void pushMiddle(int val) {
		int mid;
		queue<int>q2;
		mid = q1.size() / 2;
		while (q2.size() < mid)
		{
			q2.push(q1.front());
			q1.pop();
		}
		q2.push(val);
		while (!q1.empty())
		{
			q2.push(q1.front());
			q1.pop();
		}

		q1 = q2;


	}

	void pushBack(int val) {
		q1.push(val);
	}

	int popFront() {
		if (q1.empty())
			return -1;
		int val = q1.front();
		q1.pop();
		return val;
	}

	int popMiddle() {
		if (q1.empty())
			return -1;
		int mid, value;
		queue<int>q2;
		if (q1.size() % 2 == 0)
			mid = q1.size() / 2 - 1;
		else
			mid = q1.size() / 2;
		while (q2.size() < mid)
		{
			q2.push(q1.front());
			q1.pop();
		}
		value = q1.front();
		q1.pop();
		while (!q1.empty())
		{
			q2.push(q1.front());
			q1.pop();
		}

		q1 = q2;
		return value;
	}

	int popBack() {

		if (q1.empty())
			return -1;
		int value;
		value = q1.back();
		queue<int>q2;
		if (q1.size() == 1)
		{
			q1.pop();
			return value;
		}
		while (q1.size() != 1)
		{
			q2.push(q1.front());
			q1.pop();
		}
		q1 = q2;
		return value;
	}
};

//Maximum circular subarray sum
int maxSubarraySumCircular(vector<int>& nums) {
	int maximum = nums[0], minimum = nums[0];
	int maxsum = 0, minsum = 0, total = 0;

	for (int i = 0; i < nums.size(); i++)
	{
		total = total + nums[i];
		maxsum = maxsum + nums[i];
		minsum = minsum + nums[i];

		if (maxsum >= maximum)
			maximum = maxsum;
		if (minsum <= minimum)
			minimum = minsum;
		if (maxsum < 0)
			maxsum = 0;
		if (minsum > 0)
			minsum = 0;

	}
	if (total - minimum == 0)
		return maximum;
	return max(maximum, (total - minimum));
}


//Asterioid Collision
vector<int> asteroidCollision(vector<int>& asteroids) {
	vector<int>data;
	for (int i = 0; i < asteroids.size(); i++)
	{
		if (data.size() == 0)
			data.push_back(asteroids[i]);
		else if (asteroids[i] > 0 && data.back() > 0)
			data.push_back(asteroids[i]);
		else if (asteroids[i] < 0 && data.back()>0)
		{
			if (data.back() + asteroids[i] == 0)
				data.pop_back();
			else if (data.back() < abs(asteroids[i]))
			{
				data.pop_back();
				i--;
			}
		}
		else
			data.push_back(asteroids[i]);

	}
	return data;
}

int main()
{
	return 0;
}
