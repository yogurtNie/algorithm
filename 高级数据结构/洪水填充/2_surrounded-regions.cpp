//
// Created by 12472 on 25-9-8.
//
/*
 * 给你一个 m x n 的矩阵 board ，由若干字符 'X' 和 'O' 组成，捕获 所有 被围绕的区域：
连接：一个单元格与水平或垂直方向上相邻的单元格连接。
区域：连接所有 'O' 的单元格来形成一个区域。
围绕：如果您可以用 'X' 单元格 连接这个区域，并且区域中没有任何单元格位于 board 边缘，则该区域被 'X' 单元格围绕。
通过 原地 将输入矩阵中的所有 'O' 替换为 'X' 来 捕获被围绕的区域。你不需要返回任何值。
m == board.length
n == board[i].length
1 <= m, n <= 200
board[i][j] 为 'X' 或 'O'
*/
// https://leetcode.cn/problems/surrounded-regions/description/
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int n = board.size(), m = board[0].size();
        // 总共进行3次dfs
        // 第一次dfs起点在矩阵四周，由四周向中间感染，将不符合要求的'O'换成'F'
        for (int i = 0; i < n; i++)
        {
            if (board[i][0] == 'O')
                dfs(board, i, 0, 'O', 'F');
            if (board[i][n - 1] == 'O')
                dfs(board, i, n - 1, 'O', 'F');
        }
        for (int j = 1; j < m - 1; j++)
        {
            if (board[0][j] == 'O')
                dfs(board, 0, j, 'O', 'F');
            if (board[m - 1][j] == 'O')
                dfs(board, m - 1, j, 'O', 'F');
        }
        // 第二次dfs起点在矩阵内部，遍历矩阵，将剩余'O'标记为'X'
        for (int i = 1; i < n - 1; i++)
        {
            for (int j = 1; j < m - 1; j++)
            {
                if (board[i][j] == 'O')
                    dfs(board, i, j, 'O', 'X');
            }
        }
        // 第三次dfs就是回复'F'标记为'O'
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (board[i][j] == 'F')
                    dfs(board, i, j, 'F', '0');
            }
        }
    }
    void dfs(vector<vector<char>>& board, int x, int y, char src, int des)
    {
        if (x < 0 || x == board.size() || y < 0 || y == board[0].size() || board[x][y] != src)
            return;
        board[x][y] = des;
        dfs(board, x - 1, y, src, des);
        dfs(board, x + 1, y, src, des);
        dfs(board, x, y - 1, src, des);
        dfs(board, x, y + 1, src, des);
    }
};