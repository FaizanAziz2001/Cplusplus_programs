#include <iostream>
#include<vector>
using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};

void fill_vector(vector<int>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		v[i] = rand() % 100;
	}
}

void print_vector(vector<int>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
}

#pragma region

//BSCS20027
#pragma region
//generate paranthesis
void combinationQ1(int n, int opencount, int closecount, string result, vector<string>& v)
{
	if (opencount == n && closecount == n)
	{
		v.push_back(result);
		return;
	}
	if (opencount < n)
	{
		result.push_back('(');
		combinationQ1(n, opencount + 1, closecount, result, v);
		result.pop_back();
	}
	if (closecount < opencount)
	{
		result.push_back(')');
		combinationQ1(n, opencount, closecount + 1, result, v);
		result.pop_back();
	}


}

vector<string> generateParenthesis(int n)
{

	vector<string> s;
	combinationQ1(n, 0, 0, "", s);
	return s;
}
#pragma endregion Q1	

//BSCS20027
#pragma region 
void combinationQ2(int ldi, string digits, vector<string>s, string result, vector<string>& v)
{
	if (ldi == digits.size())
	{
		v.push_back(result);
		return;
	}

	string temp = s[digits[ldi] - 48];

	for (int i = 0; i < temp.size(); i++)
	{
		combinationQ2(ldi + 1, digits, s, result + temp[i], v);
	}

}

vector<string> letterCombinations(string digits) {
	vector<string> result;

	if (digits.empty())
		return result;

	vector<string> s{ "", "", "abc", "def", "ghi", "jkl","mno", "pqrs", "tuv", "wxyz" };
	combinationQ2(0, digits, s, "", result);
	return result;
}
#pragma endregion Q2

//BSCS20027
#pragma region

void combinationQ3(int index, int sum, int target, vector<vector<int>>& v, vector<int>& candidates, vector<int> temp)
{
	if (sum == target)
	{
		v.push_back(temp);
		return;
	}
	if (sum > target)
		return;

	if (sum < target)
	{
		temp.push_back(candidates[index]);
		combinationQ3(index, sum + candidates[index], target, v, candidates, temp);
		temp.pop_back();
		index++;

		for (index; index < candidates.size(); index++)
		{
			temp.push_back(candidates[index]);
			combinationQ3(index, sum + candidates[index], target, v, candidates, temp);
			temp.pop_back();
		}
	}
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
	vector<vector<int>> result;
	vector<int> temp;
	combinationQ3(0, 0, target, result, candidates, temp);
	return result;
}

#pragma endregion Q3

//BSCS20027
#pragma region

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

	ListNode* result = new ListNode(0);
	ListNode* head = result;
	int carry = 0, sum = 0, val1, val2;

	while (l1 != nullptr || l2 != nullptr)
	{

		val1 = (l1 == nullptr) ? 0 : l1->val;
		val2 = (l2 == nullptr) ? 0 : l2->val;

		sum = val1 + val2 + carry;
		carry = sum / 10;
		sum = sum % 10;


		ListNode* temp = new ListNode(sum, nullptr);
		result->next = temp;
		result = result->next;


		l1 = (l1 == nullptr) ? nullptr : l1->next;
		l2 = (l2 == nullptr) ? nullptr : l2->next;
	}

	if (carry != 0)
	{
		ListNode* temp = new ListNode(carry, nullptr);
		result->next = temp;
	}

	return head->next;
}

#pragma endregion Q4

//BSCS20027
#pragma region
bool isPalindrome(ListNode* head) {
	vector<int> v;
	ListNode* temp = head;
	while (temp != nullptr)
	{
		v.push_back(temp->val);
		temp = temp->next;
	}


	for (int i = 0, j = v.size() - 1; i < j; i++, j--)
	{
		if (v[i] != v[j])
			return false;
	}
	return true;
}
#pragma endregion Q5

//BSCS20035
#pragma region
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
#pragma endregion Q6

//BSCS20035
#pragma region

int merge(vector<int>& nums, int si, int mid, int ei)
{
	int count = 0;
	int j = mid + 1;
	for (int i = si; i <= mid; i++)
	{
		while (j <= ei && nums[i] / 2.0 > nums[j])
		{
			j++;
		}
		count += j - (mid + 1);
	}

	vector<int>temp(ei - si + 1);
	int i = si;
	j = mid + 1;

	for (int k = 0; k < temp.size(); k++)
	{
		if (i > mid)
			temp[k] = nums[j++];
		else if (j > ei)
			temp[k] = nums[i++];
		else if (nums[i] <= nums[j])
			temp[k] = nums[i++];
		else if (nums[j] < nums[i])
			temp[k] = nums[j++];
	}

	for (int i = 0; i < temp.size(); i++)
	{
		nums[i + si] = temp[i];
	}
	return count;
}


int mergeSort(vector<int>& nums, int si, int ei, int& count)
{
	if (si >= ei)
		return 0;
	int mid = si + (ei - si) / 2;
	mergeSort(nums, si, mid, count);
	mergeSort(nums, mid + 1, ei, count);
	count += merge(nums, si, mid, ei);
	return count;
}

int reversePairs(vector<int>& nums) {
	int count = 0;
	return mergeSort(nums, 0, nums.size() - 1, count);
}





#pragma endregion Q7

#pragma endregion leetcode


//BSCS20035
#pragma region
void Merge(vector<int>& v, int si, int mid, int ei)
{
	vector<int> temp(ei - si + 1);

	int i = si, j = mid + 1;
	for (int k = 0; k < temp.size(); k++)
	{
		if (i > mid)						//if a array reaches its size,copy b as it is
			temp[k] = v[j++];
		else if (j > ei)					//if b array reaches its size,copy a as it is
			temp[k] = v[i++];
		else if (v[i] <= v[j])
			temp[k] = v[i++];
		else if (v[i] > v[j])
			temp[k] = v[j++];

	}

	for (int i = 0; i < temp.size(); i++)
	{
		v[i + si] = temp[i];					//temp indexing starts from 0, v indexing starts from 0+si
	}
}

void MergeSort(vector<int>& v, int si, int ei)
{
	if (si < ei)
	{
		int mid = si + (ei - si) / 2;

		MergeSort(v, si, mid);
		MergeSort(v, mid + 1, ei);
		Merge(v, si, mid, ei);
	}
}
#pragma endregion Q1

//BSCS20035
#pragma region
int intpartition(vector<int>& v, int si, int ei)
{
	int index = si + rand() % (ei - si);					//random index for pivot
	int starting_index = si;								//save original starting index

	int pivot = v[index];
	swap(v[index], v[si]);										//move pivot to start

	si++;
	while (true)
	{
		while (si <= ei && v[si] < pivot)							//increase si till it reaches a val greater or equal to pivot
			si++;
		while (si <= ei && v[ei] >= pivot)							//decrease ei till it reaches a val less than pivot
			ei--;

		if (si > ei)												//boundry case
			break;

		swap(v[si], v[ei]);											//swap the values
	}

	swap(v[ei], v[starting_index]);									//move the pivot to its appropriate place
	return ei;														//return pivot index

}

void Quicksort(vector<int>& v, int si, int ei)
{
	if (si < ei)
	{
		int pivot = intpartition(v, si, ei);
		Quicksort(v, si, pivot - 1);
		Quicksort(v, pivot + 1, ei);
	}
}

#pragma endregion Q2


int main()
{
	vector<int> v(15);
	vector<int> c{ 5,8,-11,4,2 };

	srand(time(NULL));

	int choice;

	while (true)
	{
		cout << "1.Merge				2.QuickSort\n\n";
		cin >> choice;
		fill_vector(v);
		print_vector(v);
		cout << endl << endl;
		

		switch (choice)
		{

		case 1:
			cout << "Merge Sort: ";
			MergeSort(v, 0, v.size() - 1);
			break;

		case 2:
			cout << "Quick Sort: ";
			Quicksort(v, 0, v.size() - 1);
			break;

		case 3:
			return 0;

		}
		print_vector(v);
		cout << endl << endl;
	}

}
