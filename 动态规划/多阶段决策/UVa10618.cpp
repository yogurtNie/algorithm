//
// Created by 12472 on 25-5-26.
//
#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int L = 1;
const int R = 2;
char ss[100];
int d[100][4][4][3], action[100][4][4][3];          // a, b, s分别为4, 4, 3种状态
int pos[256], n;
char place[] = ".LR";

int get(int a, int ta)                  // 统计本次移动和/踩的脚消耗的能量，统计依据是上次和上上次的位置关系？不对，是本次和下次的位置关系
{
    if (a == ta) return 3;              // 相同的位置
    else if  (a + ta == 3) return 7;    // 相对的位置，就是0和3（上和下），1和2（左和右）
    else return 5;                      // 相邻的位置
}

int energy(int a, int b, int s, int f, int t, int& ta, int& tb)
        //本次左脚 本次右脚 上次动作 下次动脚 下次位置 左脚下次位置 右脚下次位置
{
    ta = a; tb = b;
    if (f == 1) ta = t;
    else if (f ==2) tb = t;

    if (ta == tb) return -1;                // 踩到同一个位置
    if (ta == R && tb == L) return -1;      // 背面跳舞机
    if (ta == R && tb != b) return -1;      // 左脚踩了右边，但是右脚动了
    if (tb == L && ta != a) return -1;

    int e = 0;
    if (f == 0) e = 0;                      // 没有脚动作，所以没有能量消耗
    else if (f != s) e = 1;                 // 上次移动的脚不是现在移动的脚

    if (f == s)                             // 上次动和本次动的脚是一样的
    {
        if (f == 1) e = get(a, ta);
        else if (f == 2) e = get(b, tb);
    }

    return e;
}

// 更新action数组
void update(int i, int a, int b, int s, int f, int t)
        // 踩几个箭头  左脚  右脚  上次动作 本次移动的脚 移动方向
{
    int ta, tb;
    int e = energy(a, b, s, f, t, ta, tb);
    if (e == -1) return;

    int cost = d[i + 1][ta][tb][f] + e;
    int& ans = d[i][a][b][s];

    if (cost < ans)
    {
        ans = cost;
        action[i][a][b][s] = (f << 2) | t;             // 想了个办法，将f和t同时保存在一个数字里
        // f有三个状态，用两位二进制数表示；t有四个状态，也得用两位二进制数表示（想要输出答案，就必须知道规划过程中的方向和移动的脚），方向是指接下来去哪个箭头，f则标识由哪个脚去
    }
}

void dp()
{
    n = strlen(ss);
    memset(d, 0, sizeof(d));

    // 开始递推
    for (int i = n; i >= 0; i--)                    // 枚举箭头
    {
        for (int a = 0; a < 4; a++)                 // 枚举左右脚的状态
        {
            for (int b = 0; b < 4; b++)
            {
                if (a == b) continue;
                for (int s = 0; s < 3; s++)         // 上一步的状态
                {
                    d[i][a][b][s] = INF;
                    if (ss[i] == '.')               // 本次要踩的为空
                    {
                        update(i, a, b, s, 0, 0);   // 啥也不干
                        for (int t = 0; t < 4; t++)
                        {
                            update(i, a, b, s, 1, t);       // 带动左脚
                            update(i, a, b, s, 2, t);       // 动右脚
                        }
                    }
                    else
                    {
                        int t = pos[ss[i]];
                        update(i, a, b, s, 1, t);           // 左脚去踩
                        update(i, a, b, s, 2, t);           // 右脚去踩
                    }
                }
            }
        }
    }
}

void print()
{
    int a = 1, b = 2, s = 0;
    for (int i = 0; i <= n; i++)
    {
        int f = action[i][a][b][s] >> 2;
        int t = action[i][a][b][s] & 3;
        printf("%c", place[f]);

        s = f;
        if (f == 1) a = t;
        else if (f == 2) b = t;
    }
    printf("\n");
}

int main()
{
    pos['U'] = 0;
    pos['L'] = 1;
    pos['R'] = 2;
    pos['D'] = 3;
    while (scanf("%s", ss) != EOF)
    {
        if (ss[0] == '#') break;
        dp();
        print();
    }
    return 0;
}