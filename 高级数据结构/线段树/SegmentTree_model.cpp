//
// Created by 12472 on 25-12-4.
//
/*
 * 由二叉树的性质，定义线段树上点下标与区间下标的便捷运算
 */
#define ls (i << 1)
#define rs (i << 1 | 1)
#define mid (l + r >> 1)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
ll Tree[N << 2];            // 扩大四倍
ll add[N << 2];            // 懒信息

// 初始化数组，这里我们可以在线输入也可以离线输入
/*
 * i: 当前所处位置下标
 * [l, r]: 当前所处位置代表的信息汇总覆盖范围
 */
void build(int i, int l, int r)
{
    if (l == r)
    {
        cin >> Tree[i];             // 如果已经相等，说明到了叶子节点
    }
    else
    {   // 递归调用，把任务下发下去，回溯回来的时候记得汇总
        build(ls, l, mid), build(rs, mid + 1, r);
        Tree[i] = Tree[ls] + Tree[rs];
    }
    add[i] = 0;                     // 初始化懒信息
}

// lazy的具体实现
/*
 * 因为这里维护的是累加和信息，所以我们要有范围加法的具体加数，以及范围长度
 * 在O(1)的时间内把累加和算出来
 *
 */
void lazy(int i, ll k, int range)
{
    Tree[i] += k * range;
    add[i] += k;
}

// 下发懒标签
/*
 *  i ~ [l, r]: 线段树对应的节点下标以及覆盖范围
 */
void down(int i, int l, int r)
{
    if (add[i] != 0)
    {   // 有堆积的标签在身的时候，才去下发
        lazy(ls, add[i], mid - l + 1);
        lazy(rs, add[i], r - mid);
        add[i] = 0;
    }
}

// 向上汇总
/*
 * 这也是一个递归的过程，要一路刷新因为不清楚到底之前欠了多少层
 */
void up(int i)
{
    Tree[i] = Tree[ls] + Tree[rs];
}

// 区间更新
/*
 * [L, R]: 任务范围
 * k: 需要新增的信息
 * i: 当前所处的线段树节点
 * [l, r]: 当前节点代表的范围
 */
void update(int L, int R, ll k, int i, int l, int r)
{
    if (L <= l && r <= R) lazy(i, k, r - l + 1);
    else
    {   // 把当前层的懒信息下发下去
        down(i, l, r);
        if (L <= mid) update(L, R, k, ls, l, mid);
        if (R > mid) update(L, R, k, rs, mid + 1, r);
        up(i);      // 记得汇总信息
    }
}

// 区间查询
/*
 * [L, R]: 任务范围
 * i ~ [l, r]: 线段树节点下标及覆盖范围
 *
 */
ll query(int L, int R, int i, int l, int r)
{
    if (L <= l && r <= R) return Tree[i];
    ll ans = 0;
    down(i, l, r);
    if (L <= mid) ans += query(L, R, ls, l, mid);
    if (R > mid) ans += query(L, R, rs, mid + 1, r);
    // up(i);               // 为什么这里不需要再向上汇总？
    return ans;
}

int main()
{
    int n, m; cin >> n >> m;
    build(1, 1, n);
    for (int i = 0; i < m; i++)
    {
        int choice; cin >> choice;
        if (choice == 1)
        {
            int x, y;ll k; cin >> x >> y >> k;
            update(x, y, k, 1, 1, n);
        }
        else if (choice == 2)
        {
            int x, y; cin >> x >> y;
            cout << query(x, y, 1, 1, n) << "\n";
        }
    }
    return 0;
}