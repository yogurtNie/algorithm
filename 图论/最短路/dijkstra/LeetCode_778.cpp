//
// Created by 12472 on 25-6-12.
//
#include<bits/stdc++.h>
using namespace std;
struct node
{
    int x, y, hei;
};
class MyCompare
{
public:
    bool operator()(const node& a,const node& b) const
    {
        return a.hei > b.hei;
    }
};
class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int Move[5] = {-1, 0, 1, 0, -1};
        int n = grid.size();
        int m = grid[0].size();
        int vis[n + 1][m + 1], dis[n + 1][m + 1];
        // 初始化
        for (int i = 0; i < n; i ++)
        {
            for (int j = 0; j < m; j ++)
            {
                vis[i][j] = 0;
                dis[i][j] = 0x3f3f3f3f;
            }
        }
        priority_queue<node, vector<node>, MyCompare> pq;
        pq.push({0, 0, grid[0][0]});
        dis[0][0] = grid[0][0];
        while (!pq.empty())
        {
            node cur = pq.top(); pq.pop();
            int x = cur.x, y = cur.y, hei = cur.hei;
            if (x == n - 1 && y == m - 1)
            {
                return hei;
            }
            vis[x][y] = 1;
            for (int i = 0; i < 4; i++)
            {
                int nx = x + Move[i], ny = y + Move[i + 1];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (vis[nx][ny]) continue;
                int nhei = max(hei, grid[nx][ny]);
                if (nhei < dis[nx][ny])
                {
                    dis[nx][ny] = nhei;
                    pq.push({nx, ny, nhei});
                }
            }
        }
        return -1;
    }
};

int main()
{
    vector<vector<int>> grid = {{0, 2}, {1, 3}};
    Solution sol;
    cout << sol.swimInWater(grid) << endl;
    return 0;
}