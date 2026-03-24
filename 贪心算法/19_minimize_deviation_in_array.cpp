//
// Created by 12472 on 26-3-24.
//
/*
* 给你一个由 n 个正整数组成的数组 nums 。
你可以对数组的任意元素执行任意次数的两类操作：
如果元素是 偶数 ，除以 2
例如，如果数组是 [1,2,3,4] ，那么你可以对最后一个元素执行此操作，使其变成 [1,2,3,2]
如果元素是 奇数 ，乘上 2
例如，如果数组是 [1,2,3,4] ，那么你可以对第一个元素执行此操作，使其变成 [2,2,3,4]
数组的 偏移量 是数组中任意两个元素之间的 最大差值
返回数组在执行某些操作之后可以拥有的 最小偏移量 。
https://leetcode.cn/problems/minimize-deviation-in-array/
 */
// 复杂度：一个数字能够进出有序表的最大次数为，logv，有n个数，所以总体复杂度为nlogv，v就是整个数组中最大的数
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minimumDeviation(vector<int>& nums) {
        set<int> s;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] % 2 == 0) s.insert(nums[i]);
            else s.insert(nums[i] * 2);      // 给奇数上升的机会
        }
        int ans = *s.rbegin() - *s.begin();
        while (*s.rbegin() % 2 == 0)
        {
            int num = *s.rbegin();
            s.erase(num);
            s.insert(num/2);
            ans = min(ans, *s.rbegin() - *s.begin());
        }
        return ans;
    }
};

int main()
{
    vector<int> v = {1,2,3,4};
    Solution sol;
    cout << sol.minimumDeviation(v) << endl;
    return 0;
}