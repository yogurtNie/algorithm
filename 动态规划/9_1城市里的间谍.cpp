#include<bits/stdc++.h>
using namespace std;
/*题目：求从车站1到车站n的最少等待时间
从1会有M1辆不同出发时间的车
从n会有M2辆不同出发时间的车
换乘无需时间，要求在T内到达车站n

1.状态方程：d[i][j]表示，在时刻i时，处于车站j，最少要等待的时间
t[i]表示，从i到i+1的行驶时间
2.状态转移方程：d[i][j] = 1.等一分钟（换时刻）
						  2.搭乘向右开的车，状态转移到 d[i + t[j]][j+1]
						  3.搭乘向左开的车，状态转移到 d[i + t[j-1]][j-1]
3.起始状态为d[T][n], 最终结果为d[0][1]
*/
const int N = 60;
const int M = 210;
const int INF = 0x3f3f3f3f;
int t[N];					// 车站的行驶时间
int M1[N], M2[N];			// 列车的出发时间 —— 其实可以直接转换成能够和i, j联系上的数组
bool has_train[M][N][2];	// 三维坐标(i, j, k) 表示在i时刻的j车站有向左/向右开去的列车
int d[M][N];				// 动规数组

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int cnt = 0;
	while (true) {
		memset(has_train, 0, sizeof(has_train));
		memset(d, 0, sizeof(d));
		memset(M1, 0, sizeof(M1));
		memset(M2, 0, sizeof(M2));
		memset(t, 0, sizeof(t));
		int n; cin >> n;
		if (n == 0) break;
		int T; cin >> T;
		for (int i = 1; i < n; i++) {
			cin >> t[i];
		}
		//for (int i = 1; i < n; i++) cout << t[i] << " ";
		//cout << endl;
		int m1; cin >> m1;		// 向右开
		for (int i = 1; i <= m1; i++) {
			cin >> M1[i];
		}
		int m2; cin >> m2; 		// 向左开
		for (int i = 1; i <= m2; i++) {
			cin >> M2[i];
		}
		
		//初始化d数组
		for (int i = 1; i <= n; i++) d[T][i] = INF;
		d[T][n] = 0;
		
		//初始化has_train数组
		for (int i = 1; i <= m1; i++) {
			int time = M1[i];
			for (int k = 1; time <= T && k < n; k++) {
				has_train[time][k][0] = 1;
				time += t[k];
			}
		}
		
		for (int i = 1; i <= m2; i++) {
			int time = M2[i];
			for (int k = n; time <= T && k > 1; k--) {
				has_train[time][k][1] = 1;
				time += t[k - 1];
			}
		}
		/*for (int i = 0; i <= 1; i++) {
			for (int j = 0; j <= T; j++) {
				for (int k = 1; k <= n; k++) {
					cout << has_train[j][k][i] << " ";
				}
				cout << "\n";
			}
			cout << "\n";
		}*/
		
		// 递推主体, 从(T, n)开始往回递推
		for (int i = T - 1; i >= 0; i--) {
			for (int j = 1; j <= n; j++) {
//				cout << "三个选择为：\n" ;
//				cout << "在原地等待：" << d[i+1][j] + 1 << "\n";
//				cout << "向左开：" << d[i + t[j - 1]][j - 1] << "\n";
//				cout << "向右开：" << d[i + t[j]][j + 1] << "\n";
				d[i][j] = d[i+1][j] + 1;			// 第一种选择：等到下个时刻
				if (has_train[i][j][1] && j > 1 && i + t[j - 1] <= T) { // 第二种选择：向左开
					d[i][j] = min(d[i][j], d[i + t[j - 1]][j - 1]);
				}
				if (has_train[i][j][0] && j < n && i + t[j] <= T) {	  // 第三种选择：向右开		
					d[i][j] = min(d[i][j], d[i + t[j]][j + 1]);
				}
				//cout << "最终结果为：" << d[i][j] << "\n";
			}
		}
		cout << "Case Number " << ++cnt << ": ";
		if (d[0][1] < INF) cout << d[0][1] << "\n";
		else cout << "impossible\n"; 
	}
	
	
	
	return 0;
	
}