//
// Created by 12472 on 26-3-23.
//
/*
 * 平均值最小的累加和
 * 给定一个数组arr，长度为n，给定一个数字k，表示一定要将arr划分为k个集合
 * 每个数字只能进入一个集合
 * 返回每个集合的平均值都累加起来的最小值，平均值向下取整
 * 1 <= n <= 10^5
 * 0 <= arr[i] <= 10^5
 * 1 <= k <= n
 * 无在线验证，对数器验证
 */
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int way1(vector<int> &nums, int k)
    {
        vector<int> sum(k, 0);          // 计算每个数组的总数
        vector<int> cnt(k, 0);          // 计算每个数组内部有多少个数
        return f(nums, k, 0, sum, cnt);
    }
    int f(vector<int> &nums, int k, int start, vector<int>& sum, vector<int> &cnt)
    {
        // 达标，开始结算答案
        if (start == nums.size())
        {
            int ans = 0;
            for (int j = 0; j < k; j++)
            {
                if (cnt[j] != 0) ans += sum[j] / cnt[j];
                else return INT_MAX;
            }
            return ans;
        }
        else
        {
            int ans = INT_MAX;
            // 依次分配给不同的项目
            for (int j = 0; j < k; j++)
            {
                cnt[j]++;
                sum[j] += nums[start];
                ans = min(ans, f(nums, k, start + 1, sum, cnt));
                sum[j] -= nums[start];
                cnt[j]--;
            }
            return ans;
        }
    }
    int way2(vector<int> &nums, int k)
    {
        int ans = 0, n = nums.size();
        sort(nums.begin(), nums.end());
        for (int i = 0; i < k-1; i++)
            ans += nums[i];
        int avg = 0;
        for (int i = k - 1; i < n; i++)
        {
            avg += nums[i];
        }
        avg /= n - (k - 1);
        return avg + ans;
    }
    void test()
    {
        int N = 8;
        int K = 5;
        int NUM = 30;
        int testTime = 2000;
        cout << "测试开始\n";
        for (int i = 0; i < testTime; i++)
        {
            int n = N % rand() + 1;
            vector<int> nums;
            int k = K % rand() + 1;
            for (int j = 0; j < n; j++)
            {
                int num = rand() % NUM + 1;
                nums.push_back(num);
            }
            int ans1 = way1(nums, k);
            int ans2 = way2(nums, k);
            if (ans1 != ans2)
            {
                cout << "测试错误\n";
                cout << k << " " << ans1 << " " << ans2 << "\n";
            }
            if (i % 100 == 0) cout <<"测试到第"<< i << "组\n";
        }
    }
};

int main()
{
    Solution sol;
    sol.test();
    return 0;
}