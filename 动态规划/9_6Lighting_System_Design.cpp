//
// Created by 12472 on 25-5-9.
//
// 灯泡有四个值：电压值V，直接影响亮度；电源费用K，需要决策，因为要省钱；灯泡本身的费用C；以及所需灯泡的数量L
// 现在需要将可以换下的灯泡中，选电压最高的换上；便于省钱 + 提升效率
// 1.状态方程：d(i)代表的是，前i个灯泡的最小开销
// 2.状态转移方程：d(i) = min(d[j] + (pre[i] - pre[j]) * c[i] + k[i])
#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
int pre[N];
int dp[N];
struct node
{
    int v, k, c, l;
}a[N];
bool cmp(node a, node b)
{
    return a.v < b.v;
}
int main()
{
    int n;
    while (cin >> n)
    {
        if (!n) break;
        pre[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i].v >> a[i].k >> a[i].c >> a[i].l;
        }
        memset(dp, 0x3f, sizeof(dp));
        sort(a + 1, a + n + 1, cmp);
        for (int i = 1; i <= n; i++)
            pre[i] = a[i].l + pre[i - 1];
        dp[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            //初始化全部变成最高的电压值
            dp[i] =  pre[i] * a[i].c + a[i].k;
            for (int j = 1; j < i; j++)
            {
                if (dp[i] > dp[j] + (pre[i] - pre[j]) * a[i].c + a[i].k)
                    dp[i] = dp[j] + (pre[i] - pre[j]) * a[i].c + a[i].k;
            }
        }
        cout << dp[n] << endl;
    }
}