//
// Created by 12472 on 25-6-7.
//
// 字符串变回文的最小插入次数
#include <bits/stdc++.h>
using namespace std;
int minInsertions(string s) {
    int len = s.length();
    vector<vector<int>> dp(len + 1, vector<int>(len + 1));
    for (int i = 0; i <= len; i++)
        for (int j = 0; j <= len; j++)
            dp[i][j] = 0;
    for (int i = 0; i < len - 1; i++)
        if (s[i] == s[i + 1]) dp[i][i + 1] = 1;

    for (int i = len - 3; i >= 0; i--) {
        for (int j = i + 2; j <= len - 1; j++) {
            if (s[i] == s[j]) {dp[i][j] = dp[i + 1][j - 1];}
            else {dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;}
        }
    }

    return dp[0][len - 1];
}

int main()
{
    string s = "mbadm";
    cout << minInsertions(s) << endl;
    return 0;
}