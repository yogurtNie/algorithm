//
// Created by 12472 on 25-5-8.
//
// 农场a比农场b至少多种植了c个单位的作物 ： a - b >= c  -->  b - a <= -c
// 农场a比农场b至多多种植了c个单位的作物 ： a - b <= c  -->  a - b <= c
// 农场a比农场b种植的作物一样多 ： a - b = 0 -->  a - b <= 0 && b - a <= 0
#include<bits/stdc++.h>
using namespace std;
const int N = 5e3 + 10;
struct node
{
    int to, wei;
    node(int a, int b) : to(a), wei(b) {}
};
vector<node> G[N];
int n;
int dist[N], vis[N], cnt[N];
bool spfa(int i)
{
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    queue<int> q;
    dist[i] = 0;
    vis[i] = 1;
    q.push(i);
    cnt[i] = 1;
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
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int choice; cin >> choice;
        if (choice == 1)
        {
            int a, b, c; cin >> a >> b >> c;
            G[a].push_back(node(b, -c));
        }
        else if (choice == 2)
        {
            int a, b, c; cin >> a >> b >> c;
            G[b].push_back(node(a, c));
        }
        else if (choice == 3)
        {
            int a, b; cin >> a >> b;
            G[b].push_back(node(a, 0));
            G[a].push_back(node(b, 0));
        }
    }
    for (int i = 1; i <= n; i++) G[0].push_back(node(i, 0));
    if (spfa(0)) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}