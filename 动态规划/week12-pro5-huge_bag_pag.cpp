//
// Created by 12472 on 25-5-11.
//
// 在超大背包的问题下，传统数组枚举是不现实的，因为背包的大小数量级达到了惊人的10^15
// 那能不能枚举状态呢？有n个物品，n的数量级在40，如果将所有状态都枚举一遍，数量级依旧会到达惊人的2^40
// 因此我们要考虑优化，如果将物品分为前20个和后20个，在前20个中挑选方法对应的重量和以及价值总和为w1, c1
// 这样只需要在后半部分寻找w2 <= W - w1且v2最大的挑选方法即可
// 怎样从枚举得到的(w2, v2)集合中高效地寻找max{v2|w2 <= W}
#include<bits/stdc++.h>
using namespace std;
const int N = 45;   // 40个物品
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3fll;
int n;
ll wei;
ll W[N], V[N];
pair<ll, ll> p[1 << (N / 2)];       // 将所有的物品一分为二，状态总数为2^(n/2)

int main()
{
    cin >> n >> wei;
    for (int i = 0; i < n; i ++)
    {
        cin >> W[i] >> V[i];
    }
    int n1 = n / 2;
    for (int i = 0; i < (1 << n1); i++) // 前一半的状态遍历
    {
        ll prew = 0, prev = 0;
        for (int j = 0; j < n1; j++)    // 物品遍历
        {
            if ((i >> j) & 1)
            {
                prew += W[j];
                prev += V[j];
            }
        }
        p[i] = make_pair(prew, prev);
    }

    sort(p, p + (1 << n1));     // 按照排序
    int m = 1;
    for (int i = 1; i < (1 << n1); i++)
    {
        if (p[m - 1].second < p[i].second)
        {
            p[m++] = p[i];              // 只有当第一个值是递增，且第二个值也为递增时，才能存在
        }
    }

    ll ans = 0;
    for (int i = 0; i < (1 << (n - n1)); i++)  // 在第二个状态里找最小值
    {
        ll prew = 0, prev = 0;
        for (int j = 0; j < n - n1; j++)
        {
            if ((i >> j) & 1)
            {
                prew += W[n1 + j];
                prev += V[n1 + j];
            }
        }
        if (prew <= wei)  // 如果比最大的背包容量要小
        {
            int tmp = (lower_bound(p, p + m, make_pair(wei - prew, INF)) - p) - 1;
            ans = max(ans, p[tmp].second + prev);
        }
    }
    cout << ans << endl;
    return 0;
}