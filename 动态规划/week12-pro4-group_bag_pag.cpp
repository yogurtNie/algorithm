//
// Created by 12472 on 25-5-11.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10, M = 110;
typedef long long ll;
int W[M][N], C[M][N];
int dp[N][N];
int cnt[M];
int main()
{
    int n, V; cin >> n >> V;
    int maxK = 0;
    for (int i = 1; i <= n; i++)
    {
        int w, c, k; cin >> w >> c >> k;
        maxK = max(maxK, k);
        cnt[k]++;
        W[k][cnt[k]] = w; C[k][cnt[k]] = c;

    }

    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= cnt[i]; j++)
    //     {
    //         cout << W[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    // 分组背包的朴素算法
    for (int i = 1; i <= maxK; i++)
    {
        for (int j = 1; j <= V; j++)
        {
            // 一定要记得输出化该组的物品
            dp[i][j] = dp[i - 1][j];
            for (int k = 1; k <= cnt[i]; k++)
            {
                if (j >= W[i][k]) dp[i][j] = max(dp[i][j], dp[i - 1][j - W[i][k]] + C[i][k]);
            }
        }
    }
    // // 调试
    // for (int i = 0; i <= n; i++)
    // {
    //     for (int j = 0; j <= V; j++)
    //     {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // 输出结果
    cout << dp[maxK][V] << endl;
}
