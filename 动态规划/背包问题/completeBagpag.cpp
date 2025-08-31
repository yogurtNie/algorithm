//
// Created by 12472 on 25-5-30.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
typedef long long ll;
int V[N], W[N];
int dp[N][N];       // dp[i][j]代表的是第i个物品放到容量为j的最大价值


int main() {
    int n, v; cin >> n >> v;
    for (int i = 0; i < n; i++) {
        cin >> W[i] >> V[i];
    }
    // 初始化
    for (int i = W[0]; i <= v; i++) {
        int num = i / W[0];
        dp[0][i] = num * V[0];
    }
    // 递推过程
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= v; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= W[i]) dp[i][j] = max(dp[i][j], dp[i][j - W[i]] + V[i]);
        }
    }
    cout << dp[n - 1][v] << endl;
    return 0;
}