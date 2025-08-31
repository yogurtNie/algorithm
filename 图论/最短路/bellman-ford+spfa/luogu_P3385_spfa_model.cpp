//
// Created by 12472 on 25-6-12.
//
// spfa经典模板，判断负环
#include<bits/stdc++.h>
using namespace std;
const int N = 2e3 + 10;
const int M = 3e3 + 10;
vector<pair<int, int>> G[N];
int n, m;
int dist[N];
bool vis[N];
int cnt[N];                 // 非经典结构，用于记录每个点松弛多少次
bool spfa(int s)
{
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    dist[s] = 0;
    cnt[s] = 1;
    while (!q.empty())
    {
        int cur = q.front();
        q.pop(); vis[cur] = 0;
        for (auto [v, w] : G[cur])
        {
            if (dist[v] > dist[cur] + w)        // 先判断是否能接着松弛
            {
                dist[v] = dist[cur] + w;
                if (!vis[v])                    // 然后判断是否在队列里
                {
                    cnt[v]++;
                    if (cnt[v] >= n) return true;
                    q.push(v);
                    vis[v] = 1;
                }
            }
        }
    }
    return false;
}


int main()
{
    int T; cin >> T;
    while (T--)
    {
        cin >> n >> m;
        int u, v, w;
        for (int i = 0; i <= n; i++) { G[i].clear(); dist[i] = 0x3f3f3f3f; vis[i] = cnt[i] = 0; }
        for (int i = 0; i < m; i++)
        {
            cin >> u >> v >> w;
            if (w >= 0)
            {
                G[u].emplace_back(v, w);
                G[v].emplace_back(u, w);
            }
            else G[u].emplace_back(v, w);
        }
        if (spfa(1)) cout << "YES\n";
        else cout << "NO\n";
    }
}