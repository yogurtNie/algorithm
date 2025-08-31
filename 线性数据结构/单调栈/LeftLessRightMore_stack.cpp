//
// Created by 12472 on 25-6-19.
//
/*
 * leetCode P962 最大宽度坡
 * 给定一个整数数组A，坡是元组(i, j)，其中i < j且A[i] <= A[j]。这样的坡的宽度为j - i。找出中的坡的最大宽度，如果不存在，返回 0
 * 左侧找最小，右侧找最大
 * 测试链接：https://leetcode.cn/problems/maximum-width-ramp/description/
 */
// 不读题的下场就是白写
// 解法：将入栈和出栈的过程解耦，入栈过程维护一个递减栈，是因为如果递增，可证该区间必然不是最好区间
// 出栈：从右往左遍历，可证如果此时能和栈中某元素构成增加区间，必然是该元素的最好答案
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        int n = nums.size();
        vector<int> st(n);
        // int top = 0;
        int top = 1;
        // 入栈过程，找递减
        for (int i = 0; i < n; i++)
        {
            // if (top == 0) st[top++] = i;
            // else
            // {
                if (nums[i] < nums[st[top - 1]])
                    st[top++] = i;
            // }
        }
        // 出栈过程
        int ans = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            if (top == 0) break;
            while (nums[i] >= nums[st[top - 1]])
            {
                ans = max(ans, i - st[--top]);
                if (top == 0) break;
            }
        }
        return ans;
    }
};

int main()
{
    vector<int> nums = {9,8,1,0,1,9,4,0,4,1};
    Solution s;
    cout << s.maxWidthRamp(nums) << endl;
    return 0;
}

// int maxWidthRamp(vector<int>& nums) {
//     int n = nums.size();
//     vector<int> st1(n); // 维护一个单调递增栈，用来找左侧第一个比它小的
//     vector<int> st2(n); // 维护一个单调递减栈，用来找右侧第一个比它大的
//     vector<int> less(n);
//     vector<int> great(n);
//     int top1 = 0, top2 = 0;
//     int cur1 = 0, cur2 = 0;
//     for (int i = 0; i < n; i++)
//     {
//         // 单调递增栈
//         while (top1 > 0 && nums[st1[top1 - 1]] > nums[i])
//         {
//             cur1 = st1[--top1];
//             less[cur1] = top1 == 0 ? cur1 : st1[top1 - 1];
//         }
//         st1[top1++] = i;
//         // 单调递减栈
//         while (top2 > 0 && nums[st2[top2 - 1]] < nums[i])
//         {
//             cur2 = st2[--top2];
//             great[cur2] = i;
//         }
//         st2[top2++] = i;
//     }
//     while (top1 > 0)
//     {
//         cur1 = st1[--top1];
//         less[cur1] = top1 == 0 ? cur1 : st1[top1 - 1];
//     }
//     while (top2 > 0)
//     {
//         cur2 = st2[--top2];
//         great[cur2] = cur2;
//     }
//     int ans = 0;
//     for (int i = 0; i < n; i++)
//     {
//         ans = max(ans, great[i] - less[i]);
//     }
//     return ans;
// }