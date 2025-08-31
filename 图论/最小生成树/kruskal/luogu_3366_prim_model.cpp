//
// Created by 12472 on 25-6-12.
//
// prim算法模板
#include<bits/stdc++.h>
using namespace std;
const int N = 5e3 + 10;         // 节点数量
const int M = 2e5 + 10;         // 边数量
bool vis[N];                    // 是否选中过了
vector<pair<int, int>> G[N];
struct node
{
    int id, sum;                // 点，到这个点的权值
    node(int a, int b) : id(a), sum(b) {}
};
class MyCompare
{
public:
    bool operator()(const node& a, const node& b) const
    {
        return a.sum > b.sum;
    }
};
int n, m;
int ans = 0, cnt = 0;
priority_queue<node, vector<node>, MyCompare> pq;
void prim()
{
    pq.push(node(1, 0));
    while (!pq.empty())
    {
        node cur = pq.top(); pq.pop();
        if (vis[cur.id]) continue;
        ans += cur.sum;
        vis[cur.id] = 1;
        cnt++;
        if (cnt == n) return;
        for (auto [v, w] : G[cur.id])
        {
            if (vis[v]) continue;
            pq.push(node(v, w));
        }
    }
}



int main()
{
    cin >> n >> m;
    int x, y, z;
    for (int i = 0; i < m; i++)
    {
        cin >> x >> y >> z;
        G[x].emplace_back(y, z);
        G[y].emplace_back(x, z);
    }
    prim();
    if (cnt == n) cout << ans << endl;
    else cout << "orz" << endl;
    return 0;
}
