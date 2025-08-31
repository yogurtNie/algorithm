//
// Created by 12472 on 25-6-22.
//
/*
 * 给你一个m x n的二进制矩阵mat，请你返回有多少个子矩形的元素全部都是 1
 * 拿到一个位置两边比它小的位置时，计算【以这一列作为底】的矩阵中，从此高度到max(left, right) + 1高度计数的所有子矩阵
 * https://leetcode.cn/problems/count-submatrices-with-all-ones/
 */
// 相等的时候怎么处理？ —— 只释放，不计算，因为会重复算
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        vector<int> st(n, 0), arr(n, 0);
        int top = 0, cur = 0, left = 0, height = 0;
        int ans = 0;
        for (int i = 0; i < m; i++)
        {
            // 计算以该行为底的累积柱形
            for (int j = 0; j < n; j++)
            {
                if (mat[i][j] == 1) arr[j] += 1;
                else arr[j] = 0;
            }
            // 开始对本行进行单调栈处理
            for (int j = 0; j < n; j++)
            {
                while (top > 0 && arr[st[top - 1]] >= arr[j])
                {
                    cur = st[--top];
                    if (arr[j] == arr[cur]) continue;
                    left = top == 0 ? -1 : st[top - 1];
                    height = left == -1 ? arr[j] : max(arr[left], arr[j]);
                    ans += (j - left - 1) * (j - left) * (arr[cur] - height) / 2;
                }
                st[top++] = j;
            }
            while (top > 0)
            {
                cur = st[--top];
                left = top == 0 ? -1 : st[top - 1];
                height = left == -1 ? 0 : arr[left];
                ans += (n - left - 1) * (n - left) * (arr[cur] - height) / 2;
            }
        }
        return ans;
    }
};

int main()
{
    vector<vector<int>> mat = {{1,1,1,1,1,1}};
    Solution sol;
    cout << sol.numSubmat(mat) << endl;
    return 0;
}