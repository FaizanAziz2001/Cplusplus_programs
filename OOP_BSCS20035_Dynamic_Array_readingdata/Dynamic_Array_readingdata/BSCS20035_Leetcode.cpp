//Leetcode problems



//task1
class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {

        vector<int> data{};
        for (int i = 0; i < nums.size(); i++)
        {
            int count = 0;
            for (int j = 0; j < nums.size(); j++)
            {
                if (i == j)
                    continue;
                if (nums[i] > nums[j])
                    count++;
            }
            data.push_back(count);
        }
        return data;
    }
};




//task 2
class Solution {
public:
    int removeElement(vector<int>& nums, int val)
    {
        if (nums.size() == 0)
            return 0;

        int fi = 0, ei = nums.size() - 1;

        while (fi <= ei)
        {
            while (fi <= ei && nums[fi] != val)
                fi++;

            while (fi <= ei && nums[ei] == val)
                ei--;

            if (fi < ei)
                swap(nums[fi], nums[ei]);
        }

        return fi;

    }
};

//task3
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {

        int rows = matrix.size(), cols = matrix[0].size();

        for (int i = 0; i < rows; i++)
        {
            if (target >= matrix[i][0] && target <= matrix[i][cols - 1])
            {
                int si = 0, ei = cols - 1;

                while (si <= ei)
                {
                    int midpoint = si + (ei - si) / 2;

                    if (matrix[i][midpoint] == target)
                        return true;
                    else if (target > matrix[i][midpoint])
                        si = midpoint + 1;
                    else
                        ei = midpoint - 1;
                }
            }
        }

        return false;
    }
};


//task4
class Solution {
public:
    int removeDuplicates(vector<int>& nums)
    {

        int count = 1, si = 1, index = si;
        if (nums.size() == 0)
            return 0;

        do
        {
            while (index < nums.size() && nums[si - 1] >= nums[index])
                index++;

            if (index < nums.size())
            {
                swap(nums[si++], nums[index]);
                count++;
            }

        } while (index < nums.size());


        return count;

    }
};

//task5
class Solution {
public:
    int maxSubArray(vector<int>& nums) {

        int total = 0, max = nums[0];
        if (nums.size() == 0)
            return 0;

        for (int i = 0; i < nums.size(); i++)
        {
            total = total + nums[i];
            if (total >= max)
                max = total;
            if (total < 0)
                total = 0;
        }

        return max;
    }
};


//task6
class Solution {
public:
    int firstBadVersion(int n) {

        int si = 1, ei = n;

        while (si <= ei)
        {
            int midpoint = si + (ei - si) / 2;
            if (isBadVersion(midpoint) == false)
                si = midpoint + 1;
            else
                ei = midpoint - 1;
        }

        return si;
    }
};

//task7
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {

        sort(nums.begin(), nums.end());
        int first = 1;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == first)
                first++;
        }
        return first;
    }
};
