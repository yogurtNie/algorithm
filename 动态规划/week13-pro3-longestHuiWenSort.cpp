//
// Created by 12472 on 25-5-13.
//
//
// Created by 12472 on 25-5-9.
//
// 针对一个字符串，输出其中最长的回文字符串
// d(i, j)代表的是[i, j]这个序列中最大的回文子串长度
// 状态转移：d(i, j) = max(
// 1. 设计状态：d(i)代表的是，以i结尾的字符串中最小的分组数
// 2. 状态转移方程：d(i) = min(d(j) + 1 | s[j+1 ~ i])是回文串
// 3. 复杂度分析：对于每个i，都需要遍历一遍比i小的j，为n^2的量级
// 4. 优化：可以先将s[i ~ j]是否是回文串预处理，用dp的思想
// 不知道为啥不行
#include<bits/stdc++.h>
using namespace std;

const int N = 4010;
string str;
bool dp[N][N];           // 用于预处理字符串是否是回文

int main()
{
    cin >> str;
    int n = str.size();
    memset(dp, 0, sizeof(dp));
    // 初始化，所以长度为1的字符都是回文
    for (int i = 0; i < n; i++) dp[i][i] = true;
    for (int i = 0; i < n - 1; i++)
        if (str[i] == str[i + 1]) dp[i][i + 1] = true;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            dp[i][j] = true;


    // 开始递推
    for (int len = 3; len <= n; len++)
    {
        for (int i = 0; i + len - 1 < n; i++)
        {
            int j = i + len - 1;
            dp[i][j] = (str[i] == str[j]) && dp[i + 1][j - 1];
        }
    }

    int ans = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (dp[i][j]) ans = max(ans, j - i + 1);
        }
    }
    cout << ans << endl;
    return 0;

}