//
// Created by 12472 on 25-5-10.
//
// 本质上是一类DAG问题
// 很重要！DAG问题代表的是从i倒推到0时的最大路径
// 1. 状态方程：dp(i)代表的是从i出发前往终点：0 的最大路径（最大重量）
// 2. 转移方程：dp(i) = max{dp(i - V[j] | (i, j) ∈ E}
#include <bits/stdc++.h>
using namespace std;
const int N = 5010, INF = 0x3f3f3f3f;
int d[N];
int W[N], C[N];
int n;
int dp(int i)
{
    int& ans = d[i];
    if (ans != -1) return ans;      // 区间dp，表明搜索过
    ans = -INF;
    for (int j = 1; j <= n; j++)
    {
        if (i >= W[j]) ans = max(ans, dp(i - W[j]) + C[j]);
    }
    return ans;
}

int main()
{
    int V; cin >> n >> V;
    for (int i = 1; i <= n; i++)
    {
        cin >> W[i] >> C[i];
    }
    memset(d, -1, sizeof d);
    d[0] = 0;
    int ans = dp(V);
    cout << (ans <= 0 ? 0 : ans)  << endl;
    // for (int i = 0; i <= V; i++) cout << d[i] << " ";
    // cout << endl;
    return 0;
}