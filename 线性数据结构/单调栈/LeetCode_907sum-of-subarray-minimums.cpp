//
// Created by 12472 on 25-6-17.
//
// 求数组连续区间的最小值求和：范围最小值
// 用单调栈能得到的是：某位置的左右最小值；和区间最小值的关系是：
//     1 ... 3...2
// 0 1 2 3 4 5 6 7 8 9
// 在区间[3, 6]，最小值一定是3，因为没有比3更小的了
// 同理，[3, 5] [4, 6] [4, 5]都一定是3，因为没有比3更小的了
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> ans(n, vector<int>(2, -1));
        vector<int> Stack(n, 0);
        int top = 0, cur = 0;
        for (int i = 0; i < n; i++)
        {
            // 维护单调递增栈（严格单调）
            while (top > 0 && arr[Stack[top - 1]] >= arr[i])
            {
                cur = Stack[--top];
                ans[cur][0] = top == 0 ? -1 : Stack[top - 1];
                ans[cur][1] = i;
            }
            Stack[top++] = i;
        }
        // 清算
        while (top > 0)
        {
            cur = Stack[--top];
            ans[cur][0] = top == 0 ? -1 : Stack[top - 1];
            ans[cur][1] = -1;
        }
        // 校正
        for (int i = n - 2; i >= 0; i--)
        {
            if (ans[i][1] != -1 && arr[i] == arr[ans[i][1]])
            {
                ans[i][1] = ans[ans[i][1]][1];
            }
        }
        // for (int i = 0; i < n; i++)
        // {
        //     cout << ans[i][0] << " " << ans[i][1] << endl;
        // }

        // 开始算答案
        int left = 0, right = 0;
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            left = ans[i][0] == -1 ? -1 : ans[i][0];
            right = ans[i][1] == -1 ? n : ans[i][1];
            sum = (sum % MOD + (i - left) * (right - i) * arr[i] % MOD) % MOD;
        }
        return sum;
    }
};

int main()
{
    vector<int> arr = {3, 1, 2, 4};
    Solution sol;
    cout << sol.sumSubarrayMins(arr) << endl;
}