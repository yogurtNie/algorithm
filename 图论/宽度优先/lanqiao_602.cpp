//
// Created by 12472 on 25-6-10.
//
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
char mp[31][51];
char dir[4] = {'D', 'L', 'R', 'U'};
int Move[4][2] = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
int vis[31][51];
char pre[31][51];

void print_ans(int x, int y)
//利用回溯输出路径
{
    if (x == 0 && y == 0) return;
    if (pre[x][y] == 'D') print_ans(x - 1, y);
    if (pre[x][y] == 'L') print_ans(x, y + 1);
    if (pre[x][y] == 'R') print_ans(x, y - 1);
    if (pre[x][y] == 'U') print_ans(x + 1, y);
    cout << pre[x][y];
}
void bfs(int x, int y)
{
    queue<pii> q;
    q.emplace(x, y);        // 从i，j开始搜
    vis[x][y] = 1;
    while (!q.empty())
    {
        pii now = q.front(); q.pop();
        // 代码终结时需要干一些事
        if (now.first == 29 && now.second == 49)
        {
            print_ans(29, 49);
            return;
        }
        // 在宽搜的过程中需要干一些事
        for (int i = 0; i < 4; i++)
        {
            int nx = now.first + Move[i][0], ny = now.second + Move[i][1];
            // 不合法剪枝
            if (nx < 0 || nx > 29 || ny < 0 || ny > 49) continue;
            // 记得判断是否到达过
            if (vis[nx][ny] == 0 && mp[nx][ny] == '0')
            {
                q.emplace(nx, ny);
                vis[nx][ny] = 1;
                pre[nx][ny] = dir[i];
            }
        }
    }
}

int main()
{
    for (int i = 0; i < 30; i++) cin >> mp[i];
    bfs(0, 0);
    return 0;
}