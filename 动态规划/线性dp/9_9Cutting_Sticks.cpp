//
// Created by 12472 on 25-5-15.
//
// 切割木棍：切割点有不同的排列顺序，选择不同的顺序切割得到的总和不同，求最小切割成本
// 1. 状态方程：d(i, j)代表[i, j]这个区间中切割的最小成本
// 2. 状态转移：考虑能不能将这个问题划分成一些子问题
// 假设在这个区间内有k个切割点，此时，d(i, j) = min(d(i, k) + d(k, j) + sum(i, j))
// 3. 边界：d(i, i) = 0, d(i, i + 1) = 0, 答案为d(0, l)
// 一开始考虑的思路：遍历l，但是后来想想没必要，因为木棍只会在切割点断开，所以其余的点考虑了也没用
// 那么只需要在原本的n个切割点的两端加入0和l，编号对应0和n+1即可
#include<bits/stdc++.h>
using namespace std;
const int N = 55, INF = 0x3f3f3f3f;
int dp[N][N];
int cntPoint[N];

int main()
{
    int l, n;
    while (cin >> l)
    {
        if (!l) break;
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> cntPoint[i];
        cntPoint[0] = 0; cntPoint[n + 1] = l;

        for (int i = n; i >= 0; i--)
        {
            for (int j = i + 2; j <= n + 1; j++)
            {
                int temp = INF;
                for (int k = i + 1; k < j; k++)
                {
                    temp = min(temp, dp[i][k] + dp[k][j] + cntPoint[j] - cntPoint[i]);
                }
                dp[i][j] = temp;
            }
        }

        // for (int i = 0; i <= n + 1; i++)
        // {
        //     for (int j = 0; j <= n + 1; j++)
        //         cout << dp[i][j] << " ";
        //     cout << endl;
        // }
        // cout << endl;
        cout << "The minimum cutting is ";
        cout << dp[0][n + 1] << "." << endl;
    }
}
