//
// Created by 12472 on 25-6-12.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 210;
const int M = 21000;
const int INF = 0x3f3f3f3f;
int dis[N][N], G[N][N];
int times[N];
int n, m;
struct edge
{
    int u, v, w, time;
    edge(int a, int b, int c, int d = -1) : u(a), v(b), w(c), time(d) {}
};
bool cmp(const edge& a,const edge& b)
{
    return a.time < b.time;
}
struct question
{
    int from, to, time;
    question(int a, int b, int c) : from(a), to(b), time(c) {}
};
vector<edge> e;
vector<question> Q;



int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> times[i];
    int u, v, w;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            G[i][j] = INF;
        }
    }
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        G[u][v] = G[v][u] = w;
    }
    int q; cin >> q;
    int from, to, day;
    for (int i = 0; i < q; i++)
    {
        cin >> from >> to >> day;
        Q.push_back(question(from, to, day));
    }


    // 开始查询
    int i;
    for (i = 0; i < q; i++)
    {
        for (int j = 0; times[j] <= Q[i].time; j++)
        {
            for (int l = 0; times[l] <= Q[i].time; l++)
            {
                for (int p = 0; times[p] <= Q[i].time; p++)
                {
                    if ()
                }
            }
        }
        if (dis[Q[i].from][Q[i].to] != INF) cout << dis[Q[i].from][Q[i].to] << endl;
        else cout << -1 << endl;
    }
    return 0;
}