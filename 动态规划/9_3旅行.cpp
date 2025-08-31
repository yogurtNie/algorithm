#include<bits/stdc++.h>
using namespace std;
/*题目：有n个点的坐标，按照x递增顺序给出
设计一条路线，从最左边的点出发，走到最右边的点之后再返回
要求除了最左点和最右点之外每个点恰好经过一次，且路径总长度最小
将问题转换成：有两个人同时从最左边出发，走两条不重复的路到达最右边

1. 定义状态方程：
	迭代过程 —— d(i, j)表示第一个人走到i，第二个人走到j，可以吗？
	好像不行，因为这样没有办法知道这个状态是否会重复
	—— d(i, j)表示1 ~ max(i, j)全部走过，且两人一个人在i，一个人在j，可以吗？
	有点瑕疵，因为显然，d(i, j) == d(j, i)
	—— 规定在状态中i > j，可以规避这种情况，这样不管是哪个人下一步都只能转移到i+1, i+2...
	但是，如果某个人走到了i+2，但是i+1没走，怎么办？
	—— 规定这种情况不许出现，也就是严格定义转移结果：d(i, j)只能转移到d(i+1, j) / d(i, i+1) -> d(i+1, i)
2. 于是状态转移方程也能确定下来：d(i, j) = max(d(i+1, j), d(i+1, i))
3. 边界：需要从终点倒推，终点的计算方程为：d(n-1, j) = dist(n-1, n) + dist(j, n), 还有一步到终点的时候，
	这个状态表示所有的点都走过了，因此只需要直接从n-1和j走到n即可
4. 结果：最终结果应该是d(2, 1) + dist(1, 2)

*/
const int N = 1e3 + 10;
struct point{
	int x, y;
}g[N];
double dist(int i, int j) {
	double ans = sqrt((g[i].x - g[j].x) * (g[i].x - g[j].x) + (g[i].y - g[j].y) * (g[i].y - g[j].y));
	return ans;
}
double d[N][N];
int n;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	while (cin >> n) {
		memset(d, 0.0, sizeof(d));
		for (int i = 1; i <= n; i++) {
			cin >> g[i].x >> g[i].y;
		}	
		if (n == 2) {
			printf("%.2f\n", 2 * dist(1, 2));
			continue;
		}
		
		/*for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j)
                d[i][j] = 1e18;*/
		
		// 初始化d数组
		for (int j = 1; j < n - 1; j++) {
			d[n-1][j] = dist(n, n - 1) + dist(n, j);
		}
		
		// 递推过程
		for (int i = n - 2; i >= 1; i--) {
			for (int j = 1; j < i; j++) {
				d[i][j] = min(d[i + 1][j] + dist(i, i + 1), d[i + 1][i] + dist(j, i + 1));
			}
		}
		
		double ans = d[2][1] + dist(1, 2);
		printf("%.2f\n", ans);
		//cout << dist(1, 2) << endl;
	}
	return 0;
	
	
}

