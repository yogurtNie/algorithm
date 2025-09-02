//
// Created by 12472 on 25-8-31.
//
// 力扣3 无重复字符的最长子串
// 给定一个字符串s，找出其中不含有重复字符的最长子串的长度
// https://leetcode.cn/problems/longest-substring-without-repeating-characters/
// 该题的易错点：s由英文字母、数字、符号和空格组成 —— char类型的ascii码范围从0~255，所以开的计数空间要大一些
#include<bits/stdc++.h>
using namespace std;
class Solution1 {
public:
    int lengthOfLongestSubstring(string s) {
        vector<bool> count(255, 0);
        int l = 0, r = 0, ans = 0;
        for (; r < s.size(); r++)
        {
            ans = max(ans, r - l + 1);
            count[s[r]] = 1;
            if (r == s.size() - 1) break;
            while (l <= r && count[s[r + 1]] == 1) // 如果即将纳入的字母已经存在于窗口内
            {
                count[s[l++]] = 0;  // 窗口前移，并更新标记  由于此时的答案必然只会更小，所以可以不必更新答案
            }
        }
        return ans;
    }
};
class Solution2
{
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> last(255, -1);  // 初始化为-1，该数组记录此时r指向字符上次出现的位置
        int l = 0, r = 0, ans = 0;
        for (; r < s.size(); r++)
        {
            l = max(l, last[s[r]] + 1);  // 当前的左边界，要么是原本的边界，要么是缩小到当前r所指字符上次出现位置的右边一位
            ans = max(ans, r - l + 1);   // 更新答案
            last[s[r]] = r;                   // 更新字符上次出现位置

        }
        return ans;
    }
};
int main()
{
    string s = " ";
    Solution2 sol;
    cout << sol.lengthOfLongestSubstring(s);
    return 0;
}