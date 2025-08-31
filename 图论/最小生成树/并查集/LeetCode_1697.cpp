//
// Created by 12472 on 25-6-12.
//
// 有m个查询，要求查[a, b, power] a -> b这条路上是否存在一条路严格小于power
// 做法：将边集和查询集都排好序，然后按照边集向前遍历，不断合并，直到遇到第n个边界的上限
// 检查该次合并之后两点是否联通，如果联通，则说明存在
// 问题转换 --> 将是否存在一条限制路径的长度转换为了合并符合边长规范的边之后，两点是否联通
#include <bits/stdc++.h>
using namespace std;
struct question
{
    int from, to, len, id;
    question(int from, int to, int len, int id) : from(from), to(to), len(len), id(id) {}
};
bool cmp(const question& a,const question& b)
{
    return a.len < b.len;
}
bool cmp2(const vector<int>& a,const vector<int>& b)
{
    return a[2] < b[2];
}
class Solution {
public:
    int parent[100005];
    int find(int x)
    {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    void Union(int x, int y)
    {
        int A = find(x), B = find(y);
        if (A != B) parent[A] = B;
    }
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        vector<bool> answer(n - 1, false);
        int m = queries.size();
        int num = edgeList.size();
        vector<question> q;
        for (int i = 0; i < m; i++)
        {
            q.push_back(question(queries[i][0], queries[i][1], queries[i][2], i));
        }
        // 初始化问题
        sort(q.begin(), q.end(), cmp);
        // 为边集合排序
        sort(edgeList.begin(), edgeList.end(), cmp2);

        // 初始化并查集
        for (int i = 0; i <= n; i++) parent[i] = i;

        // 开始累加和合并
        int i, j = 0;
        int x = 0, y = 0;
        // i是问题编号，j是边的编号
        for (i = 0, j = 0; i < m; i++)
        {
            while (j < num && edgeList[j][2] < q[i].len)
            {
                x = edgeList[j][0], y = edgeList[j][1];
                Union(x, y);
                j++;
            }
            if (find(q[i].from) != find(q[i].to)) answer[q[i].id] = false;
            else answer[q[i].id] = true;
        }
        return answer;
    }
};

int main()
{
    int n = 5;
    vector<vector<int>> edgeList = {{0,1,10}, {1,2,5}, {2,3,9}, {3,4,13}};
    vector<vector<int>> queries = {{0,4,14},{1,4,13}};
    Solution sol;
    vector<bool> ans = sol.distanceLimitedPathsExist(n, edgeList, queries);
    for (auto x : ans) cout << x << " ";

}