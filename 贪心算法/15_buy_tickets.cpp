//
// Created by 12472 on 26-3-21.
//
/*
 * 组团买票，景区里面有m个项目，第i个项目有两个参数，game[i]={Ki, Bi}，均为正数
 * 以Ki = 2，Bi = 10为例
 * 如果只有1个人买票，那么要花的票钱为 Bi - Ki * 1 = 8
 * 2个人，则花Bi - Ki * 2 = 6
 * 以此类推，如果有5个人，则花 Bi - Ki * 5 = 0，大于5人时统统按照0元
 * 即x个人游玩项目的花费是：max{x * (Bi - Ki * x), 0}
 * 问单位有n个人，每个人最多选1个项目游玩，需要你来按照可能的最大花费来准备
 * 问最保险的钱数 —— 其实就是景区能赚到的最多钱
 * 1 <= M,N,Ki,Bi <= 10^5
 */
#include <bits/stdc++.h>
using namespace std;
struct Game         // 当前项目
{
    int Bi;
    int Ki;
    int num;        // 游玩人数
    Game(int Bi=0, int Ki=0, int num=0):Bi(Bi), Ki(Ki), num(num){}
    int earn() const
    {
        return Bi - (2 * num + 1) * Ki;
    }
};
struct MyCompare
{
    bool operator()(struct Game&a,struct Game&b) const
    {
        return a.earn() < b.earn();         // 大根堆
    }
};
class Solution
{
public:
    int way1(vector<vector<int>>& tickets, int n)
    {
        int m = tickets.size();
        vector<int> cnts(m,0);
        return f(0, n, m, tickets, cnts);
    }
    int f(int i, int n, int m, vector<vector<int>>& tickets, vector<int>& cnts)
    {
        // 结算时刻，已经所有人都分配了
        if (i == n)
        {
            int ans = 0;
            for (int j = 0; j < m; j++)
            {
                ans += max(0, (tickets[j][0] - cnts[j] * tickets[j][1]) * cnts[j]);
            }
            return ans;
        }
        // 递归
        else
        {
            // 如果第i号人不选择任何项目
            int ans = f(i + 1, n, m, tickets, cnts);
            // 第i号人依次选择0,1,2...号项目
            for (int j = 0; j < m; j++)
            {
                cnts[j]++;
                ans = max(ans, f(i + 1, n, m, tickets, cnts));
                cnts[j]--;
            }
            return ans;
        }
    }
    int way2(vector<vector<int>> &tickets, int n)
    {
        priority_queue<struct Game,vector<Game>, MyCompare> p;
        int m = tickets.size();
        for (int i = 0; i < m; i++)
        {
            p.emplace(tickets[i][0], tickets[i][1],0);
        }
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            if (p.top().earn() < 0) break;
            struct Game tmp = p.top();
            p.pop();
            ans += tmp.earn();
            struct Game tmp2 = Game(tmp.Bi, tmp.Ki, tmp.num + 1);
            p.push(tmp2);
        }
        return ans;
    }
    void test()
    {
        int N = 8, M = 8;
        int V = 20;
        int testTime = 2000;
        cout << "测试开始\n";
        for (int i = 0; i < testTime; i++)
        {
            int n = rand() % N + 1;
            int m = rand() % M + 1;
            vector<vector<int>> tickets;
            for (int j = 0; j < m; j++)
            {
                int Bi = rand() % V + 1;
                int Ki = rand() % V + 1;
                tickets.emplace_back(Bi, Ki);
            }
            int ans1 = way1(tickets, n);
            int ans2 = way2(tickets, n);
            if (ans1 != ans2)
            {
                cout << "答案错误\n";
                cout << ans1 << " " << ans2 << endl;
            }
            if (i % 100 == 0) cout << "测试到第" << i <<"组\n";
        }
        cout << "测试结束\n";
    }
};
int main()
{
    Solution sol;
    sol.test();
    return 0;
}
