//
// Created by 12472 on 25-5-18.
//
// 问询问题，一个问题有m个特征构成，有n个问题，问最少确定几个特征一定可以唯一标识某一个问题
// 最多肯定是问m次可以唯一标识
// 1. 对于这个心里想着的问题，记为Q，已经问过的特征不用再问，记已经问过的特征为s，那么记p
// 为，s中问过的特征，在Q中具备的个数，那么定义状态d(s, p)为，已经问过s个特征，其中p个特征
// 具备所需要的最小问询次数。
// 2. 状态转移方程：假设下一个要问询的特征是k，那么有
// d(s, p) = min{ d(s^(1 << k), p^(1 << k)), d(s^(1 << k), p)) } + 1;
// 3. 边界：如果已经找到一个物品满足，匹配p中的所有特征，且不匹配s-p中的所有特征，那么d(s, p) = 0
// 也就是无需继续问下去了
#include<bits/stdc++.h>
using namespace std;
const int M = 13, N = 130, INF = 0x3f3f3f3f;
int d[(1 << M) + 10][(1 << M) + 10], cnt[(1 << M) + 10][(1 << M) + 10];
int m, n;
int b[N];
// 将二进制字符串转成二进制整数，右边低位左边高位
int BtoT(const char* s)
{
    int ans = 0;
    for (int i = m - 1; i >= 0; i--)
    {
        if (s[i] == '1') ans |= (1 << (m - i - 1));
    }
    return ans;
}
int dp(int s, int a)
{
    if (cnt[s][a] == 1) return 0;
    // 如果有两个物品，最优还需询问一次
    if (cnt[s][a] == 2) return 1;
    //else if (cnt[s][a] == 0) return INF;
    int& ans = d[s][a];
    if (ans >= 0) return ans;
    ans = m;
    // 开始问下一个还未提问过的特征
    for (int k = 0; k < m; k++)
    {
        if ((s & (1 << k)) == 0)
        {
            if (cnt[s ^ (1 << k)][a ^ (1 << k)] >= 1 && cnt[s ^ (1 << k)][a] >= 1)
            {
                int tmp = max(dp(s ^ (1 << k), a ^ (1 << k)), dp(s ^ (1 << k), a));
                ans = min(ans, tmp + 1);
            }
        }
    }
    return ans;
}
int main()
{
    while (cin >> m >> n)
    {
        if (m == 0) break;
        for (int i = 0; i <= (1 << m); i++)
            for (int j = 0; j <= (1 << m); j++)
                cnt[i][j] = 0;

        for (int i = 0; i < n; i++)
        {
            string str;
            cin >> str;
            b[i] = BtoT(str.c_str());
            // cout << b[i] << "\n";
        }
        // 找到询问为s时，符合a的所有物品
        for (int s = 0; s < (1 << m); s++)
        {
            for (int i = 0; i < n; i++)
            {
                // 该物品的所有具备的特征是s的子集
                int a = s & b[i];
                cnt[s][a]++;
            }
        }
        // 初始化
        for (int i = 0; i < (1 << m); i++)
            for (int j = 0; j < (1 << m); j++)
                d[i][j] = -1;


        cout << dp(0, 0) << endl;
    }
    return 0;
}