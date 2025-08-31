//
// Created by 12472 on 25-6-10.
//
// 剪格子，同样练习深搜剪枝，其实也可以试试动规（但是有一个小要求，就是必须要联通）
// 这种情况，深搜具有天然优势
#include<bits/stdc++.h>
using namespace std;
int ans = INT32_MAX;
int sum = 0, cnt = 0;
int tmp = 0;
int G[11][11];
int vis[11][11];
int Move[5] = {-1, 0, 1, 0, -1};
int m, n;
void dfs(int x, int y)
{
    if (cnt > sum / 2) return;
    if (cnt == sum / 2)
    {
        ans = min(ans, tmp);
        return;
    }

    // for (int i = 0; i < 4; i++)
    // {
    //     int nx = x + Move[i], ny = y + Move[i + 1];
    //     if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
    //     if (!vis[nx][ny])
    //     {
    //         vis[nx][ny] = 1;
    //         cnt += G[nx][ny];
    //         tmp++;
    //         dfs(nx, ny);
    //         cnt -= G[nx][ny];
    //         vis[nx][ny] = 0;
    //         tmp--;
    //     }
    // }
    vis[x][y] = 1;
    for (int i = 0; i < 4; i++)
    {
        int nx = x + Move[i], ny = y + Move[i + 1];
        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
        if (!vis[nx][ny])
        {
            tmp ++;
            cnt += G[x][y];
            dfs(nx, ny);
            tmp --;
            cnt -= G[x][y];
        }
    }
    vis[x][y] = 0;
}

int main()
{
    cin >> m >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> G[i][j];
            sum += G[i][j];
        }
    }
    if (sum % 2 != 0 )
    {
        cout << 0 << endl;
        return 0;
    }
    dfs(0, 0);
    cout << ans << endl;
    // int last = INT32_MAX;
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //     {
    //         memset(vis, 0, sizeof(vis));
    //         ans = INT32_MAX;
    //         vis[i][j] = 1;
    //         cnt += G[i][j];
    //         tmp = 1;
    //         dfs(i, j);
    //         last = min(last, ans);
    //     }
    // }
    // cout << last << endl;
    return 0;
}