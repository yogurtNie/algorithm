//
// Created by 12472 on 25-6-3.
//
//
// Created by csp on 2025/5/30.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
typedef long long ll;
int n, m;
struct ST {
#define ls (i << 1)
#define rs (ls | 1)
#define mid ((l + r) >> 1)
    ll maxi[N << 2];
    ll tag[N << 2];
    ST() {
        for (int i = 0; i < (n << 2); i++) {
            maxi[i] = tag[i] = 0;
        }
    }
    void build(int i, int l, int r) {
        if (l == r) cin >> maxi[i];
        else {
            build(ls, l, mid), build(rs, mid + 1, r);
            maxi[i] = max(maxi[ls] ,maxi[rs]);
        }
    }
    void pushdown(int i, int l, int r) {
        if (!tag[i]) return;
        maxi[ls] += tag[i];
        maxi[rs] += tag[i];
        tag[ls] += tag[i], tag[rs] += tag[i];
        tag[i] = 0;         // 晴空标记
    }
    void add(int i, int l, int r, int L, int R, ll k) {
        if (l > R || r < L) return;
        if (L <= l && r <= R) maxi[i] += k , tag[i] += k;
        else {
            pushdown(i, l, r);
            add(ls, l, mid, L, R, k);
            add(rs, mid + 1, r, L, R, k);
            maxi[i] = max(maxi[ls], maxi[rs]);
        }
    }
    ll query(int i, int l, int r, int L, int R) {
        if (L <= l && r <= R) return maxi[i];
        if (l > R || r < L) return 0;
        pushdown(i, l, r);
        ll ans = INT64_MIN;
        if (L <= mid) ans = max(ans, query(ls, l, mid, L, R));
        if (R > mid) ans = max(ans, query(rs, mid + 1, r, L, R));
        return ans;
    }
} seg;

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i ++) {
        int q, l, r; cin >> q >> l >> r;
        if (q == 1) seg.add(1, 1, n, l, r, 1);
        else if (q == 2) cout << seg.query(1, 1, n, l, r) << endl;
    }
    return 0;
}