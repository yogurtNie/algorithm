//
// Created by 12472 on 25-6-6.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 20;
int d[1 << N][N];
int mp[N][N];
int n;

// s代表目前的状态，置1表示已经去过，置0表示还未去过；i表示目前在哪个村
int dp(int s, int i)
{
    // 如果全部走过了，现在只需要回来
    if (s == ((1 << n) - 1)) return mp[i][0];
    if (d[s][i] != 0) return d[s][i];

    int ans = INT32_MAX;            // 要用未污染的状态一次性走完所有“深搜”得到的路
    for (int j = 0; j < n; j++)
    {
        // 位运算的优先级低到你难以想像，请多加括号
        if ((s & (1 << j)) == 0)  // 还未去过的村庄
        {
            ans = min(ans, mp[i][j] + dp(s ^ (1 << j), j));
        }
    }

    d[s][i] = ans;

    return ans;
}


int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++ )
            cin >> mp[i][j];
    cout << dp(1, 0) << endl;
    return 0;
}