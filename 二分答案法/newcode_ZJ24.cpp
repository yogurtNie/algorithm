//
// Created by 12472 on 25-12-7.
//
/*
* 机器人正在玩一个古老的基于DOS的游戏。游戏中有N+1座建筑——从0到N编号，从左到右排列。编号为0的建筑高度为0个单位，编号为i的建筑的高度为H(i)个单位。
起初， 机器人在编号为0的建筑处。每一步，它跳到下一个（右边）建筑。假设机器人在第k个建筑，且它现在的能量值是E, 下一步它将跳到第个k+1建筑。它将会得到或者失去正比于与H(k+1)与E之差的能量。如果 H(k+1) > E 那么机器人就失去 H(k+1) - E 的能量值，否则它将得到 E - H(k+1) 的能量值。
游戏目标是到达第个N建筑，在这个过程中，能量值不能为负数个单位。现在的问题是机器人以多少能量值开始游戏，才可以保证成功完成游戏？
 */
// 思考两步走，第一步，是否能够有单调性 —— 有，当能量值小的时候，总是比能量值大的时候更加吃亏
// 第二步，答案有没有一个确定的范围 —— 有，最小可以取到1，最大可以取到这个建筑群中最大的建筑高度h，更大的其实没意义了
// 所以我们可以用二分来尝试解决
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int H[N], n;
int f(int energe)
{
    int build = 0;
    for (int i = 1; i < n; i++)
    {
        if (H[i] > energe) energe -= (H[i] - energe);
        else energe += (energe - H[i]);
        if (energe < 0) break;
        build = i;
    }
    return build;
}
int minPassEnerge()
{
    int l = 1, r = 0;
    for (int i = 0; i < n; i++)
        if (r < H[i]) r = H[i];
    int ans = 0, m = 0;
    while (l <= r)
    {
        m = l + ((r - l) >> 1);
        if (f(m) == n - 1)          // m 可以到达，右侧必定全能到达
        {
            ans = m;
            r = m - 1;
        }
        else l = m + 1;
    }
    return ans;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> H[i];
    cout << minPassEnerge() << endl;
    return 0;
}