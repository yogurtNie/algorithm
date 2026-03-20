//
// Created by 12472 on 26-3-19.
//
/*
 * 给定一个非负的数组arr，计算任何两个数差值的绝对值
 * 如果得到的差值绝对值arr中没有，都要加入到arr中，但是只加入一份
 * 新的arr，继续计算两个数差值的绝对值
 * 一直到arr大小固定，返回arr最终的长度
 * 大厂笔试，无在线测评，使用对数器验证
 */
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    // 最优解，计算最大的gcd，并利用gcd得到要新增的数量
    // 这个大的gcd是指，所有的数相互之间的gcd的最大值
    int way2(vector<int>&nums)
    {
        int Max = 0;        // 数组中的最大值
        int Mgcd = 0;
        map<int, int> mp;   // 词频统计
        for (int i = 0; i < nums.size(); i++)
        {
            Max = max(Max, nums[i]);
            if (nums[i] != 0 && Mgcd == 0) Mgcd = nums[i];
            if (mp.find(Max) == mp.end()) mp[nums[i]] = 1;
            else mp[nums[i]] += 1;
        }
        // 计算整个数组中的最大gcd，往前滚动式计算
        for (int i = 0; i < nums.size(); i++)
        {
            Mgcd = max(Mgcd, __gcd(Mgcd, nums[i]));
        }
        int ans = Max / Mgcd;
        auto it = mp.begin();
        for (; it != mp.end(); it++)
        {
            if (it->first != 0) ans += it->second - 1;
        }
        --it;
        // 如果没有0，且有重复的数
        if (mp.find(0) == mp.end() && it->second > 1) ans += 1;
        // 如果有0，则只加上0的数量就好
        else if (mp.find(0) != mp.end()) ans += mp[0];
        return ans;
    }
};