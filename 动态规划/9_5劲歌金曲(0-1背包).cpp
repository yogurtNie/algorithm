#include<bits/stdc++.h>
using namespace std;
/*题目：在固定时间内选择尽可能多的歌唱曲目，同时剩下至少1s用于选择劲歌金曲
1. 状态方程：d(i, j)代表的状态是，当时间还剩下j时，前i首歌曲可以唱的最大时间
2. 状态转移方程: d(i, j) = max( d(i-1, j), d(i-1, j-T[i]) +  T[i] )
但是，如果单开空间需要1e9的数量级，显然不现实。
由于n+1首曲子总长度严格大于t，且每首歌保证不超过3min，所以
t实际上是180n + 678
*/
const int N = 60;
typedef long long ll;
//int Time[N];
int d[180*N + 678], Next[180*N + 678];

// 由于滚动数组无法追溯方案本身，所以得开二维数组
int main() {
	int cnt; cin >> cnt;
	for (int c = 1; c <= cnt; c++) {
		int choice_cnt = 0;
		int n, t; cin >> n >> t;
		memset(d, 0, sizeof(d));
		memset(Next, 0, sizeof(Next));
		for (int i = 1; i <= n; i++) {
			int T; cin >> T;
			for (int j = t - 1; j >= T; j--) {
				if ( Next[j - T] + 1 > Next[j] || (Next[j - T] + 1 == Next[j] && d[j] < d[j - T] + T)) {
					Next[j] = Next[j - T] + 1;
					d[j] = d[j - T] + T;
				}
			}
		}
//		for (int j = 0; j <= t; j++) cout << d[j] << " ";
//		cout << endl;
		// 找方案
		ll ans = d[t-1] + 678;
		cout << "Case " << c << ": " << Next[t-1]+1 << " ";
		cout << ans << endl;
	}
	return 0;
}

/*int main() {
	int T; cin >> T;
	for (int c = 1; c <= T; c++) {
		int n, t; cin >> n >> t;
		for (int i = 1; i <= n; i++) cin >> time[i];
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < t; j++) {
				d[i][j] = (i == 1) ? 0 : d[i-1][j];
				if (j >= time[i]) {
					if (d[i][j] < d[i-1][j-time[i]] + time[i]) {
						d[i][j] = d[i-1][j-time[i]] + time[i];
					}
				}
			}
		}
		int last = d[n][t-1]; 
		for (int i = n-1; i >= 1; i--) {
			if (last >= time[i+1] && d[i][] + time[i] == d[i+1][])
		}
	}
}*/