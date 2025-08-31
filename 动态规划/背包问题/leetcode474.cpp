//
// Created by 12472 on 25-5-29.
//
#include<bits/stdc++.h>
using namespace std;
pair<int, int> cal(string& s) {
    int zn = 0, on = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '0') zn++;
        else on++;
    }
    return make_pair(zn, on);
}
int findMaxForm(vector<string>& strs, int m, int n) {
    // 一个0-1背包问题，为什么不是多重背包而是0-1背包呢？其实是因为0/1这两个元素并不是物品，而应该是物品“重量”的两个维度，物品应该是每个子集；这是一个求方法数的题目，所以我们设dp[i][j]为有i个0和j个1时最多可以具有的子集数
    vector<vector<int>> dp(6002, vector<int>(6002));
    // 考虑怎么初始化，dp[0][0]必定是0，dp[1][0]为所有有0的子集集合，dp[0][1]为所有有1的子集集合数
    // 转移方程：dp[i][j] = max(dp[i][j], dp[i - ZeroNum][j - OneNum] + 1); zn代表的是对应str里有的0和1数量，在所有里面选最大的

    dp[0][0] = 0;
    for (auto & str : strs) {
        auto[zn, on] = cal(str);
        //cout << zn << " " << on << " " << endl;
        // 一定是从后往前遍历，不然后面基于前面已经加上这个物品的状态是会被污染的
        for (int i = m; i >= zn; i--) {
            for (int j = n; j >= on; j--) {
                dp[i][j] = max(dp[i][j], dp[i - zn][j - on] + 1);
            }
        }
        // for (int i = 0; i <= m; i++)
        // {
        //     for (int j = 0; j <= n; j++)
        //     {
        //         cout << dp[i][j] << " ";
        //     }
        //     cout << endl;
        // }
    }
    return dp[m][n];
}

int main()
{
    vector<string> strs = {"10", "0001", "111001", "1", "0"};
    cout << findMaxForm(strs, 5, 3) << endl;
}