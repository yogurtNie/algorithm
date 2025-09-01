//
// Created by 12472 on 25-9-1.
//
// 力扣134 加油站
/*
在一条环路上有 n 个加油站，其中第 i 个加油站有汽油 gas[i] 升。
你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。
给定两个整数数组 gas 和 cost ，如果你可以按顺序绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1 。如果存在解，则保证它是唯一的。
n == gas.length == cost.length
1 <= n <= 105
0 <= gas[i], cost[i] <= 104
https://leetcode.cn/problems/gas-station/
*/
// 第一个疑问是：窗口应该怎样滑动，才能决策出谁是起点？
// 起点的决定取决于是否能够按时到达终点，所以会自然而然想到要走一遍才能知道这是不是起点
// 但是这样就必定会让复杂度变成n^2
// 于是可以想到一个技巧 —— 化圈为线，将 n^2 的复杂度下降到 2n-1 的复杂度，然后固定窗口长度，当窗口内部的值为大于等于0时，返回起点
// 第二个疑问是：滑动过程中，如何在O(1)的时间内判断这条路径是否可行？
// 因为在滑动过程中，为了尽可能地缩小时间复杂度，必须要利用上之前的判断结果，不能重复计算，但是之前的判断结果是基于特定起点的，所以需要一层转换
// 于是我们需要做筛选 —— 当窗口内部的累加和已经小于0时，可以做出判断：在[l, r]中间的所有点都不可能是答案，于是从r+1开始判断，直到l到达n
#include<bits/stdc++.h>
using namespace std;
// 7ms 慢
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        int l = 0, r = 0, sum = 0;
        vector<int> sub(2 * n);
        // 得到一个差值数组：可优化掉
        for (int i = 0; i < n; i++)
        {
            sub[i] = sub[i + n] = gas[i] - cost[i];
        }
        for (; r < 2 * n; r++)
        {
            sum += sub[r];
            if (sum < 0)
            {
                l = r + 1;
                sum = 0;
            }
            else
            {
                if (r - l + 1 == n) return l;
            }
        }
        return -1;  // 若到达圈尾还未触发条件，则说明无对应答案
    }
};
// 3ms
class Solution2 {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        int l = 0, r = 0, sum = 0;
        // 优化掉差值数组
        for (; r < 2 * n; r++)
        {
            sum += gas[r % n] - cost[r % n];
            if (sum < 0)
            {
                l = r + 1;
                sum = 0;
            }
            else
            {
                if (r - l + 1 == n) return l;
            }
        }
        return -1;  // 若到达圈尾还未触发条件，则说明无对应答案
    }
};
// 7ms
class Solution3 {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        int l = 0, r = 0, sum = 0;
        // 优化循环
        for (; l < n; l = r + 1, r = l)
        {
            sum = 0;
            while (sum + gas[r % n] - cost[r % n] >= 0)  // 当累加和有余量的时候
            {
                if (r - l + 1 == n) return l;  // 先看看有没有答案
                sum += gas[r % n] - cost[r % n];  // 没有则扩展窗口
                r++;
            }
        }
        return -1;  // 若到达圈尾还未触发条件，则说明无对应答案
    }
};
int main()
{
    vector<int> gas = {1,2,3,4,5};
    vector<int> cost = {3,4,5,1,2};
    Solution2 sol;
    cout << sol.canCompleteCircuit(gas, cost);
    return 0;
}
