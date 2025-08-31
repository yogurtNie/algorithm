//
// Created by 12472 on 25-6-12.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
const int M = 2e6 + 10;
int parent[N];
int find(int x)
{
    return parent[x] == x ? x : parent[x] = find(parent[x]);
}
bool Union(int x, int y)
{
    int A = find(x), B = find(y);
    if (A == B) return false;
    parent[A] = B;
    return true;
}
struct edge
{
    int u, v, t, w;
    edge(int a, int b, int c, int d) : u(a), v(b), t(c), w(d) {}
};
class MyCompare
{
public:
    bool operator()(const edge& a,const edge& b) const
    {
        return a.w > b.w;
    }
};
priority_queue<edge,vector<edge>,MyCompare> pq;
int cnt = 0, ans = 0;
int n, m;
void kruskal()
{
    while (!pq.empty())
    {
        edge e = pq.top(); pq.pop();
        if (e.u == 1 || e.v == 1)
        {
            if (e.t != 1) continue;
        }
        if (Union(e.v, e.u))
        {
            ans += e.w;
            cnt++;
            if (cnt == n - 1) return;
        }
    }
}

int main()
{
    cin >> n >> m;
    int u, v, t, w;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> t >> w;
        pq.push(edge(u, v, t, w));
    }
    for (int i = 0; i <= n; i++) parent[i] = i;
    kruskal();
    if (cnt == n - 1) cout << ans << "\n";
    else cout << -1 << "\n";
    return 0;
}