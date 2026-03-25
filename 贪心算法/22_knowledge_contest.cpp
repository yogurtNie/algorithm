//
// Created by 12472 on 26-3-25.
//
/*
* 最近部门要选两个员工去参加一个需要合作的知识竞赛，每个员工均有一个推理能力值A_i以及一个阅读能力值B_i。如果选择第i 个人和第j个人去参加竞赛，那么他们在阅读方面所表现出的能力为 (B_i+B_j) / 2
他们在推理方面所表现出的能力为 (A_i + A_j) / 2
现在需要最大化他们表现较差一方面的能力，即让 min(X,Y) 尽可能大，问这个值最大是多少。
进阶：时间复杂度O(nlogn) ，空间复杂度O(n)
3
2 2
3 1
1 3
输出：2.0
选择第一个和第二个员工或第一个和第三个时，较差方面的能力都是1.5，选择第二个和第三个时较差方面能力是2
https://www.nowcoder.com/practice/2a9089ea7e5b474fa8f688eae76bc050
 */
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    double findMinimum(vector<vector<int>>& nums, int n)
    {
        sort(nums.begin(), nums.end(), [](vector<int>& a, vector<int>& b)->bool{return abs(a[0] - a[1]) < abs(b[0] - b[1]);});
        int MAXA = nums[0][0], MAXB = nums[0][1];
        int ans = INT_MIN;
        for (int i = 1; i < n; i++)
        {
            if (nums[i][0] < nums[i][1])
                ans = max(ans, nums[i][0] + MAXA);
            else ans = max(ans, nums[i][1] + MAXB);
            MAXA = max(MAXA, nums[i][0]);
            MAXB = max(MAXB, nums[i][1]);
        }
        return (double)ans/2;
    }
};

int main()
{
    int n; vector<vector<int>> nums;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a, b; cin >> a >> b;
        nums.push_back({a,b});
    }
    Solution sol;
    double ans = sol.findMinimum(nums, n);
    cout << fixed << setprecision(1) << ans << endl;
    return 0;

}