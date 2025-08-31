//
// Created by 12472 on 25-8-31.
//
// 力扣209 长度最小的子数组
// 给定一个含有 n 个正整数的数组和一个正整数 target 。
// 找出该数组中满足其总和大于等于 target 的长度最小的子数组 [nums_l, nums_l+1, ..., nums_r-1, nums_r] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。
// https://leetcode.cn/problems/minimum-size-subarray-sum/
#include<bits/stdc++.h>
using namespace std;
// 思路1：边界在极限值以下（极限值左边）
// 需要匹配的操作：计算ans值在所有循环出窗口的最前面
class Solution1 {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int l = 0, r = 0, sum = 0;
        int ans = INT_MAX;
        for (; r < nums.size(); r++)
        {
            sum += nums[r];
            if (sum >= target)  // 即使目前的[l, r]长度比ans大也让进，因为在while循环内部会减小sum和ans
            {
                ans = min(ans, r - l + 1);
                while (l < r)  // 即使sum已经减少到比target小了也得让进，因为要先尝试最大限度地压缩sum的值
                {
                    sum -= nums[l++];
                    if (sum >= target) ans = min(ans, r - l + 1);
                    else break;
                }
            }
        }
        return ans == INT_MAX ? 0 : ans;
    }
};

// 思路2：边界在target值以上（右边）
class Solution2 {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int l = 0, r = 0, sum = 0;
        int ans = INT_MAX;
        for (; r < nums.size(); r++)
        {
            sum += nums[r];
            while (sum - nums[l] >= target)  // 边界值是不许低于target的,但是由于循环的特性，最后一次减的时候，可能会额外多减一次，减到临界值以下
            {
                sum -= nums[l++];
            }
            if (target <= sum) ans = min(ans, r - l + 1);
        }
        return ans == INT_MAX ? 0 : ans;
    }
};

int main()
{
    int target = 4;
    vector<int> nums = {1,4,4};
    Solution2 sol;
    cout << sol.minSubArrayLen(target, nums);
    return 0;
}