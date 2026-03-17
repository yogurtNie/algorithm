//
// Created by 12472 on 26-3-17.
//
/*
 * 有一个会议时间安排的数组 intervals，每个会议时间都包括开始和结束的时间，intervals[i]=[starti,endi]
 * 返回所需会议室的最小数量
 * 本题其实本质上是最多线段重合问题，所以用牛客的测试链接就行
 * https://www.nowcoder.com/practice/1ae8d0b6bb4e4bcdbf64ec491f63fc37
每一个线段都有start和end两个数据项，表示这条线段在X轴上从start位置开始到end位置结束。
给定一批线段，求所有重合区域中最多重合了几个线段，首尾相接的线段不算重合。
例如：线段[1,2]和线段[2.3]不重合。
线段[1,3]和线段[2,3]重合
第一行一个数N，表示有N条线段
接下来N行每行2个数，表示线段起始和终止位置
输出描述：
输出一个数，表示同一个位置最多重合多少条线段
1≤N≤10^4
1≤start,end≤10^5
*/
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
vector<pair<int,int>> vec;
int N;
bool bmp(pair<int, int> & a, pair<int, int> & b)
{
    return a.first < b.first;
}
void solve()
{
    size_t ans = 1;
    priority_queue<int,vector<int>,greater<int>> q;
    for (int i = 0; i < N; i++)
    {
        while (!q.empty() && q.top() <= vec[i].first) q.pop();
        q.push(vec[i].second);
        ans = max(ans, q.size());
    }
    cout << ans << endl;
}
int main() {
    cin >> N;
    int a, b;
    for (int i = 0; i < N; i++)
    {
        cin >> a >> b;
        vec.emplace_back(a, b);
    }
    sort(vec.begin(), vec.end());
    solve();
}
// 64 位输出请用 printf("%lld")

