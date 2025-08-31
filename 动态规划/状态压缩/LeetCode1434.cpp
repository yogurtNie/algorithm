//
// Created by 12472 on 25-6-6.
//
#include<bits/stdc++.h>
using namespace std;
int h[42];
int MOD = 1e9 + 7;
int maxIdx, n;
int d[1 << 11][42];
int dp(int s, int i);
int numberWays(vector<vector<int>>& hats) {
    // 找到最大的颜色数
    maxIdx = 0, n = hats.size();
    for (int i = 0; i < n; i++) {
        for (int j : hats[i])
            maxIdx = max(j, maxIdx);
    }
    // 外层代表人，内层代表帽子
    for (int i = 0; i < n; i++) {
        // 统计出这个帽子能适配的人
        for (int j : hats[i]) h[j] |= (1 << i);
    }
    for (int i = 0; i < 1 << n + 1; i++) {
        for (int j = 0; j < maxIdx + 1; j++)
            d[i][j] = -1;
    }
    // 开始dp
    // 核心思路是，s的状态代表着目前已经被满足了多少人；i的状态代表着目前分配到了哪种帽子
    return dp(0, 1);
}
int dp(int s, int i) {
    if (s == (1 << n) - 1) return 1;        // 找到了完全能满足的方法
    if (i > maxIdx) return 0;
    if (d[s][i] != -1) return d[s][i];

    // 开始遍历所有情况
    // 第一种情况，当前的帽子不分配
    int ans = dp(s, i + 1);
    // 第二种情况，当前的帽子分配
    // 因此开始遍历能分配给谁
    for (int j = 0; j < n; j++) {
        // 含义为，当前的人没有被分配到，且当前的种类被这个人喜欢
        if ((s & (1 << j)) == 0 && (h[i] & (1 << j)) != 0) {
            ans = (ans + dp(s ^ (1 << j), i + 1)) % MOD;
        }
    }

    d[s][i] = ans;
    return ans;
}

int main()
{
    vector<vector<int>> hats = {{3,4},{4,5},{5}};
    cout << numberWays(hats) << endl;
    return 0;
}