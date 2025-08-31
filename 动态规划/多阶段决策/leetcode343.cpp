//
// Created by 12472 on 25-5-29.
//
// 可以将某个整数拆成两个数，i * j，如果此时是最优解，那么i、j接下来的拆法必定是各自的最优解
// dp[i]代表 i 这个数的最大乘积
// dp[i] = max(dp[k] * dp[j]), k+j == i
// 边界，dp[1] = 1
#include<bits/stdc++.h>
using namespace std;
const int N = 60;
vector<int> dp(N);
int integerBreak(int n) {
    int& ans = dp[n];
    if (ans != 0) return ans;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            int temp = max(integerBreak(i - j) * j, (i - j) * j);
            ans = max(temp, ans);
        }
    }
    for (int i = 1; i <= n; i++) cout << dp[i] << " ";
    return ans;
}

int main()
{
    int n; cin >> n;
    dp[1] = 1;
    integerBreak(n);
    return 0;
}