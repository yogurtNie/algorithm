//
// Created by 12472 on 26-3-20.
//
/*
* 你有 k 个 非递减排列 的整数列表。找到一个 最小 区间，使得 k 个列表中的每个列表至少有一个数包含在其中。
我们定义如果 b-a < d-c 或者在 b-a == d-c 时 a < c，则区间 [a,b] 比 [c,d] 小。
输入：nums = [[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
输出：[20,24]
解释：
列表 1：[4, 10, 15, 24, 26]，24 在区间 [20,24] 中。
列表 2：[0, 9, 12, 20]，20 在区间 [20,24] 中。
列表 3：[5, 18, 22, 30]，22 在区间 [20,24] 中。
https://leetcode.cn/problems/smallest-range-covering-elements-from-k-lists/description/
*/
#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int element, aindex, eindex;
    Node(int element = 0, int aindex = 0, int eindex = 0):element(element), aindex(aindex), eindex(eindex){}
};
struct MyCompare
{
    // 注意，这个比较器一定要加const
    bool operator()(const Node& n1, const Node& n2) const
    {
        if (n1.element == n2.element) return n1.aindex < n2.aindex;
        else if (n1.element == n2.element && n1.aindex == n2.aindex) return n1.eindex < n2.eindex;
        return n1.element < n2.element;
    }
};
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        set<Node, MyCompare> s;     // 有序表实现排序
        int k = nums.size();
        for (int i = 0; i < k; i++)
        {
            s.insert(Node(nums[i][0], i, 0));
        }
        int Min = INT_MAX;
        int left = INT_MIN, right = INT_MAX;
        while (s.size() == k)
        {
            Node start = *s.begin();
            Node end = *s.rbegin();
            s.erase(s.begin());
            if (Min > end.element - start.element)
            {
                Min = end.element - start.element;
                left = start.element;
                right = end.element;
            }
            if (start.eindex == nums[start.aindex].size() - 1) continue;
            s.insert(Node(nums[start.aindex][start.eindex + 1], start.aindex, start.eindex + 1));
        }
        return {left, right};
    }
};

int main()
{
    vector<vector<int>> nums = {{1,2,3},{1,2,3},{1,2,3}};
    Solution solution;
    vector<int> ans = solution.smallestRange(nums);
    for (auto num : ans) cout << num << " ";
    return 0;
}