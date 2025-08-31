//
// Created by 12472 on 25-6-12.
//
// 有几次免单的机会，怎么用才能获得最少花费
// 到达一个城市 + 免单次数
//Alice 和 Bob 现在要乘飞机旅行，他们选择了一家相对便宜的航空公司。该航空公司一共在 n 个城市设有业务，设这些城市分别标记为 0 到 n−1，一共有 m 种航线，每种航线连接两个城市，并且航线有一定的价格。
//Alice 和 Bob 现在要从一个城市沿着航线到达另一个城市，途中可以进行转机。航空公司对他们这次旅行也推出优惠，他们可以免费在最多 k 种航线上搭乘飞机。那么 Alice 和 Bob 这次出行最少花费多少？
#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
const int M = 5e4 + 10;
struct node
{
    int id, k, cost;        // 分别含义是，某个城市的id，到达该城市花费的免费的次数，以及最终耗费金额
    node(int a, int b, int c) : id(a), k(b), cost(c) {}
};
class MyCompare
{
public:
    bool operator()(const node& a, const node& b) const
    {
        return a.cost > b.cost;
    }
};
int n, m, k, s, t;
vector<pair<int, int>> G[N];
int vis[N][12];
int dis[N][12];
int dijkstra()
{
    priority_queue<node, vector<node>, MyCompare> pq;
    pq.push({s, 0, 0});
    dis[s][0] = 0;
    while (!pq.empty())
    {
        node cur = pq.top(); pq.pop();
        int id = cur.id, kcnt = cur.k, cost = cur.cost;
        if (id == t) return cost;
        vis[cur.id][k] = 1;
        // 开始遍历可能性
        for (auto [nid, ncost] : G[id])
        {
            // 如果用免费次数
            if (kcnt < k && !vis[nid][kcnt + 1] && dis[nid][kcnt + 1] > cost)
            {
                dis[nid][kcnt + 1] = cost;
                pq.push({nid, kcnt + 1, cost});
            }
            // 如果不用免费次数
            if (dis[nid][kcnt] > cost + ncost)
            {
                dis[nid][kcnt] = cost + ncost;
                pq.push({nid, kcnt, cost + ncost});
            }
        }
    }
    return -1;

}
int main()
{
    cin >> n >> m >> k;
    cin >> s >> t;
    int a, b, c;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        // 记得是双向图
        G[a].emplace_back(b, c);
        G[b].emplace_back(a, c);
    }
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= k; j++)
        {
            dis[i][j] = 0x3f3f3f3f;
        }
    }
    cout << dijkstra() << endl;
    return 0;

}