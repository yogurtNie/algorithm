//
// Created by 12472 on 26-2-28.
//
/*
给定一张 $n$ 个点 $m$ 条边的有向图，求出其所有的强连通分量。
**注意，本题可能存在重边和自环。**
## 输入格式
第一行两个正整数 $n$，$m$，表示图的点数和边数。
接下来 $m$ 行，每行两个正整数 $u$ 和 $v$ 表示一条边。
## 输出格式
第一行一个整数表示这张图的强连通分量数目。
接下来每行输出一个强连通分量。第一行输出 $1$ 号点所在强连通分量，第二行输出 $2$ 号点所在强连通分量，若已被输出，则改为输出 $3$ 号点所在强连通分量，以此类推。每个强连通分量按节点编号大小输出。

对于所有数据，$1 \le n \le 10000$，$1 \le m \le 100000$。
https://www.luogu.com.cn/problem/B3609
*/
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10, M = 1e5 + 10;
vector<vector<int>> graph;
int n, m;       // 图的点数与边数
int dfn[N], low[N]; // 数组一为树边编号，数组二为口袋编号（束口的最小编号，通过一条返回边能到达的最上方序号）
int cntd;

// 栈
int sta[N];
int top;

// 判断束口和分配编号的数组
int belong[N];          // 当前序号所属强联通分量的序号
int sccArr[N];
int sccl[N], sccr[N];
int idx;
int sccCnt;

bool sccPrint[N];

void tarjan(int u)
{
    dfn[u] = low[u] = ++cntd;       // 初始化为搜索序号
    sta[++top] = u;                 // 入栈
    for (int v : graph[u])
    {
        if (dfn[v] == 0)
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else
        {
            if (belong[v] == 0)
            {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
    if (dfn[u] == low[u])
    {
        sccCnt++;
        sccl[sccCnt] = idx + 1;
        int pop;
        do
        {
            pop = sta[top--];
            belong[pop] = sccCnt;
            sccArr[++idx] = pop;
        } while (pop != u);
        sccr[sccCnt] = idx;
    }
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++)
    {
        cin >> u >> v;
        graph[u].push_back(v);
    }
    for (int i = 1; i <= n; i++)
    {
        if (dfn[i] == 0)
        {
            tarjan(i);          // 没有强联通编号，则从此开始搜索
        }
    }
    cout << sccCnt << "\n";
    for (int i = 1; i <= sccCnt; i++)
    {
        sort(sccArr + sccl[i], sccArr + sccr[i] + 1);
    }
    for (int i = 1; i <= n; i++)
    {
        int scc = belong[i];
        if (!sccPrint[scc])
        {
            sccPrint[scc] = true;
            for (int j = sccl[scc]; j <= sccr[scc]; j++)
            {
                cout << sccArr[j] << " ";
            }
            cout << "\n";
        }
    }
    return 0;
}