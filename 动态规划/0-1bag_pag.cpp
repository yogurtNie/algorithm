//
// Created by 12472 on 25-5-10.
// week12 - problem1
// 1. 状态方程：dp(i)代表的是还剩下i容量的背包时能装下的最大背包容量
// 2. 状态转移方程：dp(i) = max(dp(i), dp(i - V[i]) + w[i])
#include<bits/stdc++.h>
using namespace std;
const int N = 5e3 + 10;
typedef long long ll;

int dp[N];

int main()
{
    int n, C; cin >> n >> C;

    for (int i = 1; i <= n; i++)
    {
        int w, v; cin >> w >> v;
        for (int j = C; j >= 0; j--)
        {
            if (j >= w) dp[j] = max(dp[j], dp[j - w] + v);
        }
    }
    cout << dp[C] << endl;
    return 0;
}