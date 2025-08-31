//
// Created by 12472 on 25-6-5.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
vector<int> G[N];
int n;
struct mes
{
    int cnt;        // 美观展台数量
    int val;     // 展台总价值

    bool operator < (const mes &m) const
    {
        if (cnt == m.cnt) return val < m.val;
        return cnt > m.cnt;
    }
}IsBt[N], IsNotBt[N];
int nbSum[N];

void calcu()
{
    for (int i = 1; i <= n; i++)
        for (int v : G[i]) nbSum[i]++;
}

void dp(int u, int f)
{
    IsBt[u].cnt = IsNotBt[u].val = 1;   // x美观时的初始美观展台数和x不美观时的初始价值，都应该为1
    IsBt[u].val = nbSum[u];
    IsNotBt[u].cnt = 0;
    for (int v : G[u])
    {
        if (v == f) continue;
        dp(v, u);
        // 先处理x是美观的
        IsBt[u].val += IsNotBt[v].val;
        IsBt[u].cnt += IsNotBt[v].cnt;

        // 再处理x是不美观的
        mes& smaller = (IsNotBt[v] < IsBt[v] ? IsNotBt[v] : IsBt[v]);
        IsNotBt[u].cnt += smaller.cnt;
        IsNotBt[u].val += smaller.val;

    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    calcu();
    if (n == 1) {cout << 1 << " " << 1 << "\n"; return 0;}
    if (n == 2) {cout << 2 << " " << 2 << "\n"; return 0;}
    dp(1, -1);
    mes& ans = (IsBt[1] < IsNotBt[1] ? IsBt[1] : IsNotBt[1]);
    cout << ans.cnt << " " << ans.val << "\n";
    return 0;
}