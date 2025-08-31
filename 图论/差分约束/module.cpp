//
// Created by 12472 on 25-5-8.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 5e3 + 10, INF = 0x3f3f3f3f;
struct node
{
    int to, wei;
    node(int a, int b)
    {
        to = a; wei = b;
    }
};
vector<node> G[N];
// 记住，spfa需要的数组和他们分别的用处
int dist[N];        // 距离数组，用于松弛和最终答案的获得
int vis[N];         // 标记数组，用于标记是否在队列内部
int cnt[N];         // 计数数组，用于判断是否有负环（当某个点松弛超过n-1次时，有负环）
int n;              // 总点数，用于判断是否有负环
bool spfa(int i)
{
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    queue<int> q;
    dist[i] = 0;
    cnt[i] = 1;
    q.push(i);
    vis[i] = 1;
    while (!q.empty())
    {
        int now = q.front(); q.pop(); vis[now] = 0;
        for (auto&[to, wei] : G[now])
        {
            if (dist[to] > dist[now] + wei)
            {
                dist[to] = dist[now] + wei;
                if (!vis[to])
                {
                    if (++cnt[to] > n) return false;
                    q.push(to);
                    vis[to] = 1;
                }
            }
        }
    }
    return true;

}

int main()
{
    int m; cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v, w; cin >> u >> v >> w;
        G[v].push_back(node(u, w));
    }
    // 同时记得，给spfa加入超级源点
    for (int i = 1; i <= n; i++)
    {
        G[0].push_back(node(i, 0));
    }
    if (spfa(0))
    {
        for (int i = 1; i <= n; i++) cout << dist[i] << ' ';
    }
    else cout << "NO" << endl;
    return 0;
}
