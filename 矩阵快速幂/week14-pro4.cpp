//
// Created by 12472 on 25-5-23.
//
// 类似题：POJ 3734 Q老师染砖
// 一个方案三种情况：蓝色和绿色都为偶数，用A[i]表示；蓝绿都为奇数，用B[i]表示；蓝绿一奇一偶，用C[i]表示；
// 转移方程：A[i] = 1 * A[i] + 0 * B[i] + 1 * C[i] 都为偶数时，只能填充红；都为奇数没法转移；一奇一偶时只能填充奇数那个颜色
// 同理可得：B[i] = 0 * A[i] + 1 * B[i] + 1 * C[i]
//         C[i] = 2 * A[i] + 2 * B[i] + 1 * C[i]
// 也就是矩阵乘法
//          | 1  0  1 |
// ans[i] = | 0  1  1 | * ans[i - 1]
//          | 2  2  1 |
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;
struct matrix
{
    ll m[4][4];
    matrix()
    {
        memset(m, 0, sizeof(m));
    }
}ans, t;
matrix operator * (const matrix &a, const matrix &b)
{
    matrix tmp;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                tmp.m[i][j] = (tmp.m[i][j] + a.m[i][k] * b.m[k][j]) % MOD;
    return tmp;

}

matrix matrix_pow(matrix &a, ll n)
{
    matrix tmp;
    for (int i = 0; i < 4; i++) tmp.m[i][i] = 1;
    while (n)
    {
        if (n & 1)
        {
            tmp = tmp * a;
        }
        a = a * a;
        n >>= 1;
    }
    return tmp;
}

ll Ans(ll n)
{
    if (n == 1) return 1;
    memset(t.m, 0, sizeof(t.m));
    memcpy(ans.m, t.m, sizeof(t.m));
    ans.m[1][1] = 1, ans.m[2][1] = 0, ans.m[3][1] = 2;
    t.m[1][1] = t.m[1][3] = 1;
    t.m[2][2] = t.m[2][3] = 1;
    t.m[3][1] = t.m[3][2] = 2, t.m[3][3] = 1;
    ans = matrix_pow(t, n - 1) * ans;
    return ans.m[1][1] % MOD;
}

int main()
{
    int T; cin >> T;
    while (T--)
    {
        ll n; cin >> n;
        cout << Ans(n) << endl;
    }
    return 0;
}