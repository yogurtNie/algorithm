//
// Created by 12472 on 25-9-2.
//
// https://www.nowcoder.com/practice/e7ed657974934a30b2010046536a5372
// 并查集的实现
#include<iostream>
using namespace std;
const int N = 1e6 + 10;
int parent[N];
int Size[N];
class UnionFind
{
public:
  void init(int n)
  {
    for (int i = 0; i < n; i++)
    {
      parent[i] = i;  // 每个节点的根节点都是本身
      Size[i] = 1;    // 初始大小为1
    }
  }
  int find(int x)
  {
    return x == parent[x] ? x : parent[x] = find(parent[x]);
  }
  bool isSameSet(int a, int b)
  {
    return find(a) == find(b);
  }
  void unionSet(int a, int b)
  {
    int pa = find(a), pb = find(b);
    if (pa != pb)
    {
      if (Size[pa] > Size[pb])
      {
        Size[pa] += Size[pb];
        parent[pb] = pa;
      }
      else
      {
        Size[pb] += Size[pa];
        parent[pa] = pb;
      }
    }
  }
};

int main()
{
  UnionFind uf;
  int n, m;
  cin >> n >> m;
  uf.init(n + 1);
  int opt, x, y;
  for (int i = 0; i < m; i++)
  {
    cin >> opt >> x >> y;
    if (opt == 1)
    {
      if (uf.isSameSet(x, y))
        cout << "Yes\n";
      else
        cout << "No\n";
    }
    else if (opt == 2)
    {
      uf.unionSet(x, y);
    }
  }
  return 0;
}