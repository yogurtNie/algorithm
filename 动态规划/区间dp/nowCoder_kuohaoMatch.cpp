//
// Created by 12472 on 25-6-8.
//
#include <climits>
#include <cstdint>
#include <iostream>
#include <string>
using namespace std;
const int N = 110;
int dp[N][N];

// //方法1：递归
// // 返回值的意义是，在区间l...r上最小的括号插入数量
// int func(string& str, int l, int r) {
//     if (l > r) return 0;
//     if (l == r) return 1;
//     if (l + 1 == r) {
//         if ((str[l] == '(' && str[r] == ')' )||(str[l] == '[' && str[r] == ']'))
//             return 0;
//         return 2;
//     }

//     if (dp[l][r] != -1) return dp[l][r];

//     // 直接按划分点做讨论，包括两端点
//     int ans = INT_MAX;
//     if ((str[l] == '(' && str[r] == ')' )||(str[l] == '[' && str[r] == ']')) ans = func(str, l + 1, r - 1);
//     for (int k = l; k < r; k++) {       // 其实就是两区间划分，不需要考虑越界的事情
//         ans = min(ans, func(str, l, k) + func(str, k + 1, r));
//     }
//     return dp[l][r] = ans;

// }


int main() {
    string str; cin >> str;
    int len = str.size();
    // cout << func(str, 0, len - 1) << endl;
    // 方法2：递推

    // 初始化成：
    for (int i = 0; i < len - 1; i++) {
        dp[i][i] = 1;
        if ((str[i] == '(' && str[i + 1] == ')') || (str[i] == '[' && str[i + 1] == ']')) dp[i][i + 1] = 0;
        else dp[i][i + 1] = 2;
    }
    dp[len - 1][len - 1] = 1;

    // 开始递推：递推顺序是，从后往前，后左往右
    for (int l = len - 3; l >= 0; l--) {
        for (int r = l + 2; r < len; r++) {
            dp[l][r] = INT_MAX;
            // 很容易错：除了划分点，不要忘记对区间两端点进行讨论
            if ((str[l] == '(' && str[r] == ')') || (str[l] == '[' && str[r] == ']'))
                dp[l][r] = dp[l + 1][r - 1];
            for (int k = l; k < r; k++) {
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r]);
            }
        }
    }

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
            cout << dp[i][j] << " ";
        cout << endl;
    }

    cout << dp[0][len - 1] << endl;
    return 0;
}