//
// Created by 12472 on 25-6-3.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
typedef long long ll;
#define ls (i << 1)
#define rs (i << 1 | 1)
#define mid (l + r >> 1)

ll tree[N << 2];
ll add[N << 2];
int n;

void build(int l, int r, int i)
{
    if (l == r) cin >> tree[i];
    else
    {
        build(l, mid, ls);
        build(mid + 1, r, rs);
        tree[i] = tree[ls] + tree[rs];
    }
}

void lazy(int i, ll k, int range)
{
    if (k != 0)
    {
        add[i] += k;
        tree[i] += k * range;
    }
}

void down(int i, int l, int r)
{
    if (add[i] != 0)
    {
        // lazy(i, k, l, r);
        lazy(ls, add[i], mid - l + 1);   // 注意，这里下发，发的是懒信息
        lazy(rs, add[i], r - mid);
        add[i] = 0;
    }
}

void up(int i)          // 这个不用把每一层都重置一遍，因为在递归的过程中会不断往上返回
{
    tree[i] = tree[ls] + tree[rs];
}

void update(int i, int L, int R, int l, int r, ll k)
{
    if (L <= l && R >= r)       // 任务范围全包
    {
        lazy(i, k, r - l + 1);
    }
    else
    {
        down(i, l, r);
        if (L <= mid) update(ls, L, R, l, mid, k);
        if (R > mid) update(rs, L, R, mid + 1, r, k);
        up(i);
    }
}

ll query(int i, int L, int R, int l, int r)
{
    if (L <= l && R >= r) return tree[i];
    ll ans = 0;
    down(i, l, r);
    if (L <= mid) ans += query(ls, L, R, l, mid);
    if (R > mid) ans += query(rs, L, R, mid + 1, r);
    return ans;
}

void print()
{
    for (int i = 1; i <= (n << 2); i++) cout << tree[i] << " ";
}

int main()
{
    int m;
    cin >> n >> m;
    build(1, n, 1);
    for (int i = 0; i < m; i++)
    {
        int choice; cin >> choice;
        switch (choice)
        {
            case 1:
                {
                    int l, r; ll k; cin >> l >> r >> k;
                    update(1, l, r, 1, n, k);
                    // print();
                    break;
                }
            case 2:
                {
                    int l, r; cin >> l >> r;
                    cout << query(1, l, r, 1, n) << '\n';
                    // print();
                    break;
                }
            default:
                break;
        }
    }
    // print();
    return 0;
}