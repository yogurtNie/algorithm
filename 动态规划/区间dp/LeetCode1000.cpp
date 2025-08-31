//
// Created by 12472 on 25-6-9.
//
// 合并石子的最小代价
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> pre;
    int mergeStones(vector<int>& stones, int k) {
        int len = stones.size();
        pre.resize(len + 1, 0);
        for (int i = 1; i <= len; i++) {
            pre[i] = stones[i - 1] + pre[i - 1];
        }
        if ((len - 1) % (k - 1) != 0) return -1;
        vector<vector<int>> dp(len, vector<int>(len, -1));
        int ans = func(stones, 0, len - 1, k, dp);
        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < len; j++)
            {
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }
        return ans;
    }
    int func(vector<int>& stones, int l, int r, int k, vector<vector<int>>& dp) {
        if (dp[l][r] != -1) return dp[l][r];
        if (l == r) return 0;

        int ans = INT_MAX;
        for (int i = l; i < r; i += (k - 1)) {
            ans = min(ans, func(stones, l, i, k, dp) + func(stones, i + 1, r, k, dp));
        }
        if ((r - l) % (k - 1) == 0) ans += pre[r + 1] - pre[l];
        return dp[l][r] = ans;
    }

};

int main()
{
    Solution sol;
    vector<int> stones = {3, 2, 4, 1};
    cout << sol.mergeStones(stones, 2) << endl;
    return 0;
}