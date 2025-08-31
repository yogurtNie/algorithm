//
// Created by 12472 on 25-6-9.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
// 状态设计：dp(i)代表的是走到第n级台阶的方案数
// 转移方程：dp(i) = dp(i - 1...k) 不安全台阶为-1
const int MOD = 998244353;
int dp[N];
int pre[N];
int main()
{
    int n, m, k; cin >> n >> m >> k;
    for (int i = 0; i < m; i++)
    {
        int index; cin >> index;
        dp[index] = -1;
    }
    dp[0] = 1;
    pre[0] = 0, pre[1] = 1;
    for (int i = 1; i <= n; i++)
    {
        if (dp[i] == -1)
        {
            pre[i + 1] = pre[i];
            continue;
        }
        int left = max(0, i - k), right = i - 1;
        dp[i] = (pre[right + 1] - pre[left] + MOD) % MOD;
        pre[i + 1] = (dp[i] + pre[i]) % MOD;
    }
    // for (int i = 0; i <= n; i++) cout << pre[i] << " ";
    // cout << endl;
    // for (int i = 0; i <= n; i++) cout << dp[i] << " ";
    //
    // cout << endl;
    cout << dp[n] << endl;
    return 0;
}