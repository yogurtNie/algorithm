//
// Created by 12472 on 25-6-12.
//
// 分层图，状态扩展，世界是一个巨大的动态规划
// 在x，y上新增一维，s，用于标识当前找到几把钥匙
#include <bits/stdc++.h>
using namespace std;
struct node
{
    int x, y, s;
    node(int a, int b, int c) : x(a), y(b), s(c) {}
};
class Solution {
public:
    int s = 6;
    int shortestPathAllKeys(vector<string>& grid) {
        int Move[5] = {-1, 0, 1, 0, -1};
        int n = grid.size();
        int m = grid[0].size();
        int vis[n][m][1 << 6];
        node start(0, 0, 0);
        int key_num = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == '@') start.x = i, start.y = j;
                if (grid[i][j] >= 'a' && grid[i][j] <= 'f') key_num++;
                for (int k = 0; k < 1 << 6; k++)
                {
                    vis[i][j][k] = 0;
                }
            }
        }
        queue<node> q;
        q.push(start);
        vis[start.x][start.y][start.s] = 1;
        int level = 1;
        while (!q.empty())
        {
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                node cur = q.front(); q.pop();

                int x = cur.x, y = cur.y, s = cur.s;
                for (int j = 0; j < 4; j++)
                {
                    // 一定要有一个良好的编程习惯，不要污染广搜时候的上层状态
                    int nx = x + Move[j], ny = y + Move[j + 1], ns = s;
                    // 处理越界情况
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                    if (vis[nx][ny][s]) continue;
                    // 开始分类讨论
                    // 如果是一堵墙，不管怎么样都不可能走
                    if (grid[nx][ny] == '#') continue;
                    // 如果是一把锁，有钥匙就可以走，没钥匙不许走
                    if (grid[nx][ny] >= 'A' && grid[nx][ny] <= 'F' && (s & (1 << grid[nx][ny] - 'A')) == 0) continue;
                    // 如果是一把钥匙
                    if (grid[nx][ny] >= 'a' && grid[nx][ny] <= 'f')
                    {
                        ns |= (1 << grid[nx][ny] - 'a');
                    }

                    // 判断是否到终点了
                    if (ns == (1 << key_num) - 1)
                    {
                        return level;
                    }

                    q.push({nx, ny, ns});
                    vis[nx][ny][ns] = 1;
                }
            }
            level++;
        }
        return -1;
    }
};

int main()
{
    vector<string> grid = {"@Aa"};
    Solution sol;
    cout << sol.shortestPathAllKeys(grid) << endl;
    return 0;
}