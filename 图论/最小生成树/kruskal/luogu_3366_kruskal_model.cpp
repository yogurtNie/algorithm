//
// Created by 12472 on 25-6-12.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 5e3 + 10;
const int M = 2e5 + 10;
// 边的集合
struct edge
{
    int from, to, wei;
    edge(int f, int t, int w) : from(f), to(t), wei(w) {}
};
class MyCompare
{
public:
    bool operator()(const edge &a, const edge &b) const
    {
        return a.wei > b.wei;
    }
};
// 并查集
int parent[N];
int find(int x)
{
    return x == parent[x] ? x :parent[x] = find(parent[x]);
}
bool Union(int a, int b)
{
    int A = find(a), B = find(b);
    if (A == B) return false;
    parent[A] = B;
    return true;
}

int ans = 0, cnt = 0;
int n, m;
priority_queue<edge, vector<edge>, MyCompare> pq;
void kruskal()
{
    while (!pq.empty())
    {
        edge cur = pq.top();
        pq.pop();
        int a = cur.from, b = cur.to;
        if (Union(a, b))
        {
            ans += cur.wei;
            cnt++;
            if (cnt == n - 1) return;
        }
    }
}

int main()
{
    cin >> n >> m;
    int x, y, z;
    // 初始化并查集
    for (int i = 0; i <= n; i++) parent[i] = i;
    for (int i = 0; i < m; i++)
    {
        cin >> x >> y >> z;
        pq.push(edge(x, y, z));
    }
    kruskal();
    if (cnt == n - 1) cout << ans << endl;
    else cout << "orz" << endl;
    return 0;
}
