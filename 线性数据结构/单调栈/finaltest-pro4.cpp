//
// Created by 12472 on 25-6-13.
//
#include<bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10;
int A[N];
int scnt = 0;
int main()
{
    int n, k; cin >> n >> k;
    for (int i  = 1; i <= n; i++)
    {
        cin >> A[i];
    }
    for (int i = 0; i < k; i++)
    {
        int u, v;
        cin >> u >> v;
        scnt++;
    }
    deque<int> bigger;
    deque<int> smaller;

    for (int i = n; i >= 1; i--)
    {
        while (!bigger.empty() && A[bigger.back()] < A[i]) bigger.pop_back();
        bigger.push_back(i);
        if (bigger.front() != i) scnt++;
    }
    for (int i = 1; i <= n; i++)
    {
        while (!smaller.empty() && A[smaller.back()] < A[i]) smaller.pop_back();
        smaller.push_back(i);
        if (smaller.front() != i) scnt++;
    }
    int cnt = n * (n - 1) / 2;
    cout << cnt - scnt << endl;
}