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
int root;
vector<int> edge[N];
vector<int> sons[N];
int vis[N];

void trans(int root)
{
    vis[root] = 1;
    queue<int> q;
    q.push(root);
    while (!q.empty())
    {
        int top = q.front(); q.pop();
        for (auto& v : edge[top])
        {
            if (!vis[v])
            {
                sons[top].push_back(v);
                q.push(v);
                vis[v] = 1;
            }
        }
    }
}


void dp(int u)
{
    if (sons[u].empty())
    {
        d[u][0] = 1;
        d[u][1] = 0;
        d[u][2] = N;       // 标记为不合法
        return;
    }

    // d(u, 0)
    d[u][0] = 1;
    for (auto &v : sons[u])
    {
        if (d[v][0] == -1 || d[v][1] == -1) dp(v);
        d[u][0] += min(d[v][0], d[v][1]);
    }


    // d(u, 1)
    d[u][1] = 0;
    for (auto &v : sons[u])
    {
        if (d[v][2] == -1) dp(v);
        d[u][1] += d[v][2];
    }

    // d(u, 2)
    d[u][2] = INF;
    for (auto &v : sons[u])
    {
        d[u][2] = min(d[u][2], d[u][1] - d[v][2] + d[v][0]);
    }
}
int main()
{
    int end = 0;
    while (end != -1)
    {
        int n; cin >> n;
        for (int i = 0; i <= n; i++) vis[i] = 0;
        for (int i = 0; i <= n; i++)
        {
            sons[i].clear();
            edge[i].clear();
        }
        for (int i = 0; i < n - 1; i++)
        {
            int a, b; cin >> a >> b;
            if (i == 0) root = a;
            edge[a].push_back(b);
            edge[b].push_back(a);
        }

        // 初始化为-1
        for (int i = 0; i <= n; i++) d[i][0] = d[i][1] = d[i][2] = -1;

        // 从root开始递推
        trans(root);


        dp(root);

        // for (int i = 1; i <= 6; i++)
        // {
        //     for (int j = 0; j <= 2; j++)
        //     {
        //         cout << d[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        d[root][1] = INF;
        cout << min(d[root][0], min(d[root][1], d[root][2])) << endl;

        cin >> end;
    }
    return 0;
}