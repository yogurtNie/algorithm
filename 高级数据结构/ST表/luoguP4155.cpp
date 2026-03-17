//
// Created by 12472 on 25-12-6.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int line[N << 2][3];          // 扩大4倍，用于存储所有的化环为线，以及后续多加一个用于判定是否达到终点的循环
int st[N][20];                  // 列数是N取log，20的数量级是10^6，绝对够
int n, m;
int ans[N];
// 计算n需要最大的power/col号是多少，也就是小于等于x的最大二的幂次
int log2(int x)
{
    int p = 0;
    while ((1 << p) <= (x >> 1))
        p++;
    return p;
}
void build(int i);
int jump(int i, int power);
// compute
void compute()
{
    int power = log2(n);
    build(power);            // 进行拆环和多加，再进行内部的初始化与ST表建表
    for (int i = 1; i <= n; i++)
        ans[line[i][0]] = jump(i, power);
}
// 定义排序规则，按照line[i][1]的大小来排序
bool cmp(const int a[3], const int b[3])
{
    return a[1] < b[1];
}

// 建立ST表
void build(int p)
{
    // 先对line做初始化
    // 我们在最开始的时候已经将n个范围和序号已经填好了，且是按照拆环为线的方式填充的
    for (int i = 1; i <= n; i++)
        if (line[i][1] > line[i][2])
            line[i][2] += m;            // 比如，将[6, 1]转换为[6, 9]
    // 排序，按照左侧边界的大小来排序
    sort(line + 1, line + n + 1, cmp);
    // 扩充，将每一条线段都多加一个作为终点
    for (int i = 1; i <= n; i++)
    {
        line[i + n][0] = line[i][0];
        line[i + n][1] = line[i][1] + m;
        line[i + n][2] = line[i][2] + m;
    }

    // 初始化ST表的列0
    // 这里我们用范围内能取到的最大的小于等于范围的号作为第一跳的目标
    int arrive = 0, next = 0;
    int e = n << 1;
    for (int i = 1; i <= e; i++)
    {
        next = i + 1;
        arrive = line[i + 1][1];
        while (next <= n && arrive < line[i][2])
            arrive = line[next++][1];
        st[i][0] = next;
    }

    // 开始递推，我们需要拿到的是从当前点往前跳对应的次数能达到的范围
    // 这里是按列填写的，所以我们需要把p放在外层
    for (int i = 1; i <= p; i++)
        for (int j = 1; j <= e; j++)
            st[j][i] = st[st[j][i - 1]][i - 1];

}

int jump(int i, int power)
{
    int aim = line[i][1] + m, cur = i, next = 0;
    int ans = 1;
    for (int p = power; p >= 0; p--)
    {
        next = st[cur][p];
        if (line[next][2] <= aim)
        {
            ans += 1 << p;
            cur = next;
        }
    }
    return ans + 1;
}