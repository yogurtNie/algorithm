//
// Created by 12472 on 25-6-18.
//
/*
 * 给定一个仅包含 0 和 1 、大小为 rows x cols 的二维二进制矩阵，
 * 找出只包含 1 的最大矩形，并返回其面积。
 */
// 压缩数组
// 解法最优解：每次遍历的含义是：找到以该行做底的矩阵最小值（维护一个连续数组，里面记录着该列在本行累积的连续1的个数）
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<int> arr(m, 0);
        vector<int> st(m, 0);
        int left = 0, right = 0, cur = 0;
        int top = 0, ans = 0;
        for (int i = 0; i < n; i++)
        {
            // 先求解得到连续数组
            for (int j = 0; j < m; j++)
            {
                if (matrix[i][j] == '1') arr[j]++;
                else arr[j] = 0;
            }
            // 开始用单调栈维护答案
            for (int j = 0; j < m; j++)
            {
                while (top > 0 && arr[st[top - 1]] >= arr[j])
                {
                    cur = st[--top];
                    left = top == 0 ? -1 : st[top - 1];
                    right = j;
                    ans = max(ans, (right - left - 1) * arr[cur]);
                }
                st[top++] = j;
            }
            while (top > 0)
            {
                cur = st[--top];
                left = top == 0 ? -1 : st[top - 1];
                ans = max(ans, (m - left - 1) * arr[cur]);
            }
        }
        return ans;
    }
};

int main()
{
    vector<vector<char>> matrix = {{'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'}};
    Solution sol;
    cout << sol.maximalRectangle(matrix);
    return 0;
}