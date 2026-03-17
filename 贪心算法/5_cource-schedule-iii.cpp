//
// Created by 12472 on 26-3-17.
//
/*
* 这里有 n 门不同的在线课程，按从 1 到 n 编号。给你一个数组 courses ，其中 courses[i] = [durationi, lastDayi] 表示第 i 门课将会 持续 上 durationi 天课，并且必须在不晚于 lastDayi 的时候完成。
你的学期从第 1 天开始。且不能同时修读两门及两门以上的课程。
返回你最多可以修读的课程数目。
输入：courses = [[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]
输出：3
解释：
这里一共有 4 门课程，但是你最多可以修 3 门：
首先，修第 1 门课，耗费 100 天，在第 100 天完成，在第 101 天开始下门课。
第二，修第 3 门课，耗费 1000 天，在第 1100 天完成，在第 1101 天开始下门课程。
第三，修第 2 门课，耗时 200 天，在第 1300 天完成。
第 4 门课现在不能修，因为将会在第 3300 天完成它，这已经超出了关闭日期。

输入：courses = [[1,2]]
输出：1

输入：courses = [[3,2],[4,3]]
输出：0

1 <= courses.length <= 10^4
1 <= durationi, lastDayi <= 10^4

 */
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        priority_queue<int> q;       // 大根堆，用于收容代价
        sort(courses.begin(), courses.end(), [](vector<int>& a, vector<int>& b){return a[1] < b[1];});
        int time = 0;
        for (int i = 0; i < courses.size(); i++)
        {
            // 如果当前时间加上当前代价比限制小，则默认纳入答案
            if (time  + courses[i][0] <= courses[i][1])
            {
                q.push(courses[i][0]);
                time += courses[i][0];
            }
            // 否则，回退一个代价，选择更小的那个代价
            else
            {
                if (!q.empty() && q.top() > courses[i][0])
                {
                    time += courses[i][0] - q.top();
                    q.pop();
                    q.push(courses[i][0]);
                }
            }
        }
        return q.size();
    }
};

int main()
{
    vector<vector<int>> courses = {{100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}};
    Solution sol;
    cout << sol.scheduleCourse(courses);
    return 0;
}