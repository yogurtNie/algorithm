//
// Created by 12472 on 25-6-7.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 10;
typedef long long ll;
ll d[1 << N][N][N * N];
vector<int> valid;
int n, k;

ll dp(int s, int i, int j)
{
    if (i <= n - 1 && j == k) return 1;
    if (i >= n - 1 && j < k) return 0;
    if (d[s][i][j] != -1) return d[s][i][j];

    ll ans = 0;

    for (int t : valid)
    {
        if ((s & (t << 1)) == 0 && (s & t) == 0 && (s & (t >> 1)) == 0)
        {
            int cur = t, cnt = 0;
            while (cur)
            {
                cnt++;
                cur ^= (cur & -cur);
            }
            ans += dp(t, i + 1, j + cnt);
        }
    }
    d[s][i][j] = ans;
    return ans;

}


int main()
{
    cin >> n >> k;
    for (int s = 0; s < 1 << n; s++)
    {
        if ((s & (s >> 1)) == 0) valid.push_back(s);
    }
    for (int i = 0; i < 1 << n; i++)
        for (int j = 0; j < n; j++)
            for (int l = 0; l <= k; l++)
                d[i][j][l] = -1;

    ll ans = 0;
    for (int s : valid)
    {
        int cur = s, cnt = 0;
        while (cur)
        {
            cnt++;
            cur ^= (cur & -cur);
        }
        ans += dp(s, 0, cnt);
    }
    cout << ans << endl;
}