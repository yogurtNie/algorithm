//
// Created by 12472 on 26-3-27.
//
/*
 * 将数组分成几个递增序列
 * 给你一个有序的正数数组nums和整数k
 * 判断该数组是否可以被分成一个或者几个长度至少为K的不相交（不许相等，严格递增）的递增子序列
 * 数组中的所有数字都要被若干不相交的递增子序列包含
 * https://leetcode.cn/problems/divide-array-into-increasing-sequences/
 */
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    bool canDivideIntoSubsquence(vector<int>& nums, int K)
    {
        // 统计最大词频
        int cnt = 1, maxCnt = 1;
        // 在有序数组中，求某个数的最大词频
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i - 1] != nums[i])
            {
                maxCnt = max(maxCnt, cnt);
                cnt = 1;
            }
            else cnt++;
        }
        maxCnt = max(maxCnt, cnt);
        return nums.size() / maxCnt >= K;
    }
};