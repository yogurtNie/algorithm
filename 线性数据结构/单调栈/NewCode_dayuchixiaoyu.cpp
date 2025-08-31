//
// Created by 12472 on 25-6-21.
//
// 大鱼吃小鱼
/*
*现在有N条鱼，每条鱼的体积为Ai，从左到右排成一排。
A数组是一个排列。
小明每轮可以执行一次大鱼吃小鱼的操作
一次大鱼吃小鱼的操作：对于每条鱼，它在每一次操作时会吃掉右边比自己小的第一条鱼
值得注意的时，在一次操作中，每条鱼吃比自己小的鱼的时候是同时发生的。
举一个例子，假设现在有三条鱼,体积为分别[5，4，3]，5吃4，4吃3，一次操作后就剩下[5]一条鱼。
爸爸问小明，你知道要多少次操作，鱼的数量就不会变了嘛？
 */
// https://www.nowcoder.com/practice/77199defc4b74b24b8ebf6244e1793de
// 栈维护的含义是：进栈时这条鱼没有被处理，另一个参数的意思是：处理它右边所有能处理的鱼需要几轮
// 考虑有相等的鱼怎么处理：如果相等也能弹出，不符合规则，因为弹出一次是需要+1并取max的
// 所以相等也可以进栈，不用严格小压大
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
pair<int, int> st[N];
int f[N];
int top = 0;
int main()
{
    int n; cin >> n;
    int cur = 0, now = 0;
    for (int i = 0; i < n; i++)
        cin >> f[i];
    for (int i = n - 1; i >= 0; i--)
    {
        now = 0;            // 意思是处理这条鱼右边的所有鱼需要几轮
        while (top > 0 && f[st[top - 1].first] < f[i])
        {
            cur = st[--top].second;
            now = max(now + 1, cur);
        }
        st[top++] = make_pair(i,now);
    }
    int ans = 0;
    while (top > 0)
    {
        ans = max(ans, st[--top].second);
    }
    cout << ans << endl;
    return 0;
}