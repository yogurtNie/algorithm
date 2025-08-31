//
// Created by 12472 on 25-5-14.
//
// 状态定义：dp(i, j)表示区间[i, j]中最长的回文子串序列
// 状态转移：dp(i, j) = max(dp(i+1, j-1) + 2, dp(i, j)) 当str[i] == str[j]
// 当str[i] != str[j] dp(i, j) = max(dp(i + 1, j), dp(i, j - 1))
#include<bits/stdc++.h>
using namespace std;
const int N = 4010;
int dp[N][N];
string str;

int main()
{
    cin >> str;
    int n = str.size();
    // 初始化
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; i++) dp[i][i] = 1;

    // 递推
    for (int len = 2; len <= n; len++)
    {
        for (int i = 0; i + len - 1 < n; i++)
        {
            int j = i + len - 1;
            if (str[i] == str[j]) dp[i][j] = max(dp[i][j], dp[i + 1][j - 1] + 2);
            else dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
        }
    }

    cout << dp[0][n - 1] << endl;
    return 0;
}