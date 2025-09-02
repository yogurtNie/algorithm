//
// Created by 12472 on 25-9-2.
//
// 力扣200 岛屿数量
/*
* 给你一个由'1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
此外，你可以假设该网格的四条边均被水包围。
m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] 的值为 '0' 或 '1'
 */
// https://leetcode.cn/problems/number-of-islands/description/
#include <bits/stdc++.h>
using namespace std;
const int N = 9e4 + 10;
class Solution {
public:
    int parent[N];
    int set;
    void init(int n, int m, vector<vector<char>>& grid)
    {
        set = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == '1')
                {
                    set++;
                    parent[i * m + j] = i * m + j;
                }
            }
    }
    int find(int x)
    {
        return x == parent[x] ? x : parent[x] = find(parent[x]);
    }
    bool IsSameSet(int a, int b)
    {
        return find(a) == find(b);
    }
    void Union(int a, int b)
    {
        int pa = find(a), pb = find(b);
        if (pa != pb)
        {
            parent[pa] = pb;
            set--;
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        init(n, m, grid);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == '1')
                {
                    // 检查上方
                    if (j > 0 && grid[i][j - 1] == '1')
                    {
                        if (!IsSameSet(i * m + j, i * m + j - 1))
                            Union(i * m + j, i * m + j - 1);
                    }
                    // 检查左方
                    if (i > 0 && grid[i - 1][j] == '1')
                    {
                        if (!IsSameSet(i * m + j, (i - 1)* m + j))
                            Union(i * m + j, (i - 1)* m + j);
                    }
                }
            }
        }
        return set;
    }
};

int main()
{
    vector<vector<char>> grid = {{'1','1','0','0','0'}, {'1','1','0','0','0'}, {'0','0','1','0','0'}, {'0','0','0','1','1'}};
    Solution sol;
    cout << sol.numIslands(grid);
    return 0;
}
