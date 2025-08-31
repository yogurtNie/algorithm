//
// Created by 12472 on 25-6-10.
//
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;
class Solution {
public:
    vector<vector<pii>> G;
    // 对于G来说，首位是下标，第二位是距离
    vector<int> dis;
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        G.resize(n);
        for (int i = 0; i < times.size(); i++)
        {
            G[times[i][0]].emplace_back(times[i][1], times[i][2]);
        }
        dis.resize(n + 1, INF);
        priority_queue<pii, vector<pii>, greater<>> q;
        // 对于q来说，首位是距离，第二位是点下标
        q.emplace(0, k);
        dis[k] = 0;
        while (!q.empty())
        {
            auto [d, u] = q.top();
            q.pop();
            if (d > dis[u]) continue;
            for (auto [v, w] : G[u])
            {
                if (dis[u] + w < dis[v])
                {
                    dis[v] = dis[u] + w;
                    q.emplace(dis[v], v);
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            if (dis[i] == INF)
            {
                return -1;
            }
            ans = max(ans, dis[i]);
        }
        return ans;
    }
};

int main()
{
    Solution s;
    vector<vector<int>> times = {{2,1,1}, {2,3,1}, {3,4,1}};
    cout << s.networkDelayTime(times, 4, 2) << endl;
    return 0;
}