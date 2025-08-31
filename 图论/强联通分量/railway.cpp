//
// Created by 12472 on 25-5-8.
//
// 思路：找到所有强联通分量，强联通分量中的遍历城市对个数为: n * (n - 1) / 2
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
vector<int> G1[N], G2[N];
int vis[N];
int dcnt, scnt, n;
int dfn[N], scc[N];
map<int, int> mp;
void dfs1(int x)
{
    vis[x] = 1;
    for (auto i : G1[x])
        if (!vis[i]) dfs1(i);
    dfn[++dcnt] = x;
}

void dfs2(int x)
{
    scc[x] = scnt;
    if (mp.count(scnt) == 0) mp[scnt] = 1;
    else mp[scnt] += 1;
    for (auto i : G2[x])
        if (!scc[i]) dfs2(i);
}

void kosarajo()
{
    // 初始化两个指针
    dcnt = scnt = 0;
    memset(vis, 0, sizeof(vis));
    memset(dfn, 0, sizeof(dfn));
    memset(scc, 0, sizeof(scc));
    for (int i = 1; i <= n; i++)
        if (!vis[i]) dfs1(i);
    // 非常易错，一定要记得是逆后序序列
    for (int i = n; i >= 1; i--)
    {
        if (!scc[dfn[i]])
        {
            scnt++;
            dfs2(dfn[i]);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int m; cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b; cin >> a >> b;
        G1[a].push_back(b);
        G2[b].push_back(a);
    }
    kosarajo();
    long long ans = 0;
    for (auto& [sc, cnt] : mp)
    {
        ans += cnt * (cnt - 1) / 2;
    }
    cout << ans << endl;
    //cout << scnt << endl;
    return 0;
}