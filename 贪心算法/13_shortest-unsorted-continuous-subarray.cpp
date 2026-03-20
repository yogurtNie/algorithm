//
// Created by 12472 on 26-3-20.
//
/*
* 给你一个整数数组 nums ，你需要找出一个 连续子数组 ，如果对这个子数组进行升序排序，那么整个数组都会变为升序排序。
请你找出符合题意的 最短 子数组，并输出它的长度。
输入：nums = [2,6,4,8,10,9,15]
输出：5
解释：你只需要对 [6, 4, 8, 10, 9] 进行升序排序，那么整个表都会变为升序排序。
https://leetcode.cn/problems/shortest-unsorted-continuous-subarray/description/
*/
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        vector<bool> flag1(nums.size(), false), flag2(nums.size(), false);
        int Max = INT_MIN, Min = INT_MAX;
        // 从左往右遍历
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] < Max) flag1[i] = true;
            Max = max(Max, nums[i]);
        }
        // 从右往左遍历
        for (int i = nums.size() - 1; i >= 0; i--)
        {
            if (nums[i] > Min) flag2[i] = true;
            Min = min(Min, nums[i]);
        }
        int left = -1, right = -1;
        for (int i = 0; i < nums.size(); i++)
        {
            if (flag2[i]) { left = i; break; }
        }
        for (int i = nums.size() - 1; i >= 0; i--)
        {
            if (flag1[i]) { right = i; break; }
        }
        if (left > right || left == -1 || right == -1) return 0;
        return right - left + 1;
    }
    // 一个更加简便的写法
    int findUnsortedSubarray2(vector<int>& nums)
    {
        int n = nums.size();
        int right = -1, left = n - 1;
        int Max = INT_MIN, Min = INT_MAX;
        for (int i = n - 1; i >= 0; i--)
        {
            if (nums[i] > Min) left = i;
            Min = min(Min, nums[i]);
        }
        for (int i = 0; i < n; i++)
        {
            if (nums[i] < Max) right = i;
            Max = max(Max, nums[i]);
        }
        return max(0, right - left + 1);
    }
};

int main()
{
    vector<int> nums = {2,6,4,8,10,9,15};
    Solution s;
    cout <<s.findUnsortedSubarray2(nums);
    return 0;
}