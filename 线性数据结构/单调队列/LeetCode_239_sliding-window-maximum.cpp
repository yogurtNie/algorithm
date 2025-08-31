//
// Created by 12472 on 25-6-23.
//
//https://leetcode.cn/problems/sliding-window-maximum/description/
// 单调队列模板
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> Deque(n);
        int h = 0, t = 0;
        // 先形成长度为k-1的窗口
        for (int i = 0; i < k -1; i++)
        {
            // 严格大到小
            while (h < t && nums[Deque[t - 1]] <= nums[i])
            {
                t--;
            }
            Deque[t++] = i;
        }
        int m = n - k + 1;      // 之后要得到的答案的数量（本题是固定的）
        vector<int> maxNums;
        for (int l = 0, r = k - 1; l < m; l++, r++)
        {
            while (h < t && nums[Deque[t-1]] <= nums[r])
            {
                t--;
            }
            Deque[t++] = r;
            maxNums.push_back(nums[Deque[h]]);
            while (Deque[h] <= l) h++;
        }
        return maxNums;
    }
};