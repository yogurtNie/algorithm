//
// Created by 12472 on 25-6-3.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int bombStart[N << 2];
int bombEnd[N << 2];
#define ls (i << 1)
#define rs (i << 1 | 1)
#define mid (l + r >> 1)

void up(int i)
{
    bombStart[i] = bombStart[ls] + bombStart[rs];
    bombEnd[i] = bombEnd[ls] + bombEnd[rs];
}

void update(int type, int i, int l, int r, int pos)
{
    if (l == r)
    {
        if (type == 0)
        {
            bombStart[i] += 1;
        }
        else
        {
            bombEnd[i] += 1;
        }
    }
    else
    {
        if (pos <= mid) update(type, ls, l, mid, pos);
        else update(type, rs, mid + 1, r, pos);
        up(i);
    }
}

int query(int type, int i, int l, int r, int L, int R)
{
    if (L <= l && r <= R)
        return (type == 0 ? bombStart[i] : bombEnd[i]);
    int ans = 0;
    if (L <= mid) ans += query(type, ls, l, mid, L, R);
    if (R > mid) ans += query(type, rs, mid + 1, r, L, R);
    return ans;
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int q, l, r; cin >> q >> l >> r;
        if (q == 1)
        {
            update(0, 1, 1, n, l);
            update(1, 1, 1, n, r);
        }
        else if (q == 2)
        {
            int s = query(0, 1, 1, n, 1, r);
            int e = (l == 1 ? 0 : query(1, 1, 1, n, 1, l - 1));
            cout << s - e << endl;
        }
    }
    return 0;
}