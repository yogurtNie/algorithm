//
// Created by 12472 on 25-5-18.
//
// 有s门课程，m个老师，n个求职者。老师不能辞退，求每一门课程至少安排两个老师的最少花费
// 1. 确定状态方程：用s1表示恰好有一个老师教的科目，s2表示至少两个老师教的科目，i表示老师的编号
// 最后的状态方程为d(i, s1, s2); 为了区分在职教师和求职者，教师是0~m-1号，求职者是m~m+n-1号
// 2. 状态转移方程：d(i, s1, s2) = min( d(i + 1, s1', s2') + w[i], d(i + 1, s1, s2) )
// 前后两项代表“聘用”和“不聘用”
#include<bits/stdc++.h>
using namespace std;
const int N = 125, INF = 0x3f3f3f3f, S = 10;
int d[N][1 << S][1 << S];
int m, n, s;
int w[N];
int st[N];      // 表示第i个人能教授的科目合集

// s0用于表示没有任何人能教授的集合，不需要记忆化，因为只要有s1 s2就能倒推出s0
int dp(int i, int s0, int s1, int s2)
{
    // 边界：递推的边界是，如果所有科目都有至少两个老师教，此时就不用安排任何老师
    if (i == m + n) return s2 == (1 << s) - 1 ? 0 : INF;
    int& ans = d[i][s1][s2];
    if (ans >= 0) return ans;       // 区间dp，算过了
    ans = INF;                      // 初始化
    if (i >= m) ans = min(ans, dp(i + 1, s0, s1, s2));      // 不选这个候选者
    // 开始计算选这个人的状态改变
    int m1 = st[i] & s0;        // 代表在0人教授的课程中，这个人能教哪些
    int m2 = st[i] & s1;        // 代表在1人教授的课程中，这个人能教哪些
    s0 ^= m1;                   // 在s0这个集合里去掉这些课程
    s1 = (s1 ^ m2) | m1;        // 在s1这个集合里去掉这些课程，并把从s0里去掉的加上
    s2 |= m2;                   // 在s2这个集合里加上s1中去掉的
    ans = min(ans, dp(i + 1, s0, s1, s2) + w[i]);          // 选这个老师/候选者
    return ans;
}

int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    string str;
    while (true)
    {
        getline(cin, str);
        istringstream is(str);
        is >> s >> m >> n;
        if (s == 0) break;
        // 初始化
        for (int i = 0; i <= m + n; i++)
            for (int j = 0; j < (1 << s); j++)
                for (int k = 0; k < (1 << s); k++)
                    d[i][j][k] = -1;

        for (int i = 0; i <= m + n; i++)
        {
            w[i] = st[i] = 0;
        }

        for (int i = 0; i < m + n; i++)
        {
            string s;
            getline(cin, s);
            istringstream iss(s);
            iss >> w[i];
            int temp;
            while (iss >> temp)
            {
                st[i] |= (1 << (temp - 1));
            }
        }

        int ans = dp(0, (1 << s) - 1, 0, 0);
        cout << ans << endl;

    }
    return 0;
}
