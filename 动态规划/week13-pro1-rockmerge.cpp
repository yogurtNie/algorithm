//
// Created by 12472 on 25-5-13.
//
// 需要同时得到最大总分和最小总分，可以递推得到
// 环形石子，需要拆换为链
// 确定状态：d(i, j)代表的状态是，序列[i, j]合并的最小/最大耗费
// 初始化；d(i, i) = 0
// 状态转移方程：d(i, j) = sum(i, j) + min/max(d(i, k), d(k + 1, j))
#include<bits/stdc++.h>
using namespace std;
const int N  = 110;
int pre[2 * N], a[2 * N];
int maxv[2 * N][2 * N], minv[2 * N][2 * N];
const int INF = 0x3f3f3f3f;
int main()
{
    int n; cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        a[i + n] = a[i];
    }
    // 算前缀和
    for (int i = 1; i <= 2 * n - 1; i++)
    {
        pre[i] = pre[i - 1] + a[i];
    }
    // 初始化
    for (int i = 0; i <= 2 * n - 1; i++) maxv[i][i] = minv[i][i] = 0;

    // 开始递推
    for (int len = 2; len <= n; len++)      // 从长度为2的区间开始合并
    {
        for (int i = 1; i + len - 1 <= 2 * n - 1; i++) // 从开头开始递推
        {
            int j = i + len - 1;
            int temp1 = -INF, temp2 = INF;
            for (int k = i; k < j; k++)
            {
                temp1 = max(temp1, maxv[i][k] + maxv[k + 1][j]);
                temp2 = min(temp2, minv[i][k] + minv[k + 1][j]);
            }
            maxv[i][j] = pre[j] - pre[i - 1] + temp1;
            minv[i][j] = pre[j] - pre[i - 1] + temp2;
        }
    }

    // 输出结果
    int maxAns = 0, minAns = INF;
    for (int i = 1; i <= n; i++)
    {
        maxAns = max(maxAns, maxv[i][i + n - 1]);
        minAns = min(minAns, minv[i][i + n - 1]);
    }
    cout << minAns << endl;
    cout << maxAns << endl;
    return 0;

}
