//
// Created by 12472 on 26-3-29.
//
/*
* 在 x 轴上有一个一维的花园。花园长度为 n，从点 0 开始，到点 n 结束。
花园里总共有 n + 1 个水龙头，分别位于 [0, 1, ..., n] 。
给你一个整数 n 和一个长度为 n + 1 的整数数组 ranges ，其中 ranges[i] （下标从 0 开始）表示：如果打开点 i 处的水龙头，可以灌溉的区域为 [i -  ranges[i], i + ranges[i]] 。
请你返回可以灌溉整个花园的 最少水龙头数目 。如果花园始终存在无法灌溉到的地方，请你返回 -1 。
https://leetcode.cn/problems/minimum-number-of-taps-to-open-to-water-a-garden/
输入：n = 5, ranges = [3,4,1,1,0,0]
输出：1
解释：
点 0 处的水龙头可以灌溉区间 [-3,3]
点 1 处的水龙头可以灌溉区间 [-3,5]
点 2 处的水龙头可以灌溉区间 [1,3]
点 3 处的水龙头可以灌溉区间 [2,4]
点 4 处的水龙头可以灌溉区间 [4,4]
点 5 处的水龙头可以灌溉区间 [5,5]
只需要打开点 1 处的水龙头即可灌溉整个花园 [0,5]

我认为的贪心方法：如果某段区域只有一个水龙头能灌溉到，这个水龙头必定是要纳入的
如果某个区域有多个水龙头能覆盖，那肯定取最长的
—— 我发现我的短板是很不会定义数据结构
如何实现这个想法，用最省力的数据结构？ —— 一个right数组，下标代表的意思是，以当前为起点的线段，能延伸到最远的距离
还有一个相对暴力的实现，就是用一个vector pii来排序，切割，然后遍历pii得到一个最长的结果，则纳入
 *
 */
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<int> right(n, 0);
        for (int i = 0; i <= n; i++)
        {
            int l = max(0, i - ranges[i]), r = min(n, i + ranges[i]);
            right[l] = max(right[l],  r);
        }
        int cur = 0;
        int ans = 0;
        int next = 0;
        for (int i = 0; i < n; i++)
        {
            // if (cur < i)
            // {
            //     cur = next;
            //     ans++;
            // }
            next = max(next, right[i]);
            if (i == cur)
            {
                // 这里略有些不同，因为不是点来计数，而是按段来计数
                if (i < next) {cur = next; ans++;}
                // 所以当在本节点的时候，在从前能到达的最远距离没有超过i的，说明要中断了
                else return -1;
            }

        }
        return ans;
    }
};

int main()
{
    vector<int> ranges = {0,0,0,0,0,0};
    Solution sol;
    cout << sol.minTaps(5, ranges) << endl;
    return 0;
}