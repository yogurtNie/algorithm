//
// Created by 12472 on 25-6-7.
//
// bool运算
#include<bits/stdc++.h>
using namespace std;
// 返回的两个值：第一个值为，当前运算式子的结果为false的方案数； 第二个值为：当前运算式子为true的方案数
// 根据这两个方案数，划分点选在了每一个逻辑运算符中，分别对左右的可能性进行探讨，并根据逻辑运算符的性质进一步得到本层的t和f方案
pair<int, int> func(string& s, int l, int r, vector<vector<pair<int, int>>>& dp) {
    if (dp[l][r].second != -1 || dp[l][r].first != -1) return dp[l][r];
    if (l == r) {
        dp[l][r].first = s[l] == '0' ? 1 : 0;
        dp[l][r].second = s[l] == '1' ? 1 : 0;
        return dp[l][r];
    }
    int t = 0, f = 0;
    for (int k = l + 1; k < r; k += 2) {
        pair<int, int> left = func(s, l, k - 1, dp);
        pair<int, int> right = func(s, k + 1, r, dp);
        if (s[k] == '&') {
            t += left.second * right.second;
            f += left.first * right.first + left.first * right.second + left.second * right.first;
        }
        else if (s[k] == '|') {
            t += left.second * right.second + left.first * right.second + left.second * right.first;
            f += left.first * right.first;
        }
        else if (s[k] == '^') {
            t += left.first * right.second + left.second * right.first;
            f += left.first * right.first + left.second * right.second;
        }
    }
    return dp[l][r] = make_pair(f, t);
}
int countEval(string s, int result) {
    int len = s.length();
    vector<vector<pair<int, int>>> dp(len + 1, vector<pair<int, int>>(len + 1, {-1, -1}));
    pair<int, int> re = func(s, 0, len - 1, dp);
    if (!result) return re.first;
    return re.second;
}
int main()
{
    string s = "1^0|0|1";
    int result = 0;
    cout << countEval(s, result) << endl;
    return 0;
}
