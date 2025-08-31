//
// Created by 12472 on 25-5-14.
//
// 用一个s来标识当前棋盘，N位，则为1 << (N - 1) 的大小，每位置1代表该位放了棋子
// 状态方程：f(i, s)表示的是第i个国王对应的填充状态
// 够吗？不够，因为还有一个信息：在第几行填充（s本身代表了列的填充信息）
// 状态方程更新为：f(i, j, s)，表明前i行已经填充过，目前第j个国王对应的填充状态为s对应的方案数
// 状态怎样才是合法的？
// 对于行内状态来说，必不能有两个连续的1存在，因此可以得到一个状态判别式：s & (s << 1) == 0
// 对于行间状态来说，一个1的右上、正上、左上必不能有1；当用t来表示上一行的状态时，我们有
// s & t == 0 && s & (t << 1) == 0 && s & (t >> 1) == 0
// 状态转移：当判定当前状态合法的时候，就可以将上层的状态加到本层之上
// 初始化：f(0, 0, 0) = 1
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 13;
ll f[N][N * N][1 << N];
int main()
{
    int n, k; cin >> n >> k;
    memset(f, 0, sizeof f);

    vector<int> vt;
    // 先找到所有行内状态合法的状态，之后直接从中开始选状态依次转移
    for (int s = 0; s < (1 << n); s++)
        if ((s & (s << 1)) == 0)
        {
            vt.push_back(s);
        }

    f[0][0][0] = 1;
    // 开始递推
    for (int i = 1; i <= n; i++)    // 行号
    {
        for (auto& t : vt) // 上一行
        {
            for (auto& s : vt)     // 本行
            {
                if ((s & t) == 0 && ((s & (t << 1)) == 0) && ((s & (t >> 1)) == 0))
                {
                    int w = __builtin_popcount(s);
                    for (int j = w; j <= k; j++)
                    {
                        f[i][j][s] += f[i - 1][j - w][t];
                    }
                }
            }
        }

    }

    ll ans = 0;
    for (auto& s : vt) ans += f[n][k][s];
    cout << ans << endl;
    return 0;
}