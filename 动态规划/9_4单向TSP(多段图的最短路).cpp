#include<bits/stdc++.h>
using namespace std;
/* 题目： 求一个矩形最短的不重复路径（每列进行决策，可以直行、右上、右下）
1.确认状态方程：d(i, j)是指，从(i, j)到最后一列的最小开销
2.确定状态转移方程：d(i, j) = min(d(i-1, j+1), d(i, j+1), d(i+1, j+1))
3.递推顺序：从后往前递推，同时还需要记录下一列行号的最小值，以便输出最终结果
4.边界：d(i, n) = a(i, n)
*/
const int INF = 0x3f3f3f3f;
const int R = 15, C = 110;
int a[R][C];
int dp[R][C];
int Next[R][C];
int main() {
	int n, m;
	while (cin >> n) {
		cin >> m;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cin >> a[i][j];
			}
		}
		int ans = INF, first = 0;
		for (int j = m; j >= 1; j--) {
			for (int i = 1; i <= n; i++) {
				if (j == m) dp[i][j] = a[i][j];
				else {
					//处理边界的第一行和最后一行
					int row[3] = {i-1, i, i+1};
					if (i == 1) row[0] = n;
					if (i == n) row[2] = 1;
					sort(row, row + 3); 		//字典序排序
					dp[i][j] = INF;
					for (int k = 0; k <= 2; k++) {
						if (dp[i][j] > dp[row[k]][j+1] + a[i][j]) {
							dp[i][j] = dp[row[k]][j+1] + a[i][j];
							Next[i][j] = row[k];	//记录最优解序号
						}
					}
				}
				// 比出最后一列(第一列)的最小值
				if (j == 1 && dp[i][j] < ans) {
					ans = dp[i][j]; first = i; 
				}
			}
			
		}
		cout << first;
		//printf("%d", first);
		for (int i = first, j = 1; j < m && i <= n; j++) {
			//printf(" %d", Next[i][j]);
			cout << " " << Next[i][j];
			i = Next[i][j];
		}
		cout << "\n" << ans << "\n";
		//printf("\n%d\n", ans);
	}
	return 0;	
}