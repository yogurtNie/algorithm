//
// Created by 12472 on 26-3-17.
//
/*
* 现需要将一根长为正整数 bamboo_len 的竹子砍为若干段，每段长度均为 正整数。请返回每段竹子长度的 最大乘积 是多少。
答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
输入：bamboo_len = 12
输出：81
https://leetcode.cn/problems/jian-sheng-zi-ii-lcof/description/
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;
class Solution {
public:
    ll power(int x, int n)     // 计算x^n
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
    int cuttingBamboo(int bamboo_len) {
        if (bamboo_len == 1) return 1;
        if (bamboo_len == 2) return 1;
        if (bamboo_len == 3) return 2;
        int tail = (bamboo_len % 3 == 0) ? 1 : ((bamboo_len % 3 == 1) ? 4 : 2);
        int m = (tail == 1 ? bamboo_len : bamboo_len - tail) / 3;
        ll ans = (power(3,  m) * tail) % MOD;
        return (int)ans;
    }
};

int main()
{
    Solution sol;
    cout << sol.cuttingBamboo(12) << endl;
}