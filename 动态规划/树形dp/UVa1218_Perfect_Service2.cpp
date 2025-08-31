//
// Created by 12472 on 25-5-17.
//
// 有n台机器形成树状结构。要求其中一些机器上安装服务器，使得每台不是服务器的计算机恰好和一台服务器计算机
// 相邻。求服务器的最少数量
// 1. 状态定义：一个节点有两种状态，是服务器 / 不是服务器；综合父亲节点的情况可以有以下三种状态分类
// d(u, 0) u本身是服务器，则u的子节点可以是服务器可以不是服务器，u的父节点同理
// d(u, 1) u本身不是服务器，u的父亲是服务器，则u的子节点一定都不是服务器
// d(u, 2) u本身不是服务器，u的父亲也不是服务器，那么u的子节点中一定恰好有一台服务器
// 2. 状态转移：
// d(u, 0) = sum{ max(d(v, 0), d(v, 1)) }
// d(u, 1) = sum{ d(v, 2) }
// d(u, 2) = max( d(u, 1) - d(v, 2) + d(v, 0) )
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10, INF = 0x3f3f3f3f;
int d[N][3];
vector<int> edge[N];


void dp(int u, int f)
{
    d[u][0] = 1;
    d[u][1] = 0;
    d[u][2] = N;
    for (auto& v : edge[u])
    {
        if (v != f)
        {
            dp(v, u);
            d[u][0] += min(d[v][0], d[v][1]);
            d[u][1] += d[v][2];
        }
    }
    for (auto& v : edge[u])
    {
        if (v != f)
        {
            d[u][2] = min(d[u][2], d[u][1] - d[v][2] + d[v][0]);
        }
    }
}
int main()
{
    int end = 0;
    while (end != -1)
    {
        int n; cin >> n;
        for (int i = 0; i <= n; i++)
        {
            edge[i].clear();
        }
        for (int i = 0; i < n - 1; i++)
        {
            int a, b; cin >> a >> b;
            edge[a].push_back(b);
            edge[b].push_back(a);
        }


        dp(1, -1);

        cout << min(d[1][0], d[1][2]) << endl;

        cin >> end;
    }
    return 0;
}