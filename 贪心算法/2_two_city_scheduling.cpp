//
// Created by 12472 on 26-3-16.
//
/*
 * 公司计划面试 2n 人。给你一个数组 costs ，其中 costs[i] = [aCosti, bCosti] 。第 i 人飞往 a 市的费用为 aCosti ，飞往 b 市的费用为 bCosti
 * 返回将每个人都飞到 a 、b 中某座城市的最低费用，要求每个城市都有 n 人抵达
输入：costs = [[10,20],[30,200],[400,50],[30,20]]
输出：110
解释：
第一个人去 a 市，费用为 10。
第二个人去 a 市，费用为 30。
第三个人去 b 市，费用为 50。
第四个人去 b 市，费用为 20。

最低总费用为 10 + 30 + 50 + 20 = 110，每个城市都有一半的人在面试。
https://leetcode.cn/problems/two-city-scheduling/description/
*/
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        int num = costs.size(), cost = 0;
        vector<int> diff;
        for (int i = 0; i < num; i++)
        {
            diff.push_back(costs[i][1] - costs[i][0]);
            cost += costs[i][0];
        }
        sort(diff.begin(), diff.end());
        for (int i = 0; i < num/2; i++) cost += diff[i];
        return cost;
    }
};

int main()
{
    vector<vector<int>> costs = {{10,20},{30,200},{400,50},{30,20}};
    Solution solution;
    cout << solution.twoCitySchedCost(costs) << endl;
    return 0;
}