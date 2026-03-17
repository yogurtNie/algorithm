//
// Created by 12472 on 26-3-17.
//
/*
* 在一个果园里，多多已经将所有的果子打了下来，而且按果子的不同种类分成了不同的堆。多多决定把所有的果子合成一堆。
每一次合并，多多可以把两堆果子合并到一起，消耗的体力等于两堆果子的重量之和。可以看出，所有的果子经过 n−1 次合并之后， 就只剩下一堆了。多多在合并果子时总共消耗的体力等于每次合并所耗体力之和。
因为还要花大力气把这些果子搬回家，所以多多在合并果子时要尽可能地节省体力。假定每个果子重量都为 1，并且已知果子的种类 数和每种果子的数目，你的任务是设计出合并的次序方案，使多多耗费的体力最少，并输出这个最小的体力耗费值。
例如有 3 种果子，数目依次为 1，2，9。可以先将 1、2 堆合并，新堆数目为 3，耗费体力为 3 。接着，将新堆与原先的第三堆合并，又得到新的堆，数目为 12，耗费体力为 12。所以多多总共耗费体力 =3+12=15。可以证明 15 为最小的体力耗费值。
第一行是一个整数 n(1≤n≤10^4)，表示果子的种类数。
第二行包含 n 个整数，用空格分隔，第 i 个整数 a_i(1≤a_i≤2×10^4) 是第 i 种果子的数目。
https://www.luogu.com.cn/problem/P1090
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
typedef long long ll;
priority_queue<ll, vector<ll>, greater<ll>> pq;


int main()
{
    int n;ll m; cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> m; pq.push(m);
    }
    ll ans = 0;
    for (int i = 0; i < n - 1; i++)
    {
        ll tmp1 = pq.top(); pq.pop();
        ll tmp2 = pq.top(); pq.pop();
        ans += tmp1 + tmp2;
        pq.push(tmp1 + tmp2);
    }
    cout << ans << endl;
    return 0;
}