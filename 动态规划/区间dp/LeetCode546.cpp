//
// Created by 12472 on 25-6-8.
//
// 移除盒子，同样是3维的尝试，第三维代表的是前缀信息
#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int dp[N][N][N];
int len;
int func(vector<int>& boxes, int l, int r, int k)
{
    // 边界条件
    if (l > r) return 0;
    if (l == r) return (k + 1) * (k + 1);
    if (dp[l][r][k] != -1) return dp[l][r][k];

    // 开始设置找到和前缀一起的下标
    int s = l;
    while (s + 1 < len && boxes[s + 1] == boxes[l]) s++;
    int cnt = s - l + 1 + k;

    // 开始分类讨论
    int p1 = cnt * cnt + func(boxes, s + 1, r, 0);      // 第一种可能，直接把前缀删掉
    // 第二种可能，在区间内找到对应下标进行划分
    int p2 = 0;
    for (int i = s + 2; i < len; i++)
    {
        if (boxes[i] == boxes[s] && boxes[i] != boxes[i - 1])   // 当找到一段和前缀一样的首部时，可用
        {
            p2 = max(p2, func(boxes, s + 1, i - 1, 0) + func(boxes, i, r, cnt));
        }
    }

    return dp[l][r][k] = max(p1, p2);
}
int removeBoxes(vector<int>& boxes) {
    len = boxes.size();
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len; j++)
            for (int k = 0; k < len; k++)
                dp[i][j][k] = -1;
    return func(boxes, 0, len - 1, 0);
}

int main()
{
    vector<int> boxes = {1,3,2,2,2,3,4,3,1};
    cout << removeBoxes(boxes) << endl;
    return 0;
}