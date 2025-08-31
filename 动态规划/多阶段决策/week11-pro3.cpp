//
// Created by 12472 on 25-6-10.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
typedef long long ll;
ll dp[3][N];
ll mp[3][N];

int main()
{
    int n; cin >> n;
    for (int i = 0; i < 3; i ++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> mp[i][j];
        }
    }

    // 初始化，dp[0][j]和dp[1][j]都默认是0
    // 直接开始递推
    for (int i = 2; i <= n; i++ )
    {
        for (int j = 0; j < 3; j++)
        {
            dp[j][i] = 0x3f3f3f3f3f3f3f3fll;
            for (int k = 0; k < 3; k++)
            {
                dp[j][i] = min(dp[j][i], dp[k][i - 1] + (ll)abs(mp[j][i] - mp[k][i - 1]));
            }
        }
    }
    // for (int i = 0; i <= 2; i++)
    // {
    //     for (int j = 0; j <= n; j++)
    //         cout <<dp[i][j] << " ";
    //     cout << endl;
    // }
    cout << min(dp[0][n], min(dp[1][n], dp[2][n])) << endl;
    return 0;
}