//
// Created by 12472 on 25-5-10.
//
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e4 + 10;
ll dp[N];

int main()
{
    int n, V; cin >> n >> V;
    // 二进制优化
    vector<pair<int, ll>> vec;
    for (int i = 1; i <= n; i++)
    {
        int w, c, k; cin >> w >> c >> k;
        int s = 1;
        while (k > 0)
        {
            int now = min(s, k);
            vec.push_back({w * now, (ll)c * now});
            k -= now;
            s *= 2;
        }
    }

    // 变成0-1背包
    for (auto&[w, c] :vec)
    {
        for (int j = V; j >= w; j--)
            dp[j] = max(dp[j], dp[j - w] + c);
    }
    cout << dp[V] << endl;
    return 0;
}