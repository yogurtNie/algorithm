//
// Created by 12472 on 26-3-24.
//
/*
* 森林中有未知数量的兔子。提问其中若干只兔子 "还有多少只其它兔子与你（指被提问的兔子）颜色相同?" ，将答案收集到一个整数数组 answers 中，其中 answers[i] 是第 i 只兔子的回答。
给你数组 answers ，返回森林中兔子的最少数量。
输入：answers = [1,1,2]
输出：5
解释：
两只回答了 "1" 的兔子可能有相同的颜色，设为红色。
之后回答了 "2" 的兔子不会是红色，否则他们的回答会相互矛盾。
设回答了 "2" 的兔子为蓝色。
此外，森林中还应有另外 2 只蓝色兔子的回答没有包含在数组中。
因此森林中兔子的最少数量是 5 只：3 只回答的和 2 只没有回答的
https://leetcode.cn/problems/rabbits-in-forest/
 */
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int numRabbits(vector<int>& answers) {
        unordered_map<int, int> mp;
        for (int i = 0; i < answers.size(); i++)
        {
            if (mp.find(answers[i]) == mp.end()) mp[answers[i]] = 1;
            else mp[answers[i]] += 1;
        }
        int ans = 0;
        for (auto& it : mp)
        {
            // 如果刚好够覆盖，那么就当做这些集合内部是一群兔子
            if (it.first + 1 >= it.second) ans += it.first + 1;
            else
            {
                int num = it.second;            // 有这么多兔子报了这个数
                int cnt =  num / (it.first + 1);    // 可以分成这么多组
                if (num % (it.first + 1)) cnt++;
                ans += cnt * (it.first + 1);
            }
        }
        return ans;
    }
};

int main()
{
    vector<int> v = {10,10,10};
    Solution sol;
    cout << sol.numRabbits(v) << endl;
    return 0;
}