//
// Created by 12472 on 25-6-7.
//
// 要能想到，对于一个没有相交线的三角形划分，其本质是在某个区间上取相邻的三个数组成三角形
    // 再抽象一点，就是求某一区间上可重合边界的最小乘积和
#include<bits/stdc++.h>
using namespace std;
int f(vector<int>& values, int l, int r, vector<vector<int>>& dp) {
    if (dp[l][r] != -1) return dp[l][r];
    if (l == r || l + 1 == r) return dp[l][r] = 0;         // 无法拼成三角形
    if (l + 2 == r) return dp[l][r] = values[l] * values[l + 1] *  values[r];

    // 开始处理这个区间
    int ans = 0xffffffff;
    for (int i = l + 1; i < r; i++) {
        ans = min(ans, f(values, l, i, dp) + f(values, i, r, dp) + values[l] * values[r] * values[i]);
    }
    return dp[l][r] = ans;
}
int minScoreTriangulation(vector<int>& values) {
    int n = values.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return f(values, 0, n - 1, dp);
}

int main()
{
    vector<int> values = {3,7,4,5};
    values.in
    minScoreTriangulation(values);
    return 0;
}
