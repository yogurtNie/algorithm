//
// Created by 12472 on 26-3-18.
//
/*
* 给你一个数组events，其中events[i] = [startDayi, endDayi]，表示会议i开始于startDayi，结束于endDayi。
你可以在满足startDayi<= d <= endDayi中的任意一天d参加会议i。在任意一天d中只能参加一场会议。
请你返回你可以参加的最大会议数目。
输入：events = [[1,2],[2,3],[3,4]]
输出：3
解释：你可以参加所有的三个会议。
安排会议的一种方案如上图。
第 1 天参加第一个会议。
第 2 天参加第二个会议。
第 3 天参加第三个会议。
1 <= events.length <= 105
events[i].length == 2
1 <= startDayi <= endDayi <= 105
https://leetcode.cn/problems/maximum-number-of-events-that-can-be-attended/description/
 */
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        priority_queue<int, vector<int>, greater<int>> q;   // 小根堆
        sort(events.begin(), events.end(), [](vector<int>& a, vector<int>& b)->bool{return a[0] < b[0];});
        int days = 1, i = 0, ans = 0;
        while (i < events.size())
        {
            while (i < events.size() && events[i][0] <= days)
            {
                q.push(events[i][1]);
                i++;
            }
            while (!q.empty() && q.top() < days) q.pop();
            days = q.top();
            q.pop();
            ans++;
        }
        return ans;

    }
};

int main()
{
    vector<vector<int>> events = {{1,2},{2,3},{3,4}};
    Solution s;
    cout << s.maxEvents(events);
    return 0;
}