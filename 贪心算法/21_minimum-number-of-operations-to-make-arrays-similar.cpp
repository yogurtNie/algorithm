//
// Created by 12472 on 26-3-24.
//
/*
* 给你两个正整数数组 nums 和 target ，两个数组长度相等。
在一次操作中，你可以选择两个 不同 的下标 i 和 j ，其中 0 <= i, j < nums.length ，并且：
令 nums[i] = nums[i] + 2 且
令 nums[j] = nums[j] - 2 。
如果两个数组中每个元素出现的频率相等，我们称两个数组是 相似 的。
请你返回将 nums 变得与 target 相似的最少操作次数。测试数据保证 nums 一定能变得与 target 相似。
输入：nums = [8,12,6], target = [2,14,10]
输出：2
解释：可以用两步操作将 nums 变得与 target 相似：
- 选择 i = 0 和 j = 2 ，nums = [10,12,4] 。
- 选择 i = 1 和 j = 2 ，nums = [10,14,2] 。
2 次操作是最少需要的操作次数。
https://leetcode.cn/problems/minimum-number-of-operations-to-make-arrays-similar/
*/

#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    long long makeSimilar(vector<int>& nums, vector<int>& target) {
        vector<int> nums_odd, nums_even;
        vector<int> target_odd, target_even;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] % 2) nums_odd.push_back(nums[i]);
            else nums_even.push_back(nums[i]);
            if (target[i] % 2) target_odd.push_back(target[i]);
            else target_even.push_back(target[i]);
        }
        sort(nums_odd.begin(), nums_odd.end());
        sort(nums_even.begin(), nums_even.end());
        sort(target_odd.begin(), target_odd.end());
        sort(target_even.begin(), target_even.end());
        long long ans = 0;
        int odd_nums = nums_odd.size(), even_nums = nums_even.size();
        for (int i = 0; i < odd_nums; i++)
        {
            ans += abs(nums_odd[i] - target_odd[i]);
        }
        for (int i = 0; i < even_nums; i++)
        {
            ans += abs(nums_even[i] - target_even[i]);
        }
        return ans/4;

    }
};

int main()
{
    vector<int> nums = {8,12,6};
    vector<int> target = {2,14,10};
    Solution sol;
    cout << sol.makeSimilar(nums, target) << endl;
    return 0;
}