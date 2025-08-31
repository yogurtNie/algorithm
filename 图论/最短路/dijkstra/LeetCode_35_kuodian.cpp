//
// Created by 12472 on 25-6-12.
//
// 电动车游城市，充电决策问题，应该如何决定充电和游玩
// 扩点
// 城市编号 + 在城市的电量来定义一个状态
#include <bits/stdc++.h>
using namespace std;
struct node
{
    int num, cnt, time;           // 到一个城市，cnt是电量，time是这个状态的耗时
    node(int num, int c, int t) : num(num), cnt(c), time(t) {}
};
class MyCompare
{
public:
    bool operator()(const node& a, const node& b) const
    {
        return a.time > b.time;
    }
};
class Solution {
public:
    int electricCarPlan(vector<vector<int>>& paths, int cnt, int start, int end, vector<int>& charge) {
        // 先建图
        int n = charge.size();
        vector<pair<int,int>> G[n + 1];
        for (int i = 0; i < paths.size(); i++)
        {
            G[paths[i][0]].emplace_back(paths[i][1], paths[i][2]);
            G[paths[i][1]].emplace_back(paths[i][0], paths[i][2]);
        }

        int vis[n + 1][cnt + 1];
        int dis[n + 1][cnt + 1];
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= cnt; j++)
            {
                dis[i][j] = 0x3f3f3f3f;
                vis[i][j] = 0;
            }
        }
        // 初始的状态是，将起点加入优先级队列中，并设置好dis
        priority_queue<node, vector<node>, MyCompare> pq;
        pq.push(node(start, 0, 0));                 // 当前状态为，在起点且电量为0
        dis[start][0] = 0;
        vis[start][0] = 1;
        while (!pq.empty())
        {
            node cur = pq.top(); pq.pop();
            int num = cur.num, c = cur.cnt, time = cur.time;
            // 如果已经到达终点，则说明找到解
            if (num == end)
            {
                return time;
            }
            // 否则开始在本次最优上扩展
            vis[num][c] = 1;
            // 如果在该城市充电，来到下一个状态(只有当未满电的时候可以充电
            if (c < cnt)
            {
                if (!vis[num][c + 1] && dis[num][c + 1] > time + charge[num])
                {
                    dis[num][c + 1] = time + charge[num];
                    pq.push(node(num, c + 1, time + charge[num]));
                }
            }
            // 如果在该城市不充电，直接去下一个城市
            for (auto [id, cost] : G[num])
            {
                if (vis[id][c]) continue;
                int nc, nt;
                // 电量够才能去
                if (c >= cost && !vis[id][c - cost])
                {
                    nc = c - cost;
                    nt = time + cost;
                    if (dis[id][nc] > nt)
                    {
                        dis[id][nc] = nt;
                        pq.push(node(id, nc, nt));
                    }
                }

            }
        }
        return -1;
    }
};

int main()
{
    vector<vector<int>> paths = {{1,3,3},{3,2,1},{2,1,3},{0,1,4},{3,0,5}};
    vector<int> charges = {2,10,4,1};
    Solution sol;
    cout << sol.electricCarPlan(paths, 6, 1, 0, charges) << endl;
    return 0;
}