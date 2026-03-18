//
// Created by 12472 on 26-3-18.
//
/*
 * 会议必须独占时间段的最大会议数量
 * 给定若干会议的开始与结束时间，参加某个会议期间不能参加其他会议
 * 返回能够参加的最大会议数量
 * 无在线测试，使用对数器验证
 */
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int way1(vector<vector<int>>& meetings)
    {
        return f(meetings, meetings.size(), 0);
    }
    int f(vector<vector<int>>& meetings, int n, int i)
    {
        int ans = 0;        // 当前状态下的ans为0
        if (i == n)
        {
            int cur = -1;
            for (int j = 0; j < n; j++)
            {   // 如果当前时间还能开始，那就开始
                if (cur <= meetings[j][0])
                {
                    cur = meetings[j][1];
                    ans++;
                }
            }
        }
        else
        {   // 从i开始
            for (int j = i; j < n; j++)
            {
                swap(meetings[j], meetings[i]);
                ans = max(ans, f(meetings, n, i + 1));
                swap(meetings[j], meetings[i]);
            }
        }
        return ans;
    }
    int maxMeetingNumber(vector<vector<int>> &meetings)
    {
        // 按照结束时间排序
        sort(meetings.begin(), meetings.end(), [](vector<int>&a, vector<int>&b)->bool{return a[1] < b[1];});
        int ans = 0, cur = -1;      // cur为当前的时间点，如果比当前时间点小，那么必然是可以纳入答案集的
        for (int i = 0; i < meetings.size(); i++)
        {
            if (cur <= meetings[i][0])
            {
                ans++;
                cur = meetings[i][1];
            }
        }
        return ans;
    }
    // n个会议列表，每个会议时间最大是m
    vector<vector<int>> generateMeetings(int n, int m)
    {
        vector<vector<int>> meetings;
        for (int i = 0; i < n; i++)
        {
            vector<int> temp;
            int a = rand() % m + 1;
            int b = rand() % m + 1;
            if (a == b)
            {
                temp.push_back(a);
                temp.push_back(a + 1);
            }
            else
            {
                temp.push_back(min(a, b));
                temp.push_back(max(a, b));
            }
            meetings.push_back(temp);
        }
        return meetings;
    }
    void test()
    {
        int N = 10;
        int M = 12;
        int testTimes = 2000;
        cout << "测试开始" << endl;
        for (int i = 0; i < testTimes; i++)
        {
            int n = rand() % N + 1;
            int m = rand() % M + 1;
            vector<vector<int>> meetings = generateMeetings(n, m);
            int ans1 = way1(meetings);
            int ans2 = maxMeetingNumber(meetings);

            if (ans1 != ans2)
            {
                cout << "出错！\n";
                cout << n << " " << m << " " << ans1 << " "<< ans2 <<endl;
            }
            if (i % 100 == 0) cout << "测试到第" << i << "组" << endl;
        }
        cout << "测试完成" << endl;
    }
};

int main()
{
    Solution sol;
    sol.test();
    return 0;
}