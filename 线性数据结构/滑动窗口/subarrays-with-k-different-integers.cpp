//
// Created by 12472 on 25-9-1.
//
// 力扣992 k个不同整数的子数组
/*
给定一个正整数数组 nums和一个整数 k，返回 nums 中 「好子数组」的数目。
如果 nums 的某个子数组中不同整数的个数恰好为 k，则称 nums的这个连续、不一定不同的子数组为 「好子数组 」。
例如，[1,2,3,1,2] 中有3个不同的整数：1，2，以及3。
子数组是数组的连续部分。
 */
// https://leetcode.cn/problems/subarrays-with-k-different-integers/description/
// 限定种类，不限定长度，要求连续
// 我的疑问是：如果按照之前求最优解的滑动窗口来解，必然会面临漏解的情况，因为毛毛虫会漏过中途某些开头结尾不与边界条件重合的情况
// 左神的解决办法是：每到一个新的合法位置，就统计一次
// 转换一：题目要求，nums的子数组中，数的种类严格等于k；但这时我们仅仅要求数的种类 <= k
// 用 f(nums, k) 表示 <= k 的子数组个数
// 则最终结果为 f(nums, k) - f(nums, k-1)
// 利用了一些单调性，当窗口越大，越有可能突破限制，而当窗口比当前窗口还小（被覆盖），则必不可能超过
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        // 记录当前出现的种类及数量
        int n = nums.size();
        vector<int> count(n, 0);
        int kind = 0, l = 0, r = 0, sum1 = 0, sum2 = 0;
        // 统计 <= k 的子数组数量
        for (; r < nums.size(); ++r)
        {
            if (count[nums[r]]++ == 0) kind++;  // 新增一个种类
            // 当种类数量已经超过上限 k 时
            while (kind > k)  // 开始压缩左边界
            {
                if (--count[nums[l++]] == 0)
                {
                    kind--;
                }
            }
            // 计数，为防止多记或漏记，记录[l, r]区间内 l - r, l+1 - r, ... , r - r
            sum1 += r - l + 1;
        }
        // 统计 <= k-1 的子数组数量
        l = 0, r = 0, kind = 0;
        for (int i = 0; i < n; i++) count[i] = 0;
        for (; r < nums.size(); ++r)
        {
            if (count[nums[r]]++ == 0) kind++;  // 新增一个种类
            // 当种类数量已经超过上限 k - 1 时
            while (kind > k - 1)  // 开始压缩左边界
            {
                if (--count[nums[l++]] == 0)
                {
                    kind--;
                }
            }
            // 计数，为防止多记或漏记，记录[l, r]区间内 l - r, l+1 - r, ... , r - r
            sum2 += r - l + 1;
        }
        return sum1 - sum2;
    }
};

int main()
{
    vector<int> nums = {1,2};
    Solution sol;
    cout << sol.subarraysWithKDistinct(nums, 1) << endl;
    return 0;
}