//
// Created by 12472 on 26-3-10.
//
/*
* 给定一组非负整数 nums，重新排列每个数的顺序（每个数不可拆分）使之组成一个最大的整数。
注意：输出结果可能非常大，所以你需要返回一个字符串而不是整数。
https://leetcode.cn/problems/largest-number/description/
示例 1：
输入：nums = [10,2]
输出："210"

示例 2：
输入：nums = [3,30,34,5,9]
输出："9534330"
*/
#include<bits/stdc++.h>
using namespace std;
bool cmp(string& a, string& b)
{
    return a + b < b + a;
}
class Solution {
public:
    // 先用最暴力的算法得到最终结果
    string way1(vector<string>& strs)
    {
        vector<string> ans;
        // 暴力全排列得到所有的结果
        f(strs, 0, ans);
        sort(ans.begin(), ans.end());
        return ans[0];
    }
    void f(vector<string>& strs, int pos, vector<string>& ans)
    {
        if (pos == strs.size())
        {
            string now_s;
            for (auto&s : strs)
                now_s += s;
            ans.push_back(now_s);
        }
        else
        {
            for (int i = pos; i < strs.size(); i++)
            {
                swap(strs[pos], strs[i]);
                f(strs, pos + 1, ans);
                swap(strs[pos], strs[i]);
            }
        }
    }
    // 贪心策略，比较a+b和b+a谁更大
    string way2(vector<string>& strs)
    {
        sort(strs.begin(), strs.end(), cmp);
        string ans;
        for (int i = strs.size() - 1; i >= 0; i--) ans += strs[i];
        int first = -1;
        for (int i = 0; i < ans.size(); i++)
        {
            if (ans[i] != '0') break;
            first = i;
        }
        if (first != -1) ans.erase(ans.begin(), ans.begin() + first + 1);
        return ans == "" ? "0" : ans;
    }
    // 随机验证器，随机生成长度1~n的随机字符串数组
    // n为字符数组的长度，m为每个字符的可能的宽度，v为出现的字符种类数量
    vector<string> verdification(int n, int m ,int v)
    {
        srand(time(NULL));
        vector<string> res;
        int arraySize = rand() % n + 1;  // 在1~n范围内取随机数
        for (int i = 0; i < arraySize; i++)
        {
            string s;
            int strlen = rand() % m + 1;    // 长度在1~m间
            for (int j = 0; j < strlen; j++)
            {
                s += (char)('a' + rand() % v);
            }
            res.push_back(s);
        }
        return res;
    }
    void vedify()
    {
        int n = 8, m = 5, v = 4;
        int testTimes = 2000;
        cout << "测试开始" << endl;
        for (int i = 0; i < testTimes; i++)
        {
            vector<string> strs = verdification(n, m, v);
            string ans1 = way1(strs);
            string ans2 = way2(strs);
            if (ans1 != ans2)
            {
                cout << "ERROR! The wrong sample is as follows.\n";
                for (string s : strs) cout << s << " ";
                cout << endl;
            }
            if (i % 100 == 0)
            {
                cout << "测试到第" << i + 1 << "组\n";
            }
        }
        cout << "测试结束\n";
    }
    string largestNumber(vector<int>& nums) {
        vector<string> res;
        for (int i : nums)
            res.push_back(to_string(i));
        string ans = way2(res);
        return ans;
    }
};

int main()
{
    Solution sol;
    sol.vedify();
    return 0;
}

