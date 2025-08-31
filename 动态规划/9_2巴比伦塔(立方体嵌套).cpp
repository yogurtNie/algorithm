#include<bits/stdc++.h>
using namespace std;
/* 有n种立方体，选一些立方体摞成一根尽可能高的柱子，要求每个立方体的
底面长宽严格小于它下放立方体的底面长宽（类似矩形嵌套）

一个小问题是，立方体的x, y, z可能很大，如果像矩形嵌套那样
直接用(x, y)来标记状态值，可能会很浪费空间
因此可以用(idx, k)二元组来间接表达状态，其中idx为顶面立方体
的序号，k为高的序号
比如，若立方体3的大小为a*b*c (a<=b<=c)，则状态(3, 1)指的是立方体在顶面，
且以b为高，所以a*c为底面

每一个立方体都可能作为顶点存在
1.状态方程d[i][k]表示，以i状态为顶点的柱子的最高高度, i状态由一个二元组确定
2.状态转移方程：d[i][k1] = max(d[j][k2] + b[j].dm[k2] | G[i][k1][j][k2]) 
*/
typedef long long ll;
const int N = 40;
ll d[N][3];			// 状态数组
struct block{
	ll dm[3];
}B[N];					// 立方体数组
bool G[N][3][N][3];			// 邻接矩阵
int n; 
// 初始化图
void init() {
	for (int i = 1; i <= n; i++) {
		for (int k1 = 0; k1 <= 2; k1++) {
			for (int j = 1; j <= n; j++) {
				for (int k2 = 0; k2 <= 2; k2++) {
					int a1 = 0, b1 = 0, a2 = 0, b2 = 0;
					
					if (k1 == 0) {a1 = B[i].dm[1]; b1 = B[i].dm[2]; }
					else if(k1 == 1) {a1 = B[i].dm[0]; b1 = B[i].dm[2]; } 
					else if (k1 == 2) {a1 = B[i].dm[0]; b1 = B[i].dm[1]; }

					if (k2 == 0) {a2 = B[j].dm[1]; b2 = B[j].dm[2]; }
					else if (k2 == 1) {a2 = B[j].dm[0]; b2 = B[j].dm[2];}
					else if (k2 == 2) {a2 = B[j].dm[0]; b2 = B[j].dm[1]; }
					
					if (a1 < a2 && b1 < b2) G[i][k1][j][k2] = 1;
				}
			}
		}
	}
}

void printG() {
	for (int i = 1; i <= n; i++) {
		for (int k1 = 0; k1 <= 2; k1++) {
			cout << "i: " << i << " k1: " << k1 << " | ";
			for (int j = 1; j <= n; j++) {
				for (int k2 = 0; k2 <= 2; k2++) {
					cout << "j: " << j << " k2: " << k2 << " " << G[i][k1][j][k2] << " | ";
				}
			}
			cout << endl;
		}
	}
}
ll dp(int i, int k) {
	ll& ans = d[i][k];
	if (ans > 0) return ans;
	ans = B[i].dm[k];
	for (int j = 1; j <= n; j++) {
		for (int k2 = 0; k2 <= 2; k2++) {
			if (G[i][k][j][k2]) ans = max(ans, (ll)dp(j, k2) + B[i].dm[k]);
		}
	}
	return ans;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int cnt = 0;
	while (true) {
		memset(G, 0, sizeof(G));
		memset(d, 0, sizeof(d));
		cin >> n;
		if (!n) break;
		for (int i = 1; i <= n; i++) {
			ll a, b, c; cin >> a >> b >> c;
			// 将a,b,c调成a <= b <= c
			if (a > b) swap(a, b);
			if (b > c) swap(b, c);
			if (a > b) swap(a, b);
			B[i].dm[0] = a; B[i].dm[1] = b; B[i].dm[2] = c;
		}
		init();
		
		//printG();
		
		// DAG最长路模板
		ll ans = 0;
		for (int i = 1; i <= n; i++) {
			for (int k = 0; k <= 2; k++) {
				ans = max(ans, dp(i, k));
			}
		}
		cout << "Case " << ++cnt << ": maximum height = ";
		cout << ans << "\n";
	}
	return 0;
}