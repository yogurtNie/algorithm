//
// Created by 12472 on 25-5-29.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 5e3 + 10, INF = 0x3f3f3f3f;
// int dp[N][N];
int V[N], W[N];
int dp[N];
int main() {
    int m, n; cin >> m >> n;

    for (int i = 1; i <= m; i++) cin >> W[i];
    for (int i = 1; i <= m; i++) cin >> V[i];
    //
    // for (int i = 1; i <= m; i++) {
    //     for (int j = 0; j <= n; j++) {
    //         dp[i][j] = dp[i - 1][j];
    //         if (j >= W[i]) dp[i][j] = max(dp[i][j - W[i]] + V[i], dp[i][j]);
    //     }
    // }
    // //
    // // for (int i = 0; i <= m; i++)
    // // {
    // //     for (int j = 0; j <= n; j++)
    // //         cout << dp[i][j] << " ";
    // //     cout << endl;
    // // }
    // cout << dp[m][n] << endl;
    for (int i = 1; i <= m; i++)
    {
        for (int j = n; j >= W[i]; j--)
        {
            dp[j] = max(dp[j], dp[j - W[i]] + V[i]);
        }
    }
    cout << dp[n] << endl;
    return 0;
}