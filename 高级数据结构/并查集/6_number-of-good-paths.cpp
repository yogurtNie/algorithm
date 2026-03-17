//
// Created by 12472 on 25-9-4.
//
// 力扣2421 好路径的数量
/*
 * 给你一棵 n 个节点的树（连通无向无环的图），节点编号从 0 到 n - 1 且恰好有 n - 1 条边
 * 给你一个长度为 n 下标从 0 开始的整数数组 vals ，分别表示每个节点的值。同时给你一个二维整数数组 edges ，其中 edges[i] = [ai, bi] 表示节点 ai 和 bi 之间有一条 无向 边。
* 一条 好路径 需要满足以下条件：
开始节点和结束节点的值 相同 。
开始节点和结束节点中间的所有节点值都 小于等于 开始节点的值（也就是说开始节点的值应该是路径上所有节点的最大值
* 请你返回不同好路径的数目。
注意，一条路径和它反向的路径算作 同一路径。比方说，0 -> 1与1 -> 0视为同一条路径。单个节点也视为一条合法路径。
n == vals.length
1 <= n <= 3 * 104
0 <= vals[i] <= 105
edges.length == n - 1
edges[i].length == 2
0 <= ai, bi < n
ai != bi
edges 表示一棵合法的树。
*/
// https://leetcode.cn/problems/number-of-good-paths/description/
// 有几个问题需要解决：
// 1. 怎样将edge表示的树建模表示出来
// 2. 怎样将好路径的数目和并查集的合并联系起来 —— 大概率是：节点总个数 - 节点合并次数（不对）
// 这两步分别用：处理顺序 和 打标记 来解决
// 此题共分为三步：
/*
 * 1. 将边按两侧端点最大值排序，从小到大处理，因为最终的好路径要求中间必须小于两边
 * 2. 初始化每个点集的集合，共打两个标记，第一个标记是集合的最大值，第二个标记是集合最大值的个数
 * 3. 按照边的顺序开始合并点集，规则为：
 *     若点集的max值不相等，则无答案产生，合并为同一个集合，num更新为max值更大的数量；
 *     若点集的max值相等，答案累加 num1 * num2，合并为同一个集合，num更新为num1 + num2
 */
#include <bits/stdc++.h>
using namespace std;
const int N = 3e4 + 10;
// 78ms
class Solution {
public:
    int parent[N];      // 并查集
    int Max[N];         // 记录集合最大值
    int size[N];        // 记录集合最大值的个数
    int ans;
    void init(int n, vector<int>& vals)
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            Max[i] = vals[i];
            size[i] = 1;
        }
        ans = 0;
    }
    int find(int x)
    {
        return x == parent[x] ? x : parent[x] = find(parent[x]);
    }
    bool IsSameSet(int a, int b)
    {
        return find(a) == find(b);
    }
    void unite(int a, int b)
    {
        int pa = find(a), pb = find(b);
        if (pa != pb)
        {
            if (Max[pa] == Max[pb])
            {
                ans += size[pa] * size[pb];     // 记录答案
                parent[pb] = pa;                // b挂靠在a下
                size[pa] += size[pb];           // 更新pa集合
            }
            else if (Max[pa] > Max[pb])
            {
                parent[pb] = pa;                // 小挂大
            }
            else
            {
                parent[pa] = pb;                // 同理
            }
        }
    }
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size(), m = edges.size();
        init(n, vals);
        // lambda表达式，按照v1 v2的最大权值来排序处理
        // 题眼在此
        sort(edges.begin(), edges.end(),
            [&vals](vector<int>& v1, vector<int>& v2) -> bool
            {
                int p1 = max(vals[v1[0]], vals[v1[1]]);
                int p2 = max(vals[v2[0]], vals[v2[1]]);
                return p1 < p2;
            });
        for (int i = 0; i < m; i++)
        {
            int a = edges[i][0], b = edges[i][1];
            if (!IsSameSet(a, b))
                unite(a, b);
        }
        return ans + n;
    }
};

int main()
{
    vector<int> vals = {1,1,2,2,3};
    vector<vector<int>> edges = {{0,1},{1,2},{2,3},{2,4}};
    Solution sol;
    cout << sol.numberOfGoodPaths(vals, edges) << endl;
    return 0;
}