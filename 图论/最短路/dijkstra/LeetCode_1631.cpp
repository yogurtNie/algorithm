//
// Created by 12472 on 25-6-12.
//
// 要求从最上到右下的一个最小高度差
#include <bits/stdc++.h>
using namespace std;
const int N = 110;
struct node
{
    int x, y, hei;
    node(int a, int b, int c) : x(a), y(b), hei(c) {}
};
class MyCompare
{
public:
    bool operator()(const node& a, const node& b)
    {
        return a.hei > b.hei;
    }
};
int vis[N][N];
int dis[N][N];
int ans = INT32_MAX;
class Solution {
public:
    int Move[5] = {-1, 0, 1, 0, -1};
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();
        // 初始化一个dist数组，用来填充路径答案（在这一题里是指差值的最小值）
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                dis[i][j] = 0x3f3f3f3f;             // 所以初始化成最大
            }
        }
        dis[0][0] = 0;
        priority_queue<node, vector<node>, MyCompare> pq;
        pq.push(node(0, 0, 0));             // 将初始状态填入
        while (!pq.empty())                          // 为空时结束
        {
            node cur = pq.top(); pq.pop();
            int x = cur.x, y = cur.y, hei = cur.hei;
            if (vis[x][y]) continue;
            if (x == n - 1 && y == m - 1)           // 如果到了终点，决策终止，直接返回
            {
                return hei;
            }
            vis[x][y] = 1;                          // 标记为已经是最小值，不可更改
            for (int i = 0; i < 4; i++)
            {
                int nx = x + Move[i], ny = y + Move[i + 1];         // 上下左右都试试
                if (nx < 0 || nx >= heights.size() || ny < 0 || ny >= heights[0].size()) continue;      // 越界就省略
                if (vis[nx][ny]) continue;                          // 决策过也省略
                int compare = max(hei, abs(heights[nx][ny] - heights[x][y]));                   // 看看目前的路是否比之前还大
                if (compare < dis[nx][ny])      // 如果决策更优（在之前最优的基础上），则填充下一个答案
                {
                    dis[nx][ny] = compare;
                    pq.push(node(nx, ny, compare));
                }

            }
        }
    }
};

int main()
{
    vector<vector<int>> heights = {{1,2,3},{3,8,4},{5,3,5}};
    Solution sol;
    cout << sol.minimumEffortPath(heights) << endl;
    return 0;
}