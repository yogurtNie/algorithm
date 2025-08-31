//
// Created by 12472 on 25-6-7.
//
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 17;
ll d[1 << N][N];
ll a[N];
int n;
ll k;

ll dp(int s, int i)
{
    if (s == (1 << n) - 1) return 1;
    if (d[s][i] != -1) return d[s][i];

    ll ans = 0;
    for (int j = 0; j < n; j++)
    {
        if ((s & (1 << j)) == 0 && abs(a[j] - a[i]) > k)
        {
            ans += dp(s ^ (1 << j), j);
        }
    }
    d[s][i] = ans;
    return ans;
}


int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < 1 << n; i++)
        for (int j = 0; j <= n; j++)
            d[i][j] = -1;
    ll ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans += dp(1 << i, i);
    }
    cout << ans << endl;
    return 0;

}