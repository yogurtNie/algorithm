//
// Created by 12472 on 25-5-13.
//
// 括号序列，如何定义状态：d(i, j)表明，在序列[i, j]中使其合法需要添加的最小数量
// 状态转移方程：d(i, j) = min(d(i, k) + d(k + 1, j)) 拆解成子问题
// 当s本身符合合法序列，则d(i, j) = min(d(i, j), d(i + 1, j - 1)) 注意，这里需要定义空的序列（当i+1 > j-1）时为0
// 需要定义初始值d(i, i) = 1，这样当左右的情况为[S / (S / S] / S)时，就可以不用额外考虑
// 最终的答案为d(1, n)
#include<bits/stdc++.h>
using namespace std;
string str;
const int N = 110, INF = 0x3f3f3f3f;
int dp[N][N];
bool IsPair(char a, char b)
{
    if (a == '(' && b == ')') return true;
    if (a == '[' && b == ']') return true;
    return false;
}

int main()
{
    cin >> str;
    int n = str.length();
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; i++) dp[i][i] = 1;

    // 开始递推
    for (int len = 2; len <= n; len++)
    {
        for (int i = 0; i + len - 1 < n; i++)
        {
            int j = i + len - 1;
            dp[i][j] = INF;
            if (IsPair(str[i], str[j])) dp[i][j] = min(dp[i][j], dp[i + 1][j - 1]);
            int temp = INF;
            for (int k = i; k < j; k++)
                temp = min(temp, dp[i][k] + dp[k + 1][j]);
            dp[i][j] = min(dp[i][j], temp);
        }
    }

    cout << dp[0][n - 1] << endl;
}
