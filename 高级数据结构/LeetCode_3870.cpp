//
// Created by 12472 on 25-6-3.
//
#include<bits/stdc++.h>
#define ls (i << 1)
#define rs (i << 1 | 1)
#define mid (l + r >> 1)
using namespace std;
const int N = 1e5 + 10;
int tree[N << 2];
bool Reverse[N << 2];

void lazy(int i, int range)
{
    tree[i] = range - tree[i];
    Reverse[i] = !Reverse[i];
}

void down(int i, int l, int r)
{
    if (Reverse[i])
    {
        lazy(ls, mid - l + 1);
        lazy(rs, r - mid);
        Reverse[i] = false;
    }
}

void up(int i)
{
    tree[i] = tree[ls] + tree[rs];
}

void update(int i, int l, int r, int L, int R)
{
    if (L <= l && r <= R) tree[i] = (r - l + 1) - tree[i], Reverse[i] = !Reverse[i];
    else
    {
        down(i, l, r);
        if (L <= mid) update(ls, l, mid, L, R);
        if (R > mid) update(rs, mid + 1, r, L, R);
        up(i);
    }
}

int query(int i, int l, int r, int L, int R)
{
    if (L <= l && r <= R) return tree[i];
    down(i, l, r);
    int ans = 0;
    if (L <= mid) ans += query(ls, l, mid, L, R);
    if (R > mid) ans += query(rs, mid + 1, r, L, R);
    return ans;
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int t, l, r; cin >> t >> l >> r;
        if (!t)
        {
            update(1, 1, n, l, r);
        }
        else
        {
            cout << query(1, 1, n, l, r) << endl;
        }
    }
    return 0;
}