//
// Created by 12472 on 25-5-15.
//
// 求能恰好花光m元钱的方案数
// 有n种文具，每种文具对应a_i，仅有1份
// 1. 状态方程：d(i, j)代表的是，前i个文具用光j元的方案数
// 2. 状态转移方程：
// 最终的目的是在之前的状态上抉择买不买这个文具
// 若当前的钱数j大于等于文具，则可以决定吃还是不吃
// 如果吃，则方案数为d(i-1, j-c[i])这么多，如果不吃，则方案数为d(i-1, j)这么多
// 若当前钱数j小于文具，只能继承上层状态
// 边界为 d(i, 0) = 1, d(0, i) = 0, d(i, i) = 1
// 最终答案是d(n, m)
#include<bits/stdc++.h>
using namespace std;
const int N = 110, M = 1e4 + 10, MOD = 998244353;
typedef long long ll;
int c[N];
int dp[N][M];
int main()
{
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> c[i];

    // 初始化
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i <= n; i++) dp[i][0] = 1;

    //开始递推
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if (j < c[i]) dp[i][j] = dp[i - 1][j];
            else dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - c[i]]) % MOD;

        }
    }

    cout << dp[n][m] % MOD << endl;
    return 0;
}