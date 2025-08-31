//
// Created by 12472 on 25-6-6.
//
#include<bits/stdc++.h>
using namespace std;
void debt(vector<int>& ans, vector<vector<int>>& transactions) {
    int n = transactions.size();
    int temp[13] = {0};
    for (int i = 0; i < n; i++) {
        vector<int>& now = transactions[i];
        temp[now[0]] -= now[2];
        temp[now[1]] += now[2];
    }
    for (int i = 0; i < 13; i++) {
        if (temp[i] != 0) ans.push_back(temp[i]);
    }
}
int f(int s, int sum, vector<int>& arr, int n, int* dp) {
    if (dp[s] != -1) return dp[s];
    int ans = 0;
    // 如果集合中只有一个人没还清了，则最后能拆出来的不可再分集合数量一定是0
    if ((s & (s - 1)) != 0) {
        if (sum == 0) {         // 如果最终的结果是0，那么只需要随机独立一个节点，然后去剩下的里面找最大，最后再+1就可以了
            for (int i = 0; i < n; i++) {
                if ((s & (1 << i)) != 0) {
                    ans = f(s ^ (1 << i), sum - arr[i], arr, n, dp) + 1;
                    break;
                }
            }
        }
        else {                  // 如果最终结果不是0，那么需要遍历所有节点，拿出来选最大
            for (int i = 0; i < n; i++) {
                if ((s & (1 << i)) != 0) {
                    ans = max(ans, f(s ^ (1 << i), sum - arr[i], arr, n, dp));
                }
            }
        }
    }
    dp[s] = ans;
    return ans;
}
int minTransfers(vector<vector<int>>& transactions) {
    // 先将所有的收支都跑一遍，拿到最终的结果（里面只有非0的钱数结果）
    vector<int> arr;
    debt(arr, transactions);
    int n = arr.size();
    // 我们需要的东西是：在这个无 0 的最终收支数组中，能够拆分出来的最大不可再分集合的个数
    // 最终结果会是，总的收支数减去这个最大不可再分集合的数量
    // 对于状态的设计而言，我们有：当前还未还清债务的人s，当前债务的总大小，当前已经找到的不可再分集合的个数（但这个是通过返回值来体现的，也就是要记录到dp数组中去的）
    int* dp = new int [1 << n];
    for (int i = 0; i < 1 << n; i++) dp[i] = -1;
    return n - f((1 << n) - 1, 0, arr, n, dp);
}

int main()
{
    vector<vector<int>> transactions = {{0,1,10},{2,0,5}};
    cout << minTransfers(transactions) << endl;
    return 0;
}