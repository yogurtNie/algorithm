//
// Created by 12472 on 25-9-1.
//
// 力扣1234 替换子串得到平衡字符串
/*
有一个只含有 'Q', 'W', 'E', 'R' 四种字符，且长度为 n 的字符串。假如在该字符串中，这四个字符都恰好出现 n/4 次，那么它就是一个「平衡字符串」。
给你一个这样的字符串 s，请通过「替换一个子串」的方式，使原字符串 s 变成一个「平衡字符串」。
你可以用和「待替换子串」长度相同的任何 其他字符串来完成替换。
请返回待替换子串的最小可能长度。
如果原字符串自身就是一个平衡字符串，则返回 0
1 <= s.length <= 10^5
s.length是4的倍数
s中只含有'Q', 'W', 'E','R'四种字符
*/
// https://leetcode.cn/problems/replace-the-substring-for-balanced-string/
// 可以完全转换为最小覆盖子串问题：四个字符各对应多少数量，多出的数量必定要被替换掉，所以问题变成 ——
// 包含多出数量字符的最小覆盖子串 —— 负债表模型
#include<bits/stdc++.h>
using namespace std;
// 7ms
class Solution {
public:
    int balancedString(string s) {
        char temp[4] = {'Q','W','E','R'};
        int n = s.length();
        vector<int> count(100, n/4);
        for (int i = 0; i < n; i++)
        {
            count[s[i]]--;
        }
        // 拿到欠债表，当前为负数的是多出的，为正数的是需要补充的
        int l = 0, r = 0, sum = 0, ans = INT_MAX;
        for (int i = 0; i < 4; i++)
            if (count[temp[i]] < 0) sum += -count[temp[i]];
        if (sum == 0) return 0;
        for (; r < n; r++)
        {
            if (count[s[r]]++ < 0) sum--;   // 扩展右边界
            if (sum == 0)                   // 如果已经还完负债，则开始压缩左边界
            {
                while (count[s[l]] - 1 >= 0)
                    count[s[l++]]--;
                ans = min(ans, r - l + 1);
            }
        }
        return ans;
    }
};

int main()
{
    string s = "QQQQ";
    Solution sol;
    cout << sol.balancedString(s);
    return 0;
}