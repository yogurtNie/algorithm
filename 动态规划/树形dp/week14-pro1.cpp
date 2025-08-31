//
// Created by 12472 on 25-5-23.
//
// 求树的直径和数量，最长简单路径的长度和数量
// 边界是叶子节点
// 如何求树直径的数量？必须要递推拿到所有节点的直径长度，所以不能用 最长 / 次长 来定义数组
// 我们考虑用两个数组来分别维护，dp用于维护以i为根的子树中，最长路径的数量，len用于维护以i为根的子树中，从i出发的最长路径的长度
// 状态转移：
// 当节点i的子节点j，和i的组合路径长度 len[i] + len[j] + 1 > ans, 更新ans = len[i] + len[j] + 1
// 当节点i的子节点j，比i本身的len[i]还要长，更新len[i] = len[j] + 1
// 如果节点j的路径是更长的，那么将cnt更新成dp[i] * dp[j](因为原本经过i的最长路加上j之后一定还是最长路，j同理)
// 如果节点j和节点i的路径长度是相等的，累加dp[i]
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<int> G[N];
int dp[N];
int len[N];
int n, ans = 0, cnt = 0;
void dfs(int u, int f)
{
    dp[u] = 1;
    for (auto& v : G[u])
    {
        if (v != f)
        {
            dfs(v, u);
            if (len[u] + len[v] + 1 > ans)          // 这个子树比目前的最大长度还大
            {
                ans = len[u] + len[v] + 1;
                cnt = dp[u] * dp[v];
            }
            else if (len[v] + len[u] + 1 == ans)    // 这个子树和目前最大长度一样大
            {
                cnt += dp[u] * dp[v];
            }
            if (len[v] + 1 > len[u])
            {
                len[u] = len[v] + 1;
                dp[u] = dp[v];                     // 更新最大支路数量，之前的支路作废
            }
            else if (len[v] + 1 == len[u])          // 如果和最大长度一致，则累加
            {
                dp[u] += dp[v];
            }
        }
    }
}
int main()
{
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, -1);

    cout << ans << " " << cnt << endl;
}