//
// Created by 12472 on 25-9-1.
//
// 力扣76题 最小覆盖子串
// 给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。
// m == s.length
// n == t.length
// 1 <= m, n <= 105
// https://leetcode.cn/problems/minimum-window-substring/
// 负债表思路：将需要的 t 字母组成作为一个负债表，其余字符的负债值为0，t中字母的负债值为对应数量
// 当总负债已经为0时，r找到最大边界，可以开始压缩l并更新答案
// 在压缩左边界的时候，是允许压缩到边界值以下的，因为在压缩前会记录答案，所以不会干扰正确答案
// 只是，思路一的答案记录发生在两个地方，第一个地方，是r向前拓展的时候，第二个地方，是l向前压缩的时候，都有可能产生最终的答案
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    string minWindow(string s, string t) {
        if (t.length() > s.length()) return "";  // 处理边界情况
        vector<int> Count(150, 0);
        int sum = 0;
        for (int i = 0; i < t.length(); i++)
        {
            Count[t[i]]--;   // 负债
            sum--;
        }
        // 拿到负债表，开始窗口滑动
        int left = 0, r = 0, ans = INT_MAX;
        int boundary = 0;
        for (; r < s.length(); r++)
        {
            if (Count[s[r]]++ < 0) sum++;  // 如果有负债，则抵消总负债
            if (sum >= 0)  // 如果已经负债为正，说明可以开始压缩左边界
            {
                if (ans > r - left + 1)
                {
                    ans = r - left + 1;
                    boundary = left;
                }
                while (left < r)
                {
                    if (Count[s[left++]]-- <= 0) sum--;  // 如果左边界是决定是否满足要求的字母，则再次负债
                    if (sum >= 0)
                    {
                        if (ans > r - left + 1)
                        {
                            ans = r - left + 1;
                            boundary = left;
                        }
                    }
                    else break;
                }
            }
        }
        return ans == INT_MAX ? "" : s.substr(boundary, ans);

    }
};

class Solution2
{
public:
    string minWindow(string s, string t)
    {
        if (t.length() > s.length()) return "";  // 处理边界情况
        vector<int> Count(150, 0);
        int sum = t.length();  // 总债务记成正的
        for (int i = 0; i < t.length(); i++)
        {
            Count[t[i]]--;   // 负债
        }
        // 拿到负债表，开始窗口滑动
        int left = 0, r = 0, ans = INT_MAX;
        int boundary = 0;
        for (; r < s.length(); r++)
        {
            // 窗口先向右拓展
            if (Count[s[r]]++ < 0) sum--;
            if (sum == 0)
            {
                while (Count[s[left]] > 0)
                {
                    Count[s[left++]]--;   // 压缩窗口
                }
                if (ans > r - left + 1)
                {
                    ans = r - left + 1;
                    boundary = left;
                }
            }
        }
        return ans == INT_MAX ? "" : s.substr(boundary, ans);
    }
};
int main()
{
    string s = "cabwefgewcwaefgcf", t = "cae";
    Solution2 sol;
    cout << sol.minWindow(s, t);
    return 0;
}

