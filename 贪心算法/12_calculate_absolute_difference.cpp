//
// Created by 12472 on 26-3-19.
//
/*
 * 给定一个非负的数组arr，计算任何两个数差值的绝对值
 * 如果得到的差值绝对值arr中没有，都要加入到arr中，但是只加入一份
 * 新的arr，继续计算两个数差值的绝对值
 * 一直到arr大小固定，返回arr最终的长度
 * 大厂笔试，无在线测评，使用对数器验证
 */
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    // 暴力解法
    int way1(vector<int>&nums){
        set<int> s;
        vector<int> v;
        for (auto i : nums)
        {
            s.insert(i);
            v.push_back(i);
        }
        while (!finish(v,s)){}
        return v.size();
    }
    // 暴力求解
    bool finish(vector<int>&nums,set<int>&s)
    {
        int len = nums.size();
        for (int i = 0; i < len; i++)
        {
            for (int j = i + 1; j < len; j++)
            {
                int newNum = abs(nums[j] - nums[i]);
                if (s.find(newNum) == s.end())
                {
                    nums.push_back(newNum);
                    s.insert(newNum);
                }
            }
        }
        return len == nums.size();
    }
    // 最优解，计算最大的gcd，并利用gcd得到要新增的数量
    // 这个大的gcd是指，所有的数相互之间的gcd的最大值
    int way2(vector<int>&nums)
    {
        int Max = 0;        // 数组中的最大值
        int Mgcd = 0;
        map<int, int> mp;   // 词频统计
        for (int i = 0; i < nums.size(); i++)
        {
            Max = max(Max, nums[i]);
            if (nums[i] != 0 && Mgcd == 0) Mgcd = nums[i];
            if (mp.find(Max) == mp.end()) mp[nums[i]] = 1;
            else mp[nums[i]] += 1;
        }
        if (Mgcd == 0) return nums.size();
        // 计算整个数组中的最大gcd，往前滚动式计算
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] != 0) Mgcd = __gcd(Mgcd, nums[i]);
        }
        int ans = Max / Mgcd;
        auto it = mp.begin();
        bool hasRepetiton = false;
        for (; it != mp.end(); it++)
        {
            if (it->first != 0) ans += it->second - 1;
            if (it->second > 1) hasRepetiton = true;
        }

        // 如果没有0，且有重复的数
        if (mp.find(0) == mp.end() && hasRepetiton) ans += 1;
        // 如果有0，则只加上0的数量就好
        else if (mp.find(0) != mp.end()) ans += mp[0];
        return ans;
    }
    void test()
    {
        int N = 10;         // 数组最长10个数
        int M = 31;         // 最大范围是0~30
        int testTime = 2000;
        cout << "测试开始\n";
        for (int i = 0; i < testTime; i++)
        {
            int n = rand() % N + 1;
            vector<int> nums;
            for (int j = 0; j < n; j++)
            {
                int m = rand() % M;
                nums.push_back(m);
            }
            int ans1 = way1(nums);
            int ans2 = way2(nums);
            if (ans1 != ans2)
            {
                cout << "测试出错\n";
                cout << "[";
                for (int k = 0; k < n; k++) cout << nums[k] << " ";
                cout << "]";
                cout << ans1 << " " << ans2 << endl;
            }
            if (i % 100 == 0) cout << "测试到第" << i << "组" << endl;
        }
        cout << "测试结束\n";
    }
};

int main()
{
    Solution s;
    s.test();
    // vector<int> nums = {8,1, 23, 5, 1};
    // cout << s.way2(nums);
    return 0;

}