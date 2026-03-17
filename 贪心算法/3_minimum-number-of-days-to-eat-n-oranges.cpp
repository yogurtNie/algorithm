//
// Created by 12472 on 26-3-16.
//
/*
* 厨房里总共有 n 个橘子，你决定每一天选择如下方式之一吃这些橘子：
吃掉一个橘子。
如果剩余橘子数 n 能被 2 整除，那么你可以吃掉 n/2 个橘子。
如果剩余橘子数 n 能被 3 整除，那么你可以吃掉 2*(n/3) 个橘子。
每天你只能从以上 3 种方案中选择一种方案。
请你返回吃掉所有 n 个橘子的最少天数。
输入：n = 10
输出：4
解释：你总共有 10 个橘子。
第 1 天：吃 1 个橘子，剩余橘子数 10 - 1 = 9。
第 2 天：吃 6 个橘子，剩余橘子数 9 - 2*(9/3) = 9 - 6 = 3。（9 可以被 3 整除）
第 3 天：吃 2 个橘子，剩余橘子数 3 - 2*(3/3) = 3 - 2 = 1。
第 4 天：吃掉最后 1 个橘子，剩余橘子数 1 - 1 = 0。
你需要至少 4 天吃掉 10 个橘子。
1 <= n <= 2*10^9
https://leetcode.cn/problems/minimum-number-of-days-to-eat-n-oranges/description/
 */
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    map<int, int> mp;
    int minDays(int n) {
        // 如果只有1个以下的橘子，则直接吃
        if (n <= 1) return n;
        // 如果在1个以上
        if (mp.count(n) != 0) return mp[n];
        // 如果橘子能够被2整除，则天数应该是0 + minDay(n/2) + 1
        // 如果橘子不能被2整除，但还是想用2的策略来吃，则天数应该是1 + minDay((n-1)/2) + 1
        // 如果橘子能够被3整除，则天数应该是0 + minDay(n * 2 / 3) + 1
        // 如果n % 3 == 1，则应该是 1 + minDay((n-1) *2 /3) + 1
        // 如果n % 3 == 2，则应该是 2 + minDay((n-2) *2 /3) + 1
        int ans = min(n % 2 + 1 + minDays(n / 2),n % 3 + 1 + minDays(n / 3));
        mp[n] = ans;
        return ans;

    }
};

int main()
{
    Solution s;
    cout << s.minDays(56);
    return 0;
}