//
// Created by 12472 on 25-6-10.
//
#include<bits/stdc++.h>
using namespace std;
int a[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int ans = 0;
void dfs1(int s, int t)
{
    if (s == 13)
    {
        if (a[12] * a[11] == a[10]) ans++;
        return;
    }
    if (s == 4 && a[1] + a[2] != a[3]) return;
    if (s == 7 && a[4] - a[5] != a[6]) return;
    if (s == 10 && a[7] * a[8] != a[9]) return;

    for (int i = s; i <= t; i++ )
    {
        swap(a[i], a[s]);
        dfs1(s + 1, t);
        swap(a[i], a[s]);
    }
}
bool vis[20];
int b[20];
void dfs2(int s, int t)
{
    if (s == 13)
    {
        if (b[12] * b[11] == b[10]) ans++;
        return;
    }

    if (s == 4 && b[1] + b[2] != b[3]) return;
    if (s == 7 && b[4] - b[5] != b[6]) return;
    if (s == 10 && b[7] * b[8] != b[9]) return;

    // for (int i = s; i <= t; i++)
    for (int i = 1; i <= t; i++)
    {
        if (!vis[i])
        {
            vis[i] = true;
            b[s] = a[i];
            dfs2(s + 1, t);
            vis[i] = false;
        }
    }
}
int main()
{
    dfs2(1, 13);
    cout << ans << endl;
}
