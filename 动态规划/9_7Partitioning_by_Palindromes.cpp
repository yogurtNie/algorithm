//
// Created by 12472 on 25-5-9.
//
// 针对一个字符串，将其拆解为最小的回文字符串，输出最后的分组数
// 1. 设计状态：d(i)代表的是，以i结尾的字符串中最小的分组数
// 2. 状态转移方程：d(i) = min(d(j) + 1 | s[j+1 ~ i])是回文串
// 3. 复杂度分析：对于每个i，都需要遍历一遍比i小的j，为n^2的量级
// 4. 优化：可以先将s[i ~ j]是否是回文串预处理，用dp的思想
// dp[i][j]，当i == j时一定是回文串，接下来按照奇 / 偶的顺序，依次向外延伸
// 奇数：dp[i-1][j+1] = dp[i][j] if (s[i-1] == s[j+1]) while (i-1 >= 0 && j+1 <= n)
// 偶数: dp[i][j+1] dp[i-1][j+2] if (s[i-1] == s[j+2])
#include<bits/stdc++.h>
using namespace std;

const int N = 1010;
string str;
bool dp[N][N];           // 用于预处理字符串是否是回文
int d[N];               // 状态转移

int main()
{
    int T; cin >> T;
    while (T--)
    {
        cin >> str;
        memset(dp, 0, sizeof(dp));
        memset(d, 0, sizeof(d));
        int L = str.length();
        for (int i = 1; i <= L; i++) dp[i][i] = 1;
        // 预处理某个区间的字符串是否是回文:很重要，要记住
        // 长度为2的子串单独比较
        for (int i = 1; i <= L; i++)
            dp[i][i + 1] = (str[i - 1] == str[i]);

        for (int len = 2; len <= L; len++)          // 外层区间：字符串长度
        {
            for (int i = 1; i + len - 1 <= L; i++)   // 内层区间：起始下标
            {
                dp[i][i + len - 1] = (str[i - 1] == str[i + len - 2]) && dp[i + 1][i + len - 2];
            }
        }

        // for (int i = 0; i <= L; i++)
        // {
        //     for (int j = 0; j <= L; j++)
        //     {
        //         cout << dp[i][j] << " ";
        //     }
        //     cout << endl;
        // }

        for (int i = 1; i <= L; i++)
        {
            // 设置为最大值
            d[i] = i;
            for (int j = 0; j < i; j++)
            {
                if (dp[j + 1][i]) d[i] = min(d[i], d[j] + 1);
            }
        }
        cout << d[L] << endl;
    }
}