//
// Created by 12472 on 25-6-10.
//
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int cnt[N];
ll dp[N];
// dp代表选到这个数的时候的最大值
// 两种可能，选或者不选，如果选的话则左边的数不能选，如果不选的话左边的数可以选
int main()
{
    int n; cin >> n;
    int M = 0;
    for (int i = 0; i < n; i++)
    {
        int x; cin >> x;
        cnt[x]++;
        M = max(M, x);
    }
    // 初始化，第0个数选或者不选和都是0，第1个数则是
    dp[1] = cnt[1];
    for (int i = 2; i <= M; i++)
    {
        dp[i] = max(dp[i - 1], dp[i - 2] + (ll)cnt[i] * i);
    }
    cout << dp[M] << endl;
}