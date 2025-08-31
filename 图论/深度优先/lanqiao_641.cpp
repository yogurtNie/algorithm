//
// Created by 12472 on 25-6-10.
//
#include<bits/stdc++.h>
using namespace std;
int Move[5] = {-1, 0, 1, 0, -1};
int ans = 0;
int vis[7][7];
void dfs(int x, int y)
{
    if (x == 0 || y == 0 || x == 6 || y == 6) {ans++; return;}
    for (int i = 0; i < 4; i++)
    {
        int nx = x + Move[i], ny = y + Move[i + 1];
        if (vis[nx][ny] == 0)
        {
            vis[nx][ny] = 1;
            vis[6 - nx][6 - ny] = 1;
            dfs(nx, ny);
            vis[nx][ny] = 0;
            vis[6 - nx][6 - ny] = 0;
        }
    }
}

int main()
{
    vis[3][3] = 1;
    dfs(3, 3);
    // 但是最后的答案并不是单纯的ans本身，因为左右搜的时候会重复一遍，所以要除2，而旋转对称的方案不算，所以还要再除2
    cout << ans / 4 << endl;
    return 0;
}
