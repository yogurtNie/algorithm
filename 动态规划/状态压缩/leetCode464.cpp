//
// Created by 12472 on 25-6-6.
//
#include<bits/stdc++.h>
using namespace std;
bool dp(int n, int s, int sum, int* d){
    if (sum <= 0) {
        return false;
    }
    if (d[s] != 0) return d[s] == 1;
    bool ans = false;
    for (int i = 1;i <= n; i++) {
        if ((s & (1 << i)) == 1 && !dp(n, (s ^ (1 << i)), sum - i, d)) {
            ans = true;
            break;
        }
    }
    d[s] = (ans ? 1 : -1);
    return ans;


}
bool canIWin(int maxChoosableInteger, int desiredTotal) {
    int n = maxChoosableInteger;
    int sum = desiredTotal;
    if (sum == 0) return true;
    // 如果所有数字加起来也没有sum大，则没有赢家
    if (n * (n + 1) / 2 < sum) return false;
    int* d = new int[1 << (n + 1)];
    for (int i = 0; i < (1 << (n + 1)); i++) d[i] = 0;
    return dp(n, (1 << n + 1) - 1, sum, d);

}


int main()
{
    int n, sum;
    cin >> n >> sum;
    canIWin(n, sum);
    return 0;
}