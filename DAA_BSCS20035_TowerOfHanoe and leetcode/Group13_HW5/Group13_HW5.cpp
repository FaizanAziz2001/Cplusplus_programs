#include <iostream>
#include <stack>
#include<vector>
#include <assert.h>

using namespace std;

#pragma region

//BSCS20027
#pragma region
int maxProduct(vector<int>& nums) {
	int maxp = nums[0], minp = nums[0];
	int product = nums[0];

	for (int i = 1; i < nums.size(); i++)
	{

		if (nums[i] < 0)
			swap(maxp, minp);

		int tempmax = maxp * nums[i];
		int tempmin = minp * nums[i];

		maxp = max(tempmax, nums[i]);             //[-5,8] 8  is max
		minp = min(tempmin, nums[i]);             //[-5,8] -45 is min


		product = max(product, maxp);
	}

	return product;
}
#pragma endregion Q1

//BSCS20035
#pragma region
int rob(vector<int>& nums) {
	vector<int> memo(nums.size() + 1);
	memo[0] = 0;
	memo[1] = nums[0];

	for (int i = 1; i < nums.size(); i++)
	{
		memo[i + 1] = max(memo[i], memo[i - 1] + nums[i]);
	}
	return memo[nums.size()];
}


//nums[1,2,3,1]

//dp[0,1,2,4,4]
#pragma endregion Q2

//BSCS20035
#pragma region
int partitionDisjoint(vector<int>& nums) {
	vector<int> rightmin(nums.size());
	vector<int>leftmax(nums.size());

	int rmin = nums[nums.size() - 1];
	int lmax = nums[0];
	for (int i = nums.size() - 1; i >= 0; i--)
	{
		if (nums[i] < rmin)
			rmin = nums[i];
		rightmin[i] = rmin;
	}

	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] > lmax)
			lmax = nums[i];
		leftmax[i] = lmax;
	}


	for (int i = 0; i < nums.size(); i++)
	{
		if (leftmax[i] <= rightmin[i + 1])
			return i + 1;

	}

	return 0;
}
#pragma endregion Q3

//BSCS20027
#pragma region
int maxProfit1(vector<int>& prices) {
	int sum = 0, maxsum = 0;

	for (int i = 0; i + 1 < prices.size(); i++)
	{
		sum += prices[i + 1] - prices[i];
		if (sum > maxsum)
			maxsum = sum;
		if (sum < 0)
			sum = 0;
	}

	return maxsum;
}
#pragma endregion Q4

//BSCS20027
#pragma region
int maxProfit2(vector<int>& prices) {

	int sum = 0;
	for (int i = 0; i + 1 < prices.size(); i++)
	{
		if (prices[i + 1] - prices[i] > 0)
			sum += (prices[i + 1] - prices[i]);

	}

	return sum;
}
#pragma endregion Q5

//BSCS20035
#pragma region
int maxProfit3(vector<int>& prices) {
	if (!prices.size())
		return 0;
	int buy1 = INT_MAX;
	int profit1 = INT_MIN;
	int buy2 = INT_MAX;
	int profit2 = INT_MIN;
	for (int i = 1; i < prices.size(); i++) {
		buy1 = min(buy1, prices[i]);
		profit1 = max(profit1, prices[i] - buy1);
		buy2 = min(buy2, prices[i] - profit1);
		profit2 = max(profit2, prices[i] - buy2);
	}
	return profit2;
}
#pragma endregion Q6

#pragma endregion leetcode

//BSCS20035
#pragma region
int moveTopPlate(stack<int>& source, stack<int>& destination) { // Move the top plate and returns the operation cost
	int T = source.top();
	source.pop();
	assert(destination.empty() || T < destination.top()); // this makes sure our increasing sequence is maintained at all times.
	destination.push(T);
	return 1;
}

int moveTower(stack<int>& source, stack<int>& destination, stack<int>& helper, int n) {
	if (n == 0)
		return 0;
	int count = 0;
	count+=moveTower(source, helper, destination,n-1);
	count+=moveTopPlate(source, destination);
	count+=moveTower(helper, destination, source,n-1);
	return count;
}

stack<int> createTower(int n) { // creates a valid stack with n plates of increasing size, top to bottom
	stack<int> s;
	for (int i = n; i >= 1; i--) {
		s.push(i);
	}
	return s;
}

#pragma endregion tower_of_hanoi


int main() {
	int n;
	cout << "Enter the height of tower: ";
	cin >> n;
	stack<int> a = createTower(n);
	stack<int> b, c;

	int count = moveTower(a, b, c, n);
	cout << "Count: " << count;

	assert(a.empty() && c.empty() && b.size() == n); // generates error if tower has not been moved properly.
	return 0;
}