//
// Created by 12472 on 25-8-31.
//
// 力扣 第3题 无重复字符的最长子串
// 给定一个字符串s，找出其中不含有重复字符的最长子串的长度
// https://leetcode.cn/problems/longest-substring-without-repeating-characters/
// 该题的易错点：s由英文字母、数字、符号和空格组成 —— char类型的ascii码范围从0~255，所以开的计数空间要大一些
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> count(255, 0);
        int l = 0, r = 0, ans = 0;
        for (; r < s.size(); r++)
        {
            ans = max(ans, r - l + 1);
            count[s[r]]++;
            if (r == s.size() - 1) break;
            while (l <= r && count[s[r + 1]] == 1) // 如果即将纳入的字母已经存在于窗口内
            {
                count[s[l++]] = 0;  // 窗口前移，并更新标记  由于此时的答案必然只会更小，所以可以不必更新答案
            }
        }
        return ans;
    }
};

int main()
{
    string s = " ";
    Solution sol;
    cout << sol.lengthOfLongestSubstring(s);
    return 0;
}