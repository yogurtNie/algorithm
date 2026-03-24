//
// Created by 12472 on 26-3-24.
//
/*
 * 两个0和1数量相等区间的最大长度
 * 给出一个长度为n的01串，需要找到两个区间
 * 在这两个区间中，1的数量相等，0的个数也相等
 * 这两个区间可以相交，但是不可以完全重叠，两个区间的左右端点不可以完全一样
 * 请你找到两个最长区间，满足以上要求，返回区间最大长度
 * 无在线测试
 */
#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    int way1(vector<int>& nums)
    {

    }
    int way2(vector<int>& nums)
    {
        int leftZero = -1, rightZero = nums.size();
        int leftOne = -1, rightOne = nums.size();
        for (int i = 0; i < nums.size(); i++)
            if (nums[i] == 0) {leftZero = i; break;}
        for (int i = 0; i < nums.size(); i++)
            if (nums[i] == 1) {leftOne = i; break;}
        for (int i = nums.size() - 1; i >= 0; i--)
            if (nums[i] == 0) {rightZero = i; break;}
        for (int i = nums.size() - 1; i >= 0; i--)
            if (nums[i] == 1) {rightOne = i; break;}
        return max(rightZero - leftZero,rightOne - leftOne);
    }
};