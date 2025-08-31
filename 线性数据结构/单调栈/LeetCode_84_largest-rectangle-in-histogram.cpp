//
// Created by 12472 on 25-6-18.
//
/*给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
求在该柱状图中，能够勾勒出来的矩形的最大面积.
 */
// 分析：为什么即使最后不修正，只是相等位置弹出，最后的答案也是对的？
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> st(n);
        int top = 0;
        int ans = 0;
        int left = 0, right = 0, cur = 0;
        for (int i = 0; i < n; i++)
        {
            // 维护单调递增栈
            while (top > 0 && heights[st[top - 1]] >= heights[i])
            {
                cur = st[--top];
                left = top == 0 ? -1 : st[top - 1];
                right = i;
                ans = max(ans, (right - left - 1) * heights[cur]);
            }
            st[top++] = i;
        }
        // 清算
        while (top > 0)
        {
            cur = st[--top];
            left = top == 0 ? -1 : st[top - 1];
            ans = max(ans, (n - left - 1) * heights[cur]);
        }
        return ans;
    }
};

int main()
{
    vector<int> heights = {2,4};
    Solution solution;
    cout << solution.largestRectangleArea(heights) << endl;
    return 0;
}