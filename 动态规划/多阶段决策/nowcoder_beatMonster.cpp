//
// Created by 12472 on 25-6-9.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 510;
int money[N], power[N];
int dp[N * 1000];
int main()
{
    int n; cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> power[i] >> money[i];
    }
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += money[i];
        for (int j = 0; j < n * 1000; j++)
            dp[j] = INT_MIN;
    }
    // 计算一下sum的规模（用于横轴，最少花的钱数）

    // 初始化
    for (int j = 0; j <= sum; j++)
    {
        if (j >= money[0]) dp[j] = power[0];
    }

    // 开始递推
    for (int i = 1; i < n; i++)
    {
        for (int j = sum; j >= 0; j--)
        {
            int cur = INT_MIN;
            if (dp[j] >= power[i]) cur = dp[j];
            if (j >= money[i] && dp[j - money[i]] != INT_MIN)
            {
                cur = max(cur, dp[j - money[i]] + power[i]);
            }
            dp[j] = cur;
        }
    }

    for (int j = 0; j <= sum; j++)
    {
        if (dp[j] != INT_MIN)
        {
            cout << j << endl;
            break;
        }
    }
}