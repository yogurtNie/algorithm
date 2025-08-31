//
// Created by 12472 on 25-5-15.
//
// 括号序列
// 1. 状态方程：d(i, j)表明[i, j]这个序列内部变成正规括号序列所要增加的数量
// 2. 状态转移：
// 当 s[i] match s[j]时，d(i, j) = d(i + 1, j - 1)
// 当 s[i] cannot match s[j]时，d(i, j) = min(d(i, k) + d(k + 1, j))
// 当 s[i] == '(' / '[' cannot match s[j]时，d(i, j) = d(i + 1, j) + ')' / ']'

#include <bits/stdc++.h>
using namespace std;
const int N = 110, INF = 0x3f3f3f3f;
int dp[N][N];
//string str;
char str[N];
bool IsPair(char a, char b)
{
    if (a == '(' && b == ')') return true;
    if (a == '[' && b == ']') return true;
    return false;
}

void print(int i, int j)
{
    if (i > j) return;
    if (i == j)
    {
        if (str[i] == '(' || str[i] == ')') cout << "()";
        else cout << "[]";
        return;
    }
    int ans = dp[i][j];
    // 如果是能够匹配上的情况，且继承了上层状态
    if (IsPair(str[i], str[j]) && ans == dp[i + 1][j - 1])
    {
        cout << str[i];
        print(i + 1, j - 1);
        cout << str[j];
    }
    // 否则依次匹配对应的k值
    for (int k = i; k < j; k++)
    {
        if (ans == dp[i][k] + dp[k + 1][j])
        {
            print(i, k);
            print(k + 1, j);
            return;
        }
    }
}
int main()
{
    int T; scanf("%d", &T);
    getchar();
    while (T--)
    {
        getchar();
        gets(str + 1);
        int n = strlen(str + 1);
        memset(dp, 0, sizeof(dp));

        // 初始化
        for (int i = 1; i <= n; i++)
        {
            dp[i][i] = 1;
            dp[i][i - 1] = 0;
        }

        // // 开始递推
        // for (int len = 2; len <= n; len++)
        // {
        //     for (int i = 1; i + len - 1 <= n; i++)
        //     {
        //         int j = i + len - 1;
        //         dp[i][j] = INF;
        //         if (IsPair(str[i], str[j])) dp[i][j] = min(dp[i][j], dp[i + 1][j - 1]);
        //         for (int k = i; k <= j - 1; k++)
        //         {
        //             dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
        //         }
        //     }
        // }
        for (int i = n - 1; i > 0; i--)
        {
            for (int j  = i + 1; j <= n; j++)
            {
                dp[i][j] = n;
                if (IsPair(str[i], str[j])) dp[i][j] = min(dp[i][j], dp[i + 1][j - 1]);
                for (int k = i; k < j; k++)
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
        }

        // 打印答案
        if (n) print(1, n);
        puts("");
        if (T) puts("");
        //cout << dp[1][n] << endl;
    }
    return 0;
}