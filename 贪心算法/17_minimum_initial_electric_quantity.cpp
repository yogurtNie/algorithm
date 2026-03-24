//
// Created by 12472 on 26-3-23.
//
/*
 * 执行所有任务的最少初始电量
 * 每一个任务有两个参数，需要消耗的电量，以及至少多少电量才能开始这个任务
 * 返回手机至少需要多少的初始电量，才能执行完所有的任务
* 给你一个任务数组 tasks ，其中 tasks[i] = [actual_i, minimum_i] ：
actual_i 是完成第 i 个任务 需要耗费 的实际能量。
minimum_i 是开始第 i 个任务前需要达到的最低能量。
比方说，如果任务为 [10, 12] 且你当前的能量为 11 ，那么你不能开始这个任务。如果你当前的能量为 13 ，你可以完成这个任务，且完成它后剩余能量为 3 。
你可以按照 任意顺序 完成任务。
请你返回完成所有任务的 最少 初始能量。
 * https://leetcode.cn/problems/minimum-initial-energy-to-finish-tasks/description/
 */
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        sort(tasks.begin(), tasks.end(), [](vector<int>& a, vector<int>& b)->bool{return a[0] - a[1] > b[0] - b[1];});
        int ans = 0;
        for (int i = 0; i < tasks.size(); i++)
        {
            ans = max(ans + tasks[i][0], tasks[i][1]);
        }
        return ans;
    }
};
int main()
{
    vector<vector<int>> tasks = {{1,2},{2,4},{4,8}};
    Solution sol;
    cout << sol.minimumEffort(tasks) << endl;
    return 0;
}
