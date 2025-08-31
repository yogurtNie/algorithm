//
// Created by 12472 on 25-6-27.
//
/*
 * 老板需要你帮忙浇花。给出 N 滴水的坐标，y 表示水滴的高度，x 表示它下落到 x 轴的位置。
 * 每滴水以每秒 1 个单位长度的速度下落。你需要把花盆放在 x 轴上的某个位置，使得从被花盆接着的第 1 滴水开始，到被花盆接着的最后 1 滴水结束，之间的时间差至少为 D。
 * 我们认为，只要水滴落到 x 轴上，与花盆的边沿对齐，就认为被接住。给出 N 滴水的坐标和 D 的大小，请算出最小的花盆的宽度 W
 * 分析：通过滑动窗口，如果当前下标中的差值不合格，则继续扩充，否则更新答案，并缩小左边界
 * 测试连接：https://www.luogu.com.cn/problem/P2698
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<int> MaxD, MinD;
int n, d;
struct node
{
    int x, y;
    bool operator < (const node &rhs) const
    {
        return x < rhs.x;
    }
}arr[N];
int maxl, maxr, minl, minr;
bool ok()
{
    int Wmax = maxl < maxr ? arr[MaxD[maxl]].y : 0;
    int Wmin = minl < minr ? arr[MinD[minl]].y : 0;
    return Wmax - Wmin >= d;
}
void push(int r)
{
    while (maxl < maxr && arr[MaxD[maxr - 1]].y <= arr[r].y)
    {
        maxr--;
    }
    MaxD[maxr++] = r;
    while (minl < minr && arr[MinD[minr - 1]].y >= arr[r].y)
    {
        minr--;
    }
    MinD[minr++] = r;
}
void pop(int l)
{
    if (maxl < maxr && MaxD[maxl] == l)
    {
        maxl++;
    }
    if (minl < minr && MinD[minl] == l)
    {
        minl++;
    }
}
int main()
{
    cin >> n >> d;
    // 维护两个单调队列，一个用来取最小值，一个用来取最大值
    MaxD.resize(n, 0), MinD.resize(n, 0);
    maxl = maxr = minl = minr = 0;
    int ans = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i].x >> arr[i].y;
    }
    sort(arr, arr + n);
    for (int l = 0, r = 0; l < n; l++)
    {
        // 先考虑右边界能不能扩充
        while (!ok() && r < n)
        {
            // 能的话就扩
            push(r++);
        }
        // 扩到扩不了之后，更新答案
        // r-1是当前最右边的，l是当前最左边的
        if (ok()) ans = min(ans, arr[r - 1].x - arr[l].x);
        // 然后更新左边界
        pop(l);
    }
    if (ans == INT_MAX) cout << -1 << endl;
    else cout <<  ans << endl;
    return 0;
}