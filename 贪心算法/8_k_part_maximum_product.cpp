//
// Created by 12472 on 26-3-18.
//
/*
 * 将一个数字分成k份的最大乘积，求能够得到的乘积尽可能的大是多少
 * n可能达到10^12的规模，返回对1e9 + 7取模的数
 * 无在线测评，使用对数器验证
 */
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
typedef long long ll;
class Solution
{
public:
    ll power(int x, int n, int MOD)
    {
        ll ans = 1, tmp = x;
        while (n)
        {
            if (n & 1) ans = (ans * tmp) % MOD;
            tmp = (tmp * tmp) % MOD;
            n >>= 1;
        }
        return ans;
    }
    // 暴力验证
    int way1(int x, int k)
    {
        if (k == 1) return x;       // 如果只有1次，那就是x
        int ans = INT_MIN;
        // 被分出去的数要比原数小，且剩下的数至少要够k-1来分
        for (int i = 1; i <= x && ((x - i) >= k - 1); i++)
        {
            ans = max(ans, i * way1(x - i, k - 1));
        }
        return ans;     // 这样的缺点是没法处理大数
    }
    int way2(int x, int k)
    {
        int a = x / k;          // x能被分成k个数
        int b = x % k;          // 其中有b个数可以再+1
        ll ans1 = power(a, k - b, MOD);
        ll ans2 = power(a + 1, b, MOD);
        ll ans3 = ans1 * ans2 % MOD;
        return (int)ans3;
    }
    void test()
    {
        int N = 30;
        int testTimes = 2000;
        cout << "测试开始" << endl;
        for (int i = 0 ;i < testTimes ; i++)
        {
            // n的范围在1~N，k的范围在1~n
            int n = rand() % N + 1;
            int k = rand() % n + 1;
            int ans1 = way1(n, k);
            int ans2 = way2(n, k);
            if (ans1 != ans2)
            {
                cout << "测试出错！\n";
                cout << n << " " << k << " " << ans1 << " " << ans2 << endl;
            }
            if (i % 100 == 0) cout << "测试到第" << i << "组" << endl;
        }
        cout << "测试结束" << endl;
    }
};

int main()
{
    Solution sol;
    sol.test();
    return 0;
}


