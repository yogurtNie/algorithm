//
// Created by 12472 on 25-6-20.
//
/*
 * 给你一个字符串 s ，请你去除字符串中重复的字母，使得每个字母只出现一次。需保证 返回结果的字典序最小（要求不能打乱其他字符的相对位置）
 * https://leetcode.cn/problems/remove-duplicate-letters/description/
 * 讨论怎么删除就是讨论怎么保留
 * 栈里保存的东西：保留字符最小的字典序的可能性 （不改变相对次序）
 * 什么时候允许出栈？当答案可以更优，且不会错失某个字母的时候 —— 对字母计数，每入栈一次减少一次
 */
// 这题很有价值的点是在，单调栈不改变相对次序的特质，以及讨论最优和选取最优的可能性用法
// 需要分别探讨进栈的条件和出栈的条件
// 如果后面还有机会，就可以放心弹出
// 没有机会，就只好捏着鼻子忍下，不弹出
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> count(26, 0);       // 得到一次词频表，不错失答案
        vector<bool> used(26, 0);
        for (char c : s)
            count[c - 'a']++;
        int n = s.size();
        vector<int> st(n, 0);
        int top = 0;
        for (int i = 0; i < n; i++)
        {
            // 不满足大压小
            if (used[s[i] - 'a'])
            {
                // 跳过的时候也要记得减少词频
                count[s[i] - 'a']--;
                continue;
            }
            while (top > 0 && count[s[st[top - 1]]-'a'] > 0 && s[i] <= s[st[top - 1]])
            {
                used[s[st[top - 1]] - 'a'] = 0;
                top--;
            }
            st[top++] = i;
            count[s[i] - 'a']--;        // 减少词频
            used[s[i] - 'a'] = true;
        }
        string ans;
        for (int i = 0; i < top; i++)
        {
            ans += s[st[i]];
        }
        return ans;
    }
};

int main()
{
    string s = "bbcaac";
    Solution sol;
    cout << sol.removeDuplicateLetters(s) << endl;;
    return 0;
}