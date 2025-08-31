//
// Created by 12472 on 25-5-29.
//
// 二维数组做法，注意，请一定把初始化考虑清楚，0是什么，1是什么
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        int sum = 0;
        for (auto& v : nums) sum += v;
        if ((sum + target) % 2 != 0) return 0;
        if (abs(target) > sum) return 0;
        int left = (sum + target) / 2;
        vector<vector<int>> dp(n + 2, vector<int>(1000 + 2));
        // 这一步做得也不够，能过完全是因为数据集没有难为你
        dp[0][0] = 1;
        dp[0][nums[0]] += 1;
        // 你需要初始化的地方有：矩阵的第一行和第一列
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                dp[i][0] = (1 << (++cnt));
            }
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= left; j++) {
                dp[i][j] = dp[i - 1][j];
                if (j >= nums[i]) dp[i][j] = max(dp[i][j], dp[i - 1][j - nums[i]] + dp[i - 1][j]);
            }
        }
        return dp[n - 1][left];
    }
};
