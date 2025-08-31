//
// Created by 12472 on 25-6-24.
//
/*
 * 给你一个整数数组nums，和一个表示限制的整数 limit，请你返回最长连续子数组的长度，该子数组中的任意两个元素之间的绝对差必须小于或者等于 limit 。
 * https://leetcode.cn/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/description/
 * 分析单调性：扩出窗口的时候，最大值只可能变大，最小值只可能变小
 * 所以如果最大值 - 最小值是达标的，那么里面一定是达标的
 * 而如果最大值 - 最小值不达标，那么外面再扩一定不达标
 */
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> maxD, minD;
    int maxl, maxr, minl, minr, n;
    vector<int> arr;
    int longestSubarray(vector<int>& nums, int limit) {
        // 做好初始化工作
        arr = nums;
        n = arr.size();
        maxD.resize(n); minD.resize(n);
        maxl = minl = maxr = minr = 0;
        int ans = 0;
        // 开始维护单调队列
        for (int l = 0, r = 0; r <= n; l++)
        {
            while (l <= r && ok(limit, nums[r]))
            {
                push(r++);
            }
            ans = max(ans, r - l);
            pop(l);
        }
        return ans;
    }
    bool ok(int limit, int num)
    {
        int maxi = maxl == maxr ? num : max(arr[maxD[maxl]], num);
        int mini = minl == minr ? num : min(arr[minD[minl]], num);
        return maxi - mini <= limit;
    }
    void push(int r)
    {
        while (maxl < maxr && arr[maxD[maxr - 1]] <= arr[r])
        {
            maxr--;
        }
        maxD[maxr++] = r;
        while (minl < minr && arr[minD[minr - 1]] >= arr[r])
        {
            minr--;
        }
        minD[minr++] = r;

    }
    void pop(int l)
    {
        if (maxl < maxr && maxD[maxl] == l) maxl++;
        if (minl < minr && minD[minl] == l) minl++;
    }
};
int main()
{
    vector<int> arr = {10,1,2,4,7,2};
    Solution sol;
    cout << sol.longestSubarray(arr, 5) << endl;
    return 0;
}