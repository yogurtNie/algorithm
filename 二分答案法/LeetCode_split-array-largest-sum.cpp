//
// Created by 12472 on 25-12-7.
//
// 画匠问题
// 进行k次划分，怎样让每一份的累加和的最大值最小
/*
* 给定一个非负整数数组 nums 和一个整数 k ，你需要将这个数组分成 k 个非空的连续子数组，使得这 k 个子数组各自和的最大值 最小。
返回分割后最小的和的最大值。
子数组 是数组中连续的部份
 */
// 1. 答案有没有范围
// 2. 有没有单调性
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        int l = 1, r = 0;
        for (int i = 0; i < nums.size(); i++)
            r += nums[i];
        int ans = 0, m = 0;
        while (l <= r) {
            m = l + ((r - l) >> 1);         // 等价于 (r + l) / 2
            if (f(nums, m) <= k) {       				// changeable，这里是能够满足，我们去左侧
                ans = m;                    // l...  m...r
                r = m - 1;                  // l..m-1
            }
            else  l = m + 1;                // 不达标，我们去右侧
        }
        return ans;
    }

    int f(vector<int>& nums, int max_sum)
    {
        int num = 1, tmp_sum = 0;       // num的初始值是1，而不是0，因为起码得有一个分支
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > max_sum) return INT16_MAX;
            if (tmp_sum + nums[i] > max_sum)
            {
                num++; tmp_sum = nums[i];
            }
            else tmp_sum += nums[i];
        }
        return num;
    }
};

int main()
{
    Solution s;
    vector<int> nums{7,2,5,10,8};
    cout << s.splitArray(nums, 2);
    return 0;
}