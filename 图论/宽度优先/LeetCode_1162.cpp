//
// Created by 12472 on 25-6-10.
//
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    typedef pair<int, int> pii;
    int move[5] = {-1, 0, 1, 0, -1};
    int maxDistance(vector<vector<int>>& grid) {
        int n = grid.size();
        queue<pii> q;
        vector<vector<int>> vis(n + 1, vector<int>(n + 1, 0));
        int seas = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    q.emplace(i, j);
                    vis[i][j] = 1;
                }
                else seas++;
            }
        }
        if (seas == n * n || seas == 0) return -1;
        // 开始广搜
        int level = 0;
        while (!q.empty()) {
            int size = q.size();
            level++;
            for (int i = 0; i < size; i ++) {
                pii now = q.front(); q.pop();
                for (int j = 0; j < 4; j++) {
                    int nx = now.first + move[j], ny = now.second + move[j + 1];
                    // 记得检查有无出界
                    if (nx < 0 || ny >= n || nx >= n || ny < 0) continue;
                    if (vis[nx][ny] == 0 && grid[nx][ny] == 0) {
                        q.emplace(nx, ny);
                        vis[nx][ny] = 1;
                    }
                }
            }
        }
        return level - 1;
    }
};

int main()
{
    vector<vector<int>> grid = {{1, 0, 1}, {0, 0, 0}, {1, 0, 1}};
    Solution sol;
    cout << sol.maxDistance(grid) << endl;
    return 0;
}