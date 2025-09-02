//
// Created by 12472 on 25-9-2.
//
// 更加简略的模板，省略小挂大的写法
// https://www.luogu.com.cn/problem/P3367
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int parent[N];
void init(int n)
{
    for (int i = 0; i < n; i++)
        parent[i] = i;
}
int find(int x)
{
    return x == parent[x] ? x : parent[x] = find(parent[x]);
}
bool IsSameSet(int a, int b)
{
    return find(a) == find(b);
}
void unionSet(int a, int b)
{
    int pa = find(a), pb = find(b);
    if (pa != pb)
    {
        parent[pa] = pb;
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    init(n);
    int opt, x, y;
    for (int i = 0; i < m; i++)
    {
        cin >> opt >> x >> y;
        if (opt == 1)
            unionSet(x, y);
        else if (opt == 2)
        {
            if (IsSameSet(x, y))
                cout << "Y" << endl;
            else
                cout << "N" << endl;
        }
    }
    return 0;
}