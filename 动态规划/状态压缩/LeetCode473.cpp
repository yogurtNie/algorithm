//
// Created by 12472 on 25-6-6.
//
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int d[1 << 16];
bool dp(ll size, ll len, ll s, int cnt, int n, vector<int>& v, int* d)
{
    if (cnt == 0) {
        if (s == 0) return true;
        return false;
    }
    if (d[s] != 0) return d[s] == 1;

    bool ans = false;
    for (int i = 0; i < n; i++) {
        if ((s & (1 << i)) != 0 && len - v[i] >= 0) {
            if (len - v[i] == 0) {
                ans = dp(size, size, s ^ (1 << i), --cnt, n, v, d);
            }
            else if (len - v[i] > 0) {
                ans = dp(size, len - v[i], s ^ (1 << i), cnt, n, v, d);
            }
            if (ans) break;
        }
    }

    d[s] = (ans ? 1 : -1);

    return ans;
}

bool makesquare(vector<int>& matchsticks) {
    int n = matchsticks.size();
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        sum += matchsticks[i];
    }
    if (sum % 4 != 0) return false;
    ll len = sum / 4;
    return dp(len, len, (1 << n) - 1, 4, n, matchsticks, d);
}

int main()
{
    vector<int> v = {3,3,3,3,4};
    if (makesquare(v)) cout << "true" << endl;
    else cout << "false" << endl;
    return 0;
}
