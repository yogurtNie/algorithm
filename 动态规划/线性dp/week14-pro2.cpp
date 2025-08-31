//
// Created by 12472 on 25-5-23.
//
// 滑动队列优化
// 状态方程：d(i) 为以i结尾的最大区间和，其实最终只需要求max{d(i)}
// 状态转移方程: d(i) = pre[i] - min{pre[k]} 其中 i - m <= k <= i
// 优化一下，怎样快速地拿到min？滑动队列维护区间前缀和的最小值
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
typedef long long ll;
ll pre[N], d[N];

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        int now; cin >> now;
        pre[i] = pre[i - 1] + now;
    }
    deque<int> q;
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        while (!q.empty() && pre[q.back()] > pre[i]) q.pop_back();
        while (!q.empty() && q.front() < i - m) q.pop_front();
        q.push_back(i);

        d[i] = pre[i] - pre[q.front()];
        ans = max(ans, d[i]);
    }
    cout << ans << endl;
    return 0;
}