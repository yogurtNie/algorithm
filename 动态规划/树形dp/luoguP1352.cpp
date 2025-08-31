//
// Created by 12472 on 25-6-5.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 6e3 + 10;
int happy[N];
vector<int> G[N];
int no[N], yes[N];
int n;
bool IsNotRoot[N];

void dp(int u)
{
    no[u] = 0;
    yes[u] = happy[u];
    for (int v : G[u])
    {
        dp(v);
        no[u] += max(no[v], yes[v]);
        yes[u] += no[v];
    }
}


int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> happy[i];

    for (int i = 1; i < n; i++)
    {
        int u, v; cin >> u >> v;
        G[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int v : G[i]) IsNotRoot[v] = true;
    }
    int rroot = 0;
    for (int i = 1; i <= n; i++)
        if (!IsNotRoot[i]) rroot = i;
    dp(rroot);
    cout << max(no[rroot], yes[rroot]);
    return 0;
}