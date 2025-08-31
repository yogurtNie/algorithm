//
// Created by 12472 on 25-5-13.
//
// 题目：合并两个序列，每个序列原本的相对位置不能改变；求四种颜色最大的长度（最大位置和最小位置之差）之和的最小值
// 1.确定状态：dp(i, j)代表的是，分别从序列A和序列B中取出i和j个元素之后的最小长度
// 2.状态转移：在移走某个元素时，如何判断要在总数上加多少？其实很简单，此时有多少颜色尚未结束，则加几
// 所以dp(i, j) = min(dp(i - 1, j) + cnt_color, dp(i, j - 1) + cnt_color)
// 3.边界：答案是dp(n, m), 初始值dp(0, 0) = 0；

#include<bits/stdc++.h>
using namespace std;
//string str1, str2;
const int N = 5e3 + 10, INF = 0x3f3f3f3f;
int dp[N][N];
// 预处理，记录每个元素的开始和结束时间
int startIdx[2][27], endIdx[2][27];
// 预处理，记录对于每个节点对应尚未结束的颜色计数，c(i ,j)表示，从A中取出i个和从B中取出j个之后尚未结束的颜色
int cnt[N][N];

int main()
{
    int T; cin >> T;
    while (T--)
    {
        string str1, str2; cin >> str1 >> str2;
       // memset(dp, 0, sizeof(dp));
        memset(startIdx, INF, sizeof(startIdx));
        memset(endIdx, -1, sizeof(endIdx));
        int n = str1.length(), m = str2.length();
        str1 = " " + str1;
        str2 = " " + str2;

        for (int i = 1; i <= n; i++)
        {
            startIdx[0][str1[i] - 'A' + 1] = min(startIdx[0][str1[i] - 'A' + 1], i);
            endIdx[0][str1[i] - 'A' + 1] = max(endIdx[0][str1[i] - 'A' + 1], i);
        }
        for (int i = 1; i <= m; i++)
        {
            startIdx[1][str2[i] - 'A' + 1] = min(startIdx[1][str2[i] - 'A' + 1], i);
            endIdx[1][str2[i] - 'A' + 1] = max(endIdx[1][str2[i] - 'A' + 1], i);
        }

        // 填充cnt的过程
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= m; j++)
            {
                if (i == 0 && j == 0) continue;

                int index1 = (int)str1[i] - 'A' + 1;
                int index2 = (int)str2[j] - 'A' + 1;

                if (i)  // 当i不为0
                {
                    cnt[i][j] = cnt[i - 1][j];      // 先继承上层状态
                    if (startIdx[0][index1] == i && startIdx[1][index1] > j)    // 在决策是否选择i对应的str1的元素放进队列中，如果j中已经放过相同颜色的字符，则此时不该++cnt
                        cnt[i][j]++;
                    if (endIdx[0][index1] == i && endIdx[1][index1] <= j)
                        cnt[i][j]--;

                }
                if (j)
                {
                    cnt[i][j] = cnt[i][j - 1];
                    if (startIdx[1][index2] == j && startIdx[0][index2] > i)
                        cnt[i][j]++;
                    if (endIdx[1][index2] == j && endIdx[0][index2] <= i)
                        cnt[i][j]--;
                }
            }
        }
        // dp[0][0] = 0;
        // dp[0][1] = dp[1][0] = 0;

        // 填充完毕后开始递推
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= m; j++)
            {
                if (!i && !j) continue;
                dp[i][j] = INF;
                if (i) dp[i][j] = min(dp[i - 1][j] + cnt[i - 1][j], dp[i][j]);
                if (j) dp[i][j] = min(dp[i][j - 1] + cnt[i][j - 1], dp[i][j]);
            }
        }

        cout << dp[n][m] << endl;

    }
    return 0;
}