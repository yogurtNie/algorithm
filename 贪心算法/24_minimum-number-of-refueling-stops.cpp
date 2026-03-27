//
// Created by 12472 on 26-3-27.
//
/*
 * 汽车从起点出发驶向目的地，该目的地位于出发位置东面 target 英里处。
沿途有加油站，用数组 stations 表示。其中 stations[i] = [positioni, fueli] 表示第 i 个加油站位于出发位置东面 positioni 英里处，并且有 fueli 升汽油。
假设汽车油箱的容量是无限的，其中最初有 startFuel 升燃料。它每行驶 1 英里就会用掉 1 升汽油。当汽车到达加油站时，它可能停下来加油，将所有汽油从加油站转移到汽车中。
为了到达目的地，汽车所必要的最低加油次数是多少？如果无法到达目的地，则返回 -1 。
注意：如果汽车到达加油站时剩余燃料为 0，它仍然可以在那里加油。如果汽车到达目的地时剩余燃料为 0，仍然认为它已经到达目的地。
输入：target = 100, startFuel = 10, stations = [[10,60],[20,30],[30,30],[60,40]]
输出：2
解释：
出发时有 10 升燃料。
开车来到距起点 10 英里处的加油站，消耗 10 升燃料。将汽油从 0 升加到 60 升。
然后，从 10 英里处的加油站开到 60 英里处的加油站（消耗 50 升燃料），
并将汽油从 10 升加到 50 升。然后开车抵达目的地。
沿途在两个加油站停靠，所以返回 2 。
https://leetcode.cn/problems/minimum-number-of-refueling-stops/description/
 */
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
      int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
          priority_queue<int> q;      // 能够跑到的里程中的油量比较
          if (target <= startFuel) return 0;
          int n = stations.size();      // 有多少个加油站
          sort(stations.begin(), stations.end(), [](vector<int>& a, vector<int>& b)->bool{return a[0] < b[0];});    // 按照里程排序
          int ans = 0;
          for (int i = 0; i < n; i++)
          {
              if (stations[i][0] > startFuel)
              {
                  while (!q.empty() && startFuel < stations[i][0])
                  {
                      startFuel += q.top();
                      q.pop();
                      ans++;
                      if (startFuel >= target) return ans;
                  }
                  if (startFuel < stations[i][0]) return -1;
              }
              q.push(stations[i][1]);
          }
          // 此时遍历完了所有的加油站还未到达target，这个时候我们需要最后尝试一下
          while (!q.empty() && startFuel < target)
          {
              startFuel += q.top();
              q.pop();
              ans++;
          }
          return startFuel >= target ? ans : -1;
      }
};

int main()
{
    vector<vector<int>> stations = {{10,60},{20,30},{30,30},{60,40}};
    Solution s;
    cout << s.minRefuelStops(100, 10, stations) << endl;
    return 0;
}























