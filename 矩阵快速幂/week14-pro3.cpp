//
// Created by 12472 on 25-5-23.
//
// 斐波那契数列，大数量级 + 矩阵快速幂
// 记忆化优化
// | 0  1 |  *   | f(n - 2) |  =  |      f(n - 2)       |
// | 1  1 |      | f(n - 3) |     | f(n - 2) + f(n - 3) |
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int mod;
struct matrix
{
    ll m[3][3];
    matrix()
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                m[i][j] = 0;

    }
}ans, t;

matrix operator * (const matrix &a, const matrix &b)
{
    matrix temp;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                temp.m[i][j] = (temp.m[i][j] + a.m[i][k] * b.m[k][j]) % mod;
    return temp;
}

matrix matrix_pow(matrix& a, ll p)
{
    matrix temp;
    for (int i = 0; i < 3; i++) temp.m[i][i] = 1;           // 单位矩阵
    while (p)
    {
        if (p & 1)
        {
            temp = temp * a;                                // 顺序不能倒，因为矩阵运算不满足交换律
        }
        a = a * a;
        p >>= 1;
    }
    return temp;
}

ll Ans(ll n)
{
    if (n == 1) return 1 % mod;
    if (n == 2) return 1 % mod;
    if (n == 3) return 2 % mod;
    memset(t.m, 0, sizeof(t.m));
    memset (ans.m, 0, sizeof(ans.m));
    ans.m[1][1] = ans.m[2][1] = 1;
    t.m[1][2] = t.m[2][1] = t.m[2][2] = 1;

    matrix tmp = matrix_pow(t, n - 3) * ans;
    ll res = (tmp.m[1][1] % mod + tmp.m[2][1] % mod) % mod;
    return res;
}
int main()
{
    int T; cin >> T;
    while (T--)
    {
        ll n; cin >> n >> mod;
        cout << Ans(n) << endl;
    }
    return 0;
}