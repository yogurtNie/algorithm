//
// Created by 12472 on 25-9-3.
//
// 力扣947 移除最多的同行或同列石头
/*
* n 块石头放置在二维平面中的一些整数坐标点上。每个坐标点上最多只能有一块石头。
如果一块石头的 同行或者同列 上有其他石头存在，那么就可以移除这块石头。
给你一个长度为 n 的数组 stones ，其中 stones[i] = [xi, yi] 表示第 i 块石头的位置，返回 可以移除的石子 的最大数量。
1 <= stones.length <= 1000
0 <= xi, yi <= 104
不会有两块石头放在同一个坐标点上
*/
// https://leetcode.cn/problems/most-stones-removed-with-same-row-or-column/description/
// 可以有这样一个小结论：能够纳入同一个并查集的石头集合，最后一定可以通过消除只剩下一块石头
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
// 94ms
class Solution {
public:
    int parent[N];
    int set;
    void init(int n)
    {
        set = n;
        for(int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }
    int find(int x)
    {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool IsSameSet(int a, int b)
    {
        return find(a) == find(b);
    }
    void unite(int x, int y)
    {
        int pa = find(x), pb = find(y);
        if (pa != pb)
        {
            parent[pa] = pb;
            set--;
        }
    }
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        init(n);
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (!IsSameSet(i, j))
                {
                    if (stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1])
                        unite(i, j);
                }
            }
        }
        return n - set;
    }
};

int main()
{
    vector<vector<int>> stones = {{0,0},{0,1},{1,0},{1,2},{2,1},{2,2}};
    Solution sol;
    cout << sol.removeStones(stones) << endl;
    return 0;
}