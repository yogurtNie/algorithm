//
// Created by 12472 on 25-9-2.
//
/*
* n 对情侣坐在连续排列的 2n 个座位上，想要牵到对方的手。
人和座位由一个整数数组 row 表示，其中 row[i] 是坐在第 i 个座位上的人的 ID。情侣们按顺序编号，第一对是(0, 1)，第二对是(2, 3)，以此类推，最后一对是 (2n-2, 2n-1)。
返回 最少交换座位的次数，以便每对情侣可以并肩坐在一起。 每次交换可选择任意两人，让他们站起来交换座位。
2n == row.length
2 <= n <= 30
n 是偶数
0 <= row[i] < 2n
row 中所有元素均无重复
*/
// https://leetcode.cn/problems/couples-holding-hands/description/
// 需要观察法
// 第一个结论：如果有k对情侣在同一集合，则必定交换k-1次
// 第二个衔接：如何将并查集和情侣换位结合在一起 —— 当两两检查情侣是否匹配的时候，如果不匹配，则需要进行一次交换（合并），如果情侣中的另一人的不匹配对象是一个新的情侣组号，则同样要加入这个合并集合
// 在这个基础之上，我们可以进一步推导
// 假设最终由m个需要合并的集合，每个集合内部分别为 a_1,a_2,...,a_m对情侣，对应的合并次数（交换次数）为 a_1 - 1, a_2 - 1, ..., a_m - 1
// 加在一起： a_1 + a_2 + ... + a_m - m
// 即 总情侣对数 - m 就是答案
#include <bits/stdc++.h>
using namespace std;
const int N = 40;
class Solution {
public:
    int parent[N];
    void init(int n)
    {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    int find(int x)
    {
        return x == parent[x] ? x : parent[x] = find(parent[x]);
    }
    void unite(int x, int y)
    {
        int pa = find(x), pb = find(y);
        if (pa != pb)
        {
            parent[pa] = pb;
        }
    }
    bool IsSameSet(int x, int y)
    {
        return find(x) == find(y);
    }
    int minSwapsCouples(vector<int>& row) {
        int n = row.size() / 2;
        init(n + 1);
        for (int i = 0; i < n * 2; i+=2)
        {
            int left = row[i] / 2, right = row[i + 1] / 2;
            if (!IsSameSet(left, right))
                unite(left, right);
        }
        int count = 0;
        for (int i = 0; i < n; i++)
            if (parent[i] == i) count++;
        return n - count;
    }
};

int main()
{
    vector<int> row = {3, 2, 0, 1};
    Solution s;
    cout << s.minSwapsCouples(row) << endl;
    return 0;
}