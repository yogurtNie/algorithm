//
// Created by 12472 on 25-6-16.
//
#include<bits/stdc++.h>
using namespace std;
// const int N = 1e5 + 10;
// int MyStack[N];
// int ans[N];
// int arr[N];
// int top = 0;
// int main()
// {
//     int n; cin >> n;
//     for (int i = 1; i <= n; i++)
//     {
//         cin >> arr[i];
//     }
//
//     // 开始维护单调递减栈
//     int cur = 0;
//     for (int i = 1; i <= n; i++)
//     {
//         while (top > 0 && arr[MyStack[top - 1]] <= arr[i])
//         {
//             cur = MyStack[--top];
//             ans[cur] = i - cur ;
//         }
//         MyStack[top++] = i;
//     }
//
//     // 清算
//     while (top > 0)
//     {
//         cur = MyStack[--top];
//         ans[cur] = 0;
//     }
//
//     for (int i = 1; i <= n; i++) cout << ans[i] << " ";
//
// }

class Solution {
public:
    vector<int> ans;
    vector<int> MyStack;
    vector<int> re;
    int top = 0;
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        ans.resize(n);
        MyStack.resize(n);
        re.resize(n);
        // 开始维护单调递减栈
        int cur = 0;
        for (int i = 0; i < n; i++)
        {
            if (top > 0){
                while (temperatures[MyStack[top - 1]] <= temperatures[i])
                {
                    cur = MyStack[--top];
                    ans[cur] = i - cur;
                    if (top == 0) break;
                }
            }
            MyStack[top++] = i;
        }

        // 清算
        while (top > 0)
        {
            cur = MyStack[--top];
            ans[cur] = 0;
        }

        // 校正
        for (int i = n - 2; i >= 0; i--) {
            if (ans[i] != 0 && temperatures[i] == temperatures[re[i]]) {
                if (ans[re[i]] != 0) ans[i] += ans[re[i]];
                else ans[i] = 0;
            }
        }
        return ans;
    }
};

int main()
{
    vector<int> temperatures = {1,2,3,4,5,6,7,8,9,10};
    Solution sol;
    sol.dailyTemperatures(temperatures);
    return 0;
}