//
// Created by 12472 on 25-6-10.
//
// 根据给定的箭矢的数量倒推骑士道路
#include<bits/stdc++.h>
using namespace std;
const int N = 25;
int a[N], b[N];
int n;
vector<int> path;
int vis[N][N];
int Move[5] = {-1, 0, 1, 0, -1};
bool found = false;
void dfs(int x, int y)
{
    if (found) return;
    if (a[x] < 0 || b[y] < 0) return;
    if (x == n - 1 && y == n - 1)       // 已经到达终点后检查，是否满足a和b都降为0
    {
        bool flag = true;
        for (int i = 0; i < n; i++)
        {
            if (a[i] != 0 || b[i] != 0) {flag = false; break;}
        }
        if (flag)
        {
            found = true;
            for (int i = 0; i < path.size(); i++) cout << path[i] << " ";
        }
        return;
    }

    // 开始递归
    for (int i = 0; i < 4; i++)
    {
        int nx = x + Move[i], ny = y + Move[i + 1];
        if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
        if (!vis[nx][ny])
        {
            a[nx]--, b[ny]--;
            vis[nx][ny] = true;
            path.push_back(n * nx + ny);
            dfs(nx, ny);
            a[nx]++, b[ny]++;
            vis[nx][ny] = false;
            path.pop_back();
        }
    }
}



int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) cin >> b[i];
    for (int i = 0; i < n; i++) cin >> a[i];
    path.push_back(0);
    vis[0][0] = true;
    a[0] --, b[0] --;
    dfs(0, 0);
    return 0;
}