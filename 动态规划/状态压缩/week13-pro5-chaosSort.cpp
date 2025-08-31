//
// Created by 12472 on 25-5-14.
//
// 定义状态，有n个互不相同的数的时候可以想着能不能用状态压缩
// 当然可以！定义s为某个排序的状态，置1代表这个数已经在排列里了
// 还需要一个下标，来唯一标识这个序列对应的状态
// 于是定义f(i, s)，代表这个序列的结尾是a[i]，用到的数的状态为s对应的排列方案数
// 状态转移：什么时候是合法的？
// 针对下一个可以填进这个状态的数j，有
// |a[i] - a[j]| > k
// (s & (1 << j)) == 0 代表j不在s中
// f(0, 0) = 0;
// 如果下个状态合法，那么就可以继承这个对应的状态
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 18;
int a[N];
ll f[N][1 << N];

int main()
{
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    // 初始化：所有单选的都置1
    for (int i = 1; i <= n; i++)
        f[i][1 << (i - 1)] = 1;

    // 递推
    for (int s = 1; s < (1 << n); s++)
    {
        for (int i = 1; i <= n; i ++)
        {
            if (s & (1 << (i - 1)) == 0) continue;
            for (int j = 1; j <= n; j++)
            {
                if (abs(a[i] - a[j]) > k && (s & (1 << (j - 1))) == 0)
                    f[j][s | (1 << (j - 1))] += f[i][s];
            }
        }
    }

    // 输出结果
    ll ans = 0;
    for (int i = 1; i <= n; i++) ans += f[i][(1 << n) - 1];
    cout << ans << endl;
    return 0;


}