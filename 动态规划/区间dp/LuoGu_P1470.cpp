//
// Created by 12472 on 25-6-8.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 55;
int dp[N][N];
int main()
{
    string s; cin >> s;
    int n = s.length();
    // 初始化
    for (int i = 0; i < n; i++)
        dp[i][i] = 1;
    for (int i = 0; i < n - 1; i++)
    {
        if (s[i] == s[i + 1]) dp[i][i + 1] = 1;
        else dp[i][i + 1] = 2;
    }

    // 递推
    for (int l = n - 3; l >= 0; l--)
    {
        for (int r = l + 2; r < n; r++)
        {
            dp[l][r] = INT32_MAX;
            // if (s[l] == s[r]) dp[l][r] = dp[l + 1][r - 1] + 1;
            // 一定得这么写，因为有特殊情况：AAAAA，如果按上面注释掉的写法，会算成3
            // 区别在于，上面将两个端点都直接确定下来，然后将中间的状态和两端状态切割开来了，但是应该是
            // 两端状态是否解决取决于大任务的决策，但是中间任务是否解决也需要大任务决策，所以要保留一个端点来确认中间状态和两端状态的关系
            if (s[l] == s[r]) dp[l][r] = dp[l][r - 1];
            for (int k = l; k < r; k++)
            {
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r]);
            }
        }
    }

    cout << dp[0][n - 1] << endl;
    return 0;
}