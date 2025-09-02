//
// Created by 12472 on 25-9-2.
//
/*
* 如果交换字符串 X 中的两个不同位置的字母，使得它和字符串 Y 相等，那么称 X 和 Y 两个字符串相似。如果这两个字符串本身是相等的，那它们也是相似的。
例如，"tars" 和 "rats" 是相似的 (交换 0 与 2 的位置)；"rats" 和 "arts" 也是相似的，但是 "star" 不与 "tars"，"rats"，或 "arts" 相似。
总之，它们通过相似性形成了两个关联组：{"tars", "rats", "arts"} 和 {"star"}。注意，"tars" 和 "arts" 是在同一组中，即使它们并不相似。形式上，对每个组而言，要确定一个单词在组中，只需要这个词和该组中至少一个单词相似。
给你一个字符串列表 strs。列表中的每个字符串都是 strs 中其它所有字符串的一个字母异位词。请问 strs 中有多少个相似字符串组？
1 <= strs.length <= 300
1 <= strs[i].length <= 300
strs[i] 只包含小写字母。
strs 中的所有单词都具有相同的长度，且是彼此的字母异位词。
*/
// https://leetcode.cn/problems/similar-string-groups/description/

#include <bits/stdc++.h>
using namespace std;
const int N = 310;
class Solution {
public:
    int set;
    int parent[N];
    void init(int n)
    {
        set = n;
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    int find(int x)
    {
        return (parent[x] == x) ? x : parent[x] = find(parent[x]);
    }
    bool IsCombine(int a, int b)
    {
        return find(a) == find(b);
    }
    void Union(int a, int b)
    {
        int pa = find(a), pb = find(b);
        if (pa != pb)
        {
            parent[pa] = pb;
            set--;      // 合并一次，集合数量-1
        }
    }
    int numSimilarGroups(vector<string>& strs) {
        int n = strs.size();
        int m = strs[0].size();
        init(n);
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (!IsCombine(i, j))
                {
                    int count = 0;
                    for (int k = 0; k < m; k++)
                    {
                        if (strs[i][k] != strs[j][k])
                            count++;
                    }
                    if (count == 2 || count == 0)
                        Union(i, j);
                }
            }
        }
        return set;
    }
};

int main()
{
    vector<string> strs = {"omv","ovm"};
    Solution s;
    cout << s.numSimilarGroups(strs) << endl;
    return 0;
}