//
// Created by 12472 on 25-6-10.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 110;
int p[N][N];                // 代表第i个考场的第k个座位的状态
bool a[N][N];                // 代表某个人和某个人是否认识
int n;
int ans = INT32_MAX;
void dfs(int x, int room)       // 第x个人分配到第room个房间
{
    // 回溯条件
    // 如果是room >= ans，则不会超时；如果是room > ans，超时了。
    if (room >= ans) return;     // 剪枝
    if (x > n)
    {
        if (ans > room) ans = room;
        return;
    }
    // 开始递归
    // 尝试从1号考场开始分配
    int t, j;
    for (j = 1; j <= room; j++)
    {
        // 如果在这个考场的所有人都不认识，则可以在最后给x加一张桌子
        t = 1;
        while (p[j][t] != 0 && a[x][p[j][t]] == 0) t++;
        if (a[x][p[j][t]] == 1) continue;
        if (p[j][t] == 0)
        {
            p[j][t] = x;
            dfs(x + 1, room);
            p[j][t] = 0;
        }
    }
    p[room + 1][1] = x;
    dfs(x + 1, room + 1);
    p[room + 1][1] = 0;
}
int main()
{
    cin >> n;
    int m; cin >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v; cin >> u >> v;
        a[u][v] = a[v][u] = 1;
    }
    dfs(1, 1);
    cout << ans << endl;
    return 0;
}