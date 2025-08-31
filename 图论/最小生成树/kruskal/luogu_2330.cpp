//
// Created by 12472 on 25-6-12.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 310;
const int M = 1e4 + 10;
int parent[N];
struct edge
{
    int from, to, wei;
    edge(int from, int to, int wei) : from(from), to(to), wei(wei) {}
};
class MyCompare
{
public:
    bool operator()(const edge& a, const edge& b) const
    {
        return a.wei > b.wei;
    }
};
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
priority_queue<edge, vector<edge>, MyCompare> pq;
int cnt = 0, ans = 0;
int n, m;
void kruskal()
{
    while (!pq.empty())
    {
        edge cur = pq.top(); pq.pop();
        int a = cur.from, b = cur.to;
        if (Union(a, b))
        {
            cnt++;
            ans = max(ans, cur.wei);
        }
        if (cnt == n - 1) return;
    }
}
int main()
{
    cin >> n >> m;
    int u, v, c;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> c;
        pq.push(edge(u, v, c));
    }
    for (int i = 0; i <= n; i ++) parent[i] = i;
    kruskal();
    cout << n - 1 << " " << ans;
    return 0;
}