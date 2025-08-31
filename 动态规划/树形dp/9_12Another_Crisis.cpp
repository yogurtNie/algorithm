//
// Created by 12472 on 25-5-16.
//
// 工人要向老板请愿，当直系下属中有超过T%的人都上书请愿，则这个人也会向上请愿
// 求让老板看到请愿书的最小工人签字成本
// 1. 确定状态：d(i)代表，以i为根节点的子树向上请愿的工人成本
// 2. 状态转移：i向上请愿需要的人数为（假设有k个孩子）c = ceil(k * (double)(T/100))
// 取最小，也就是将孩子按成本从小到大排序，取前c个
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<int> sons[N];        // sons[i]代表i的所有子节点集合
int n, T;
int d[N];
int dp(int u)
{
    if (sons[u].empty()) return 1;
    vector<int> temp;
    for (auto& i : sons[u])
    {
        temp.push_back(dp(i));
    }
    sort(temp.begin(), temp.end());
    int k = sons[u].size();
    int c = (k * T - 1) / 100 + 1;
    int ans = 0;
    for (int i = 0; i < c; i++) ans += temp[i];
    return ans;
}


int main()
{
    while (cin >> n >> T)
    {
        if (n == 0 && T == 0) break;
        memset(d, 0, sizeof(d));
        for (int i = 0; i <= n; i++) sons[i].clear();

        for (int i = 1; i <= n; i++)
        {
            int s; cin >> s;
            sons[s].push_back(i);
        }

        cout << dp(0) << "\n";
    }
    return 0;
}
