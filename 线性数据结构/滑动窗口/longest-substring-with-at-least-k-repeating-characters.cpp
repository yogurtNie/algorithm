//
// Created by 12472 on 25-9-1.
//
// 力扣395 至少有k个重复字符的最长子串
/* 给你一个字符串 s 和一个整数 k ，请你找出 s 中的最长子串，要求该子串中的每一字符出现次数都不少于 k 。返回这一子串的长度。
如果不存在这样的子字符串，则返回 0。
 */
// https://leetcode.cn/problems/longest-substring-with-at-least-k-repeating-characters/description/
// 找最长子串，每种字符的数量大于等于 k
// 1 <= s.length <= 104
// s 仅由小写英文字母组成
// 1 <= k <= 105
// 疑问：当不限定字符种类时，统计会变得很难
/*
 * 解决办法：限定字符种类，依次统计当严格限定有 m 种字符且 >= k 时的种类数
 * 最多尝试26次，因为s仅有小写英文字母
 */
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int Count(string s, int m, int k)  // 在 s 中找到有 m 种字符作为子串且每个字符数量都 >= k 的子串长度最大值
    {
        vector<int> counts(150, 0);   // 出现字数统计表
        int left = 0, r = 0, kind = 0, ans = 0;
        for (; r < s.size(); r++)
        {
            if (++counts[s[r]] == k) kind++;  // 这样写的问题在于：如果出现 aba 这种情况，kind依旧会达到1，但是这个时候是有字母不满足要求的
            if (kind == m)      // 开始压缩左边界
            {
                ans = max(ans, r - left + 1);
                while (counts[s[left]] >= k)
                {
                    counts[s[left++]]--;
                    if (counts[left - 1] < k)
                    {
                        kind--; break;
                    }
                    ans = max(ans, r - left + 1);
                }
            }
        }
        return ans;
    }
    int longestSubstring(string s, int k) {
        int n = s.size();
        int ans = 0;
        for (int i = 1; i <= n; i++)
            ans = max(ans, Count(s, i, k));
        return ans;
    }
};
// 303ms
class Solution2 {
public:
    int Count(string s, int m, int k)  // 在 s 中找到有 m 种字符作为子串且每个字符数量都 >= k 的子串长度最大值
    {
        vector<int> counts(150, 0);   // 出现字数统计表
        int left = 0, r = 0, kind = 0, satisfy = 0, ans = 0;
        for (; r < s.size(); r++) // 右边界何时可以扩充：当kind满足m的时候 -> 右边界扩充的时候，必定满足kind == m
        {
            counts[s[r]]++;   // 增加计数
            if (counts[s[r]] == k) satisfy++;   // 当数量达标时，满足数量+1
            if (counts[s[r]] == 1) kind++;      // 当有新增种类时，统计种类+1
            // 当种类数量大于满足的数量，则需要压缩左边界，降低种类
            while (kind > m)
            {
                if (counts[s[left]] == k) satisfy--;
                if (counts[s[left]] == 1) kind--;
                counts[s[left++]]--;
            }
            // 当 kind 比 satisfy 小，或者kind == satisfy但是比m小，都需要拓展右边界，即continue
            // 当满足收集条件的时候，开始收集答案
            if (kind == m && kind == satisfy)
            {
                ans = max(ans, r - left + 1);
            }
        }
        return ans;
    }
    int longestSubstring(string s, int k) {
        int n = s.size();
        int ans = 0;
        for (int i = 1; i <= n; i++)
            ans = max(ans, Count(s, i, k));
        return ans;
    }
};
// 271ms
class Solution3 {
public:
    int Count(string s, int m, int k)  // 在 s 中找到有 m 种字符作为子串且每个字符数量都 >= k 的子串长度最大值
    {
        vector<int> counts(150, 0);   // 出现字数统计表
        int left = 0, r = 0, kind = 0, satisfy = 0, ans = 0;
        for (; r < s.size(); r++) // 右边界何时可以扩充：当kind满足m的时候 -> 右边界扩充的时候，必定满足kind == m
        {
            counts[s[r]]++;   // 增加计数
            if (counts[s[r]] == k) satisfy++;   // 当数量达标时，满足数量+1
            if (counts[s[r]] == 1) kind++;      // 当有新增种类时，统计种类+1
            // 当种类数量大于满足的数量，则需要压缩左边界，降低种类
            while (kind > m)
            {
                if (counts[s[left]] == k) satisfy--;
                if (counts[s[left]] == 1) kind--;
                counts[s[left++]]--;
            }
            // 当 kind 比 satisfy 小，或者kind == satisfy但是比m小，都需要拓展右边界，即continue
            // 当满足收集条件的时候，开始收集答案
            if (kind == m && kind == satisfy)
            {
                ans = max(ans, r - left + 1);
            }
        }
        return ans;
    }
    int longestSubstring(string s, int k) {
        int n = s.size();
        int Ans = 0;
        for (int i = 1; i <= n; i++)
        {
            vector<int> count(150, 0);   // 出现字数统计表
            int left = 0, r = 0, kind = 0, satisfy = 0, ans = 0;
            for (; r < s.size(); r++) // 右边界何时可以扩充：当kind满足m的时候 -> 右边界扩充的时候，必定满足kind == m
            {
                count[s[r]]++;   // 增加计数
                if (count[s[r]] == k) satisfy++;   // 当数量达标时，满足数量+1
                if (count[s[r]] == 1) kind++;      // 当有新增种类时，统计种类+1
                // 当种类数量大于满足的数量，则需要压缩左边界，降低种类
                while (kind > i)
                {
                    if (count[s[left]] == k) satisfy--;
                    if (count[s[left]] == 1) kind--;
                    count[s[left++]]--;
                }
                // 当 kind 比 satisfy 小，或者kind == satisfy但是比m小，都需要拓展右边界，即continue
                // 当满足收集条件的时候，开始收集答案
                if (kind == i && kind == satisfy)
                {
                    ans = max(ans, r - left + 1);
                }
            }
            Ans = max(Ans, ans);
        }
        return Ans;
    }
};
int main()
{
    string s = "aaabb";
    Solution2 sol;
    cout << sol.longestSubstring(s, 3) << endl;
    return 0;
}