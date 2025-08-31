//
// Created by 12472 on 25-5-17.
//
// n个人形成树形结构，除了老板之外每个员工都有唯一的直属上司。要求选尽可能多的人，在人数最多的前提下方案是否唯一？
// 如果是单纯的树的独立集问题，则直接用一个坐标来标识，即d(i)代表以i为根节点的最多人数
// 但是现在需要确定方案的唯一性，所以需要多一维坐标来确定
// d(i, 0)代表不选i时的最大人数，f(i, 0)代表不选i时的方案唯一性（1是唯一，0不唯一）
// d(i, 1)代表选i时的最大人数，f(i, 1)代表选i时的方案唯一性
// 状态转移：d(u, 1) = sum{ d(v, 0) | v是u的子节点 } f(u, 1) = f(v_1, 0) ^ f(v_2, 0) ^ ... 代表的含义是，当不选所有子节点的方案都唯一时，这个方案才是唯一的
// d(u, 0) = sum{ max(d(v, 0), d(v, 1)) } 即子节点可选可不选 有任何一个子节点的d(v, 0)和d(v, 1)一样，不唯一
// f(u, 0)唯一，只有当选择的所有dv都唯一时才成立
#include<bits/stdc++.h>
using namespace std;
const int N = 210;
map<string, int> mp;
int d[N][2];
int f[N][2];
vector<int> sons[N];

void dp(int u)
{
    if (sons[u].empty())
    {
        d[u][0] = 0;
        d[u][1] = 1;
        f[u][0] = f[u][1] = 1;
        return;
    }

    // d(u, 1)
    int cnt = 1; int flag = 1;
    for (auto& v : sons[u])
    {
        if (d[v][0] == -1) dp(v);
        cnt += d[v][0];
        flag &= f[v][0];
    }

    d[u][1] = cnt;
    f[u][1] = flag;

    // d(u, 0)
    int cnt2 = 0; int flag2 = 1;
    for (auto& v : sons[u])
    {
        if (d[v][1] == -1) dp(v);
        int delta = max(d[v][0], d[v][1]);
        flag2 &= ((d[v][0] == d[v][1]) ? 0 : (delta == d[v][0] ? f[v][0] : f[v][1]));
        cnt2 += delta;
    }

    d[u][0] = cnt2;
    f[u][0] = flag2;

}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    while (cin >> n)
    {
        if (!n) break;
        mp.clear();
        for (int i = 0; i <= n; i++) sons[i].clear();
        string boss; cin >> boss;
        mp[boss] = 0;
        int cnt = 1;
        for (int i = 0; i < n - 1; i++)
        {
            string e, b; cin >> e >> b;
            if (mp.count(b) == 0) mp[b] = cnt++;
            if (mp.count(e) == 0) mp[e] = cnt++;
            int s = mp[e], p = mp[b];
            sons[p].push_back(s);
        }
        for (int i = 0; i <= n; i++) d[i][0] = d[i][1] = -1;

        dp(0);

        int ans = max(d[0][0], d[0][1]);
        cout << ans << " ";
        if (d[0][0] == d[0][1]) cout << "No\n";
        else if ((ans == d[0][0] && f[0][0] == 0) || (ans == d[0][1] && f[0][1] == 0)) cout << "No\n";
        else cout << "Yes\n";
    }
    return 0;
}