//
// Created by csp on 2025/5/9.
//
// 建图 -> 缩点 -> 最长路
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
const int M = 1e5 + 10;

typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
map<int, ll> mp;
int dcnt, scnt;
ll value[N];
vector<int> G1[N], G2[N];

int vis[N], scc[N];
ll dfn[N];
int n, m;       // 点的数量
void dfs1(int x) {
    vis[x] = 1;
    for (auto y : G1[x])
        if(!vis[y]) dfs1(y);
    dfn[++dcnt] = x;
}
ll sumValue = 0;
void dfs2(int x) {
    scc[x] = scnt;
    sumValue += value[x];
    for (auto y :G2[x])
        if (!scc[y]) dfs2(y);
}

void kjo() {
    dcnt = scnt = 0;
    memset(vis, 0, sizeof vis);
    for (int i = 1; i <= n; i++) {
        if(!vis[i]) dfs1(i);
    }
    for (int i = n; i>= 1; i--) {
        if (!scc[dfn[i]]) {
            sumValue = 0;
            ++scnt;
            dfs2(dfn[i]);
            mp[scnt] = sumValue;
        }
    }
}

int main() {
    cin >> n >> m;
    //赋值点权
    for (int i = 1; i <= n; i++) {
        cin >> value[i];
    }
    //建立图
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        G1[u].push_back(v);
        G2[v].push_back(u);
    }
    //找强连通分量
    kjo();
    set<int> newG[scnt + 10];
    memset(vis, 0, sizeof vis);
    for (int i = 1; i <= n; i++) {
        for (int v : G1[i]) {
            if (scc[i] != scc[v]) newG[scc[i]].insert(scc[v]);
        }
    }
//    for (int i = 1; i <= scnt; i++) cout << value[i] << " ";
//    cout << endl;
//    for (int i = 1; i <= scnt; i++) {
//        cout << i << ": ";
//        for (auto y : newG[i]) cout << y << " ";
//        cout << endl;
//    }

    // 开始在新的图上跑spfa
    queue<int> q;
    memset(vis, 0, sizeof vis);     // 用于判断是否在队列李
    //memset(dfn,0x3f, sizeof dfn);   // 用于当距离数组
    memset(scc, 0, sizeof scc);     // 用于判断是否存在负环，其实不是很必要
    for (int i = 0; i <= n; i++) dfn[i] = -INF;
    //加入超级源点
    for (int i = 1; i <= scnt; i++) newG[0].insert(i);
    value[0] = 0;

    q.push(0);
    vis[0] = 1;
    dfn[0] = 0;
    ll ans = 0;
    while (!q.empty()) {
        int now = q.front(); q.pop(); vis[now] = 0;
        for (auto y : newG[now]) {
            if (dfn[y] < dfn[now] + mp[y]) {
                dfn[y] = dfn[now] + mp[y];
                ans = max(ans, dfn[y]);
                if (!vis[y]) {
                    q.push(y);
                    vis[y] = 0;
                }
            }
        }
    }
    cout << ans << endl;
    return 0;

}