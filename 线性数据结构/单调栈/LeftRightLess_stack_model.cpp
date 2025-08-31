//
// Created by 12472 on 25-6-15.
//
// 有相等值存在的左右最小单调栈，手写栈
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int MyStack[N];
int arr[N];
int ans[N][2];
int top = 0;
int main()
{
    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> arr[i];
    int cur = 0;
    for (int i = 0; i < n; i++)
    {
        // 当栈不为空，且当前栈顶元素比当前元素要大，则弹出（维护单调递增栈）
        while (top > 0 && arr[MyStack[top - 1]] >= arr[i])
        {
            cur = MyStack[--top];               // 取当前栈顶，弹出时可以填答案了
            ans[cur][0] = ((top == 0) ? -1 : MyStack[top - 1]);     // 左边最小数是当前栈顶元素，如果栈顶为空，则是-1
            ans[cur][1] = i;
        }
        MyStack[top++] = i;     // top永远标记栈顶，栈顶在栈未满时一定是空的

    }
    // 全部遍历完之后，进入清算阶段
    while (top > 0)
    {
        cur = MyStack[--top];
        ans[cur][0] = top == 0 ? -1 : MyStack[top - 1];
        ans[cur][1] = -1;
    }
    // for (int i = 0; i < n; i++)
    // {
    //     cout << ans[i][0] << " " << ans[i][1] << endl;
    // }
    // cout << "-------------" << endl;

    // 清算完成后，进入矫正阶段，从后往前校正
    for (int i = n - 2; i >= 0; i--)
    {
        // 矫正的范围是：如果i对应的元素和右边元素是一样的，用右边元素的答案替换i的答案
        // 易错
        if (ans[i][1] != -1 && arr[i] == arr[ans[i][1]])
        {
            ans[i][1] = ans[ans[i][1]][1];
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << ans[i][0] << " " << ans[i][1] << endl;
    }
    return 0;
}