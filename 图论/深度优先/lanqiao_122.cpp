//
// Created by 12472 on 25-6-10.
//
// 四平方和，练习dfs剪枝（一步一步优化的办法）
// 发现dfs怎么都优化不好的时候，（递归），就可以试试递推了
#include<bits/stdc++.h>
using namespace std;
int n;
int a[4];
int temp[4];
int cnt;
void dfs(int i, int pre)
{
    if (i == 4 && cnt != n) return;
    if (i == 4)     // 终点
    {
        bool flag = true;       // 是否是字典序最小
        for (int j = 0; j < 4; j++)
        {
            if (a[j] < temp[j]) {flag = false; break;}
            else if (a[j] == temp[j]) continue;
            else break;
        }
        if (flag)
        {
            for (int k = 0;k < 4; k++) a[k] = temp[k];
        }
        return;
    }

    if (cnt > n) return;        // 可行性剪枝

    // 还可以进行范围剪枝，因为每确定一个数，下一个数能选的范围又少一点
    int last = 0;
    for (int tmp = 0; tmp < i; tmp++) last += temp[tmp] * temp[tmp];
    for (int j = pre; last + j * j <= n; j++ )
    {
        cnt += j * j;
        temp[i] = j;
        dfs(i + 1, j);
        cnt -= j * j;
    }


}

int main()
{
    cin >> n;
    // for (int i = 0; i < 4; i++) a[i] = INT32_MAX;
    // dfs(0, 0);
    //
    // for (int i = 0; i < 4; i++) cout << a[i] << " ";
    // return 0;
    for (int a = 0; a <= sqrt(n); a++)
    {
        for (int b = a; a * a + b * b <= n; b++)
        {
            for (int c = b; c * c + b * b + a * a <= n; c++)
            {
                int t = n - a * a - b * b - c * c;
                int d = sqrt(t);
                if (d * d == t && d >= c)
                {
                    cout << a << " " << b << " " << c << " " << d;
                    return 0;
                }
            }
        }
    }
    return 0;
}