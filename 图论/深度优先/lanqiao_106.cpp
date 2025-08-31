//
// Created by 12472 on 25-6-10.
//
// 正则问题，如果用暴力解法
#include<bits/stdc++.h>
using namespace std;
string str;
int pos = 0;
int dfs()
{
    int cnt = 0, tmp = 0;
    int n = str.size();
    while (pos < n)
    {
        // 如果是左括号，说明要来到新的一层，开始崭新的计数，然后把计数累加到上层中（就像是一个洋葱）
        if (str[pos] == '(') { pos++; tmp += dfs();}
        else if (str[pos] == ')') {pos++; cnt = max(cnt, tmp); return cnt;}
        else if (str[pos] == '|') {pos++; cnt = max(cnt, tmp); tmp = 0;}
        else if (str[pos] == 'x') {pos++; tmp++; }
    }
    cnt = max(cnt, tmp);
    return cnt;
}


int main()
{
    cin >> str;
    cout << dfs() << endl;

}