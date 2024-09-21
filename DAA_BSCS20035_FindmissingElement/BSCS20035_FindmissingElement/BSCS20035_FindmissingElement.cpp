#include <iostream>
#include<vector>

using namespace std;

#pragma region
int search(int* nums, int target, int size)
{

	int si = 0;
	int ei = size - 1;
	while (si <= ei)
	{

		int midpoint = si + ((ei - si) / 2);
		if (nums[midpoint] == target)
			return midpoint;
		if (nums[midpoint] < target)
			si = midpoint + 1;
		else if (nums[midpoint] > target)
			ei = midpoint - 1;
	}

	return -1;
}
#pragma endregion B_search

#pragma region
int Partition(int D[], int si, int ei)
{
	int pivot = D[ei];
	int pi = si - 1;

	for (int i = si; i < ei; i++)
	{
		if (D[i] <= pivot)
		{
			pi++;
			swap(D[pi], D[i]);

		}
	}
	swap(D[pi + 1], D[ei]);
	return (pi + 1);
}

void QS(int D[], int si, int ei)
{

	if (si < ei)
	{
		int Pi = Partition(D, si, ei);
		QS(D, si, Pi - 1);
		QS(D, Pi + 1, ei);
	}
}

void Quick_Sort(int D[], int size)
{
	QS(D, 0, size - 1);
}
#pragma endregion QuickSort

#pragma region
int q1(int* arr, int size)
{

	for (int i = 0; i < size; i++)
	{
		int count{};
		for (int j = 0; j < size; j++)
		{
			if (i == arr[j])
			{
				break;
			}
			else
			{
				count++;
			}
		}
		if (count == size)
		{
			return i;
		}
	}
	return -1;

}

int q2(int* arr, int size)
{
	Quick_Sort(arr, size);
	for (int i = 0; i <= size; i++)
	{
		if (search(arr, i, size) == -1)
		{
			return i;
		}

	}

	return -1;
}

int q3(int* arr, int size)
{
	Quick_Sort(arr, size);
	for (int i = 0; i < size; i++)
	{
		if (arr[i] != i)
		{
			return i;
		}
	}
}

int q4(int* arr, int size)
{
	Quick_Sort(arr, size);

	int si = 0;
	int ei = size - 1;
	int midpoint = 0;
	while (si <= ei)
	{

		midpoint = si + ((ei - si) / 2);
		if (arr[midpoint] != midpoint)
		{
			if (arr[midpoint - 1] != midpoint - 1)
				ei = midpoint - 1;
			else
				return midpoint;
		}
		else
			si = midpoint + 1;
	}

	return midpoint;

}

int q5(int* arr, int size)
{
	bool* aux = new bool[size + 1]{};

	for (int i = 0; i < size; i++)
	{
		aux[arr[i]] = 1;
	}
	for (int j = 0; j < size + 1; j++)
	{
		if (aux[j] == 0)
		{
			return j;
		}
	}
}

int q6(int* arr, int size)
{
	int sum;
	sum = ((size + 1) * (size)) / 2;
	for (int i = 0; i < size; i++)
	{
		sum = sum - arr[i];
	}
	return sum;
}

void q7()
{
	/*
	*
	* Part1
	*
	*
	Bit complexity is the number of bits read in an algorithm. In solution 6, the time complexity is O(N).
	This means that there are N numbers which are being read N times in total, and the complexity of this
	algorithm increases with the number of inputs in a linear relation. So, the bit complexity of this solution
	would be N*(Number of bits in the number). Since we dont know how big the number is, we can use this general formula to
	calculate the bit complexity of that solution. Normally, it would be N(8) if the number has 8-bits.





	*/


	/*
	* Part 2
	The pseudo code for an algorithm:

	function numToBinaryStringConversion(argument)
	{

		convert the given argument into a binary string
		and retrun it;
	}

	main()
	{
		an array arr is given along with its size;
		loop(running for the 2^log(arr[size-1])-1 )
		{

		numToBinaryStringConversion(array);

		we store the values in a new array of the  size=2^ log(arr[size-1]-1)
		and call it arr2;
		}

		in arr2, we compare the the last bits of the binary number representation
		of each number in the orignal array arr and figure out the number of 1's and
		0's. Since we know that one element is missing, we can figure out the missing bit
		at the last position of the missing number. If the numnber of 1's is greater, the last
		bit of the missing bit is 0 and vice versa;

		Similary we perform the same task for the second and third bit, to form the complete 3-bit
		binary number that was missing from the orignal array arr;

		loop(for number of bits)
		{
			loop(for size of string array)
			{
				check for 0
				  increment 0's varaible
				check for 1
					increment 1's varaible
			}

			compare number and zeroes and append it in a string
		}

	}
	*/
}
#pragma endregion Question 1

#pragma region

void Question_4()
{
	/*
		NUTS AND BOLTS:


		Method 1:
		main()
		{

		We assume that the locks are represented by some unique and non-repeating special characters for each lock
		and the keys are represented by the symbol of their corresponding locks;
		The array for locks is arr1, and the array for keys is arr2;

		This means that we have 2 arrays with the same values, although they are unsorted and in a different order than
		the other;

		Quick_sort(arr1,size_of_arr1);
		Quick_sort(arr2,size_of_arr2);

		Since both the arrays were same, they would be sorted in the same fashion, according to their ascii code.

		print(arr1);
		print(arr2);


		//The time complexity for this method would be 2NlogN which would equal to O(NlogN) since quick sort takes NlogN time.

		}

		Method 2:


		main()
		{

		We assume that the locks and keys are unlabelled and the only way to know which key belong to which lock, we have to test them against
		each other by testing each combination to find the right one.

		We can make auxillary arrays to

		The array for locks is Locks, and the array for keys is Keys. Both of their sizes are also given(N);

		outerLoop for Locks(index i, runs from 0 till N)
		{

			innerLoop for Keys(index j, runs till N)
			{
			if(Keys[j] fits in Locks[i])
				then swap Key[j] with Key[i]

			//since we found the first key, we can decrease the number of iterations we have to go through for the next lock by adding 1 to the
			starting index of this loop for the next iteration
			}

		}

		When both loops complete, we will have sorted the Keys array according to the order present in Locks array, and the Lock and Key in same index
		would fit each other;

		print(Locks);
		print(Keys);

		//for first lock we have to search N ways, for the second, N-1 ways,....... and so on till the last lock which has only 1 way.

		//hence the maximum number of trials are ((N)*(N+1))/2
		}


	*/
}
#pragma endregion Question 4

#pragma region 
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

#pragma endregion leetcode struct 

#pragma region
int searchleetcode(vector<int>& nums, int target) {

	int si = 0;
	int ei = nums.size() - 1;
	while (si <= ei)
	{
		int midpoint = si + ((ei - si) / 2);
		if (nums[midpoint] == target)
			return midpoint;
		if (nums[midpoint] < target)
			si = midpoint + 1;
		else if (nums[midpoint] > target)
			ei = midpoint - 1;
	}

	return -1;
}

int binarysearchleetcode(int si, int ei, vector<int>& nums, int target)
{
	if (si > ei)
		return -1;

	int midpoint = si + ((ei - si) / 2);
	if (nums[midpoint] == target)
		return midpoint;
	else if (nums[midpoint] < target)
		return binarysearchleetcode(midpoint + 1, ei, nums, target);
	else if (nums[midpoint] > target)
		return binarysearchleetcode(si, midpoint - 1, nums, target);

	return -1;
}

int search(vector<int>& nums, int target) {

	return binarysearchleetcode(0, nums.size() - 1, nums, target);
}
#pragma endregion Q2 binarysearch

#pragma region


//insert search position

int searchInsert(vector<int>& nums, int target) {
	int si = 0;
	int ei = nums.size() - 1;
	int midpoint;
	while (si <= ei)
	{
		midpoint = si + ((ei - si) / 2);
		if (nums[midpoint] == target)
			return midpoint;
		else if (nums[midpoint] < target)
			si = midpoint + 1;
		else if (nums[midpoint] > target)
			ei = midpoint - 1;
	}

	if (target > nums[midpoint])
		return midpoint + 1;
	else
		return midpoint;
}

//find square root
int mySqrt(int x) {

	for (long i = 0; true; i++)
	{
		if (i * i > x)
			return i - 1;
	}

	return -1;
}

//find peak element

int findPeakElement(vector<int>& nums) {
	int si = 0;
	int ei = nums.size() - 1;

	while (si <= ei)
	{
		int mid = si + (ei - si) / 2;
		if ((mid == 0 || nums[mid] > nums[mid - 1]) && (mid == nums.size() - 1 || nums[mid] > nums[mid + 1]))
			return mid;
		else if (mid > 0 && mid<nums.size() - 1 && nums[mid - 1]>nums[mid])
			ei = mid - 1;
		else
			si = mid + 1;
	}

	return 0;
}

//search 2d matrix

bool searchMatrix(vector<vector<int>>& matrix, int target) {

	int row;
	for (int i = 0; i < matrix.size(); i++)
	{
		if (target >= matrix[i][0] && target <= matrix[i][matrix[i].size() - 1])
		{

			int si = 0;
			int ei = matrix[i].size() - 1;

			while (si <= ei)
			{
				int midpoint = si + (ei - si) / 2;
				if (matrix[i][midpoint] == target)
					return true;
				if (matrix[i][midpoint] < target)
					si = midpoint + 1;
				else
					ei = midpoint - 1;
			}
		}
	}
	return false;
}

//rotate list

ListNode* rotateRight(ListNode* head, int k) {
	if (head == nullptr || head->next == nullptr || k == 0)
		return head;

	ListNode* tail;
	ListNode* temp = head;
	int size = 1;

	while (temp->next)
	{
		size++;
		temp = temp->next;
	}

	if (k % size == 0)
		return head;

	tail = temp;
	tail->next = head;

	k = k % size;

	for (int i = 0; i < size - k; i++)
	{
		tail = tail->next;
	}

	head = tail->next;
	tail->next = nullptr;

	return head;
}


//binary pruning

TreeNode* pruneTree(TreeNode* root)
{
	if (!root)
		return nullptr;

	root->left = pruneTree(root->left);
	root->right = pruneTree(root->right);

	if (!root->left && !root->right && root->val == 0)
		return nullptr;
	else
		return root;
}


#pragma endregion Q3 leetcode

int main()
{
	int arr[5] = { 2,3,1,4,5 };

	//Quick_Sort(arr, 5);
	//cout << search(arr, 5, 5);
	//cout << q5(arr, 5)<<endl;
	int arr2[11] = { 0,3,2,4,5,6,7,1,9,10,11 };
	//cout << q5(arr2, 11);

	//cout<<q1(arr, 5);
	//cout << q2(arr, 5)<<endl;
	//cout << q2(arr2,11);
	//cout << q3(arr, 5) << endl;
	//cout << q3(arr2, 11);
	cout << q4(arr, 5) << endl;
	//cout << q4(arr2, 11);
	//cout << q6(arr, 5) << endl;
	//cout << q6(arr2, 11);
}

