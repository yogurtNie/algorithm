//
// Created by 12472 on 25-9-4.
//
// 力扣2092 找出知晓秘密的所有专家
/*
 * 给你一个整数 n ，表示有 n 个专家从 0 到 n - 1 编号。另外给你一个下标从 0 开始的二维整数数组 meetings ，其中 meetings[i] = [x_i, y_i, time_i] 表示专家 x_i 和专家 y_i 在时间 time_i 要开一场会。一个专家可以同时参加 多场会议 。最后，给你一个整数 firstPerson 。
 * 专家 0 有一个 秘密 ，最初，他在时间 0 将这个秘密分享给了专家 firstPerson 。接着，这个秘密会在每次有知晓这个秘密的专家参加会议时进行传播。更正式的表达是，每次会议，如果专家 x_i 在时间 time_i 时知晓这个秘密，那么他将会与专家 y_i 分享这个秘密，反之亦然。
 * 秘密共享是 瞬时发生 的。也就是说，在同一时间，一个专家不光可以接收到秘密，还能在其他会议上与其他专家分享。
 * 在所有会议都结束之后，返回所有知晓这个秘密的专家列表。你可以按 任何顺序 返回答案。
2 <= n <= 105
1 <= meetings.length <= 105
meetings[i].length == 3
0 <= xi, yi <= n - 1
xi != yi
1 <= time_i <= 105
1 <= firstPerson <= n - 1
 */
// https://leetcode.cn/problems/find-all-people-with-secret/description/
// 我的疑问是：如何在持续的合并之下确定哪个集合是知晓秘密的集合，以及如何将时间因素纳入考量？
// 时间因素怎么考量：当前时刻过去之后，将没有纳入秘密集团的人组成的集合解散，重新回归自由身
// 下一个疑问：这样势必会重复很多不必要的遍历操作，怎么优化？
// 引入新的技巧 —— 打标签，如果已经纳入秘密集团，则flag标为True，否则拆掉
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
bool cmp(vector<int>& a, vector<int>& b)        // cmp函数无法定义在类内，因为会隐含this指针
{
    return a[2] < b[2];
}
class Solution
{
public:
    int parent[N];
    int flag[N];
    void init(int n)
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            flag[i] = 0;
        }
    }
    int find(int x)
    {
        return x == parent[x] ? x : parent[x] = find(parent[x]);
    }
    bool IsSameSet(int a, int b)
    {
        return find(a) == find(b);
    }
    void unite(int a, int b)
    {
        int pa = find(a), pb = find(b);
        if (pa != pb)
        {
            // if (flag[pa] || flag[pb])
            //     flag[pa] = flag[pb] = 1;
            // parent[pa] = pb;
            parent[pa] = pb;  // 将pb挂靠在pa下
            flag[pb] |= flag[pa];   // 如果pa是知道秘密的，则pb一定也知道；如果pa不知道，则pb维持原状
        }
    }
    void recover(int start, int end, vector<vector<int>>& meetings)
    {
        for (int i = start; i < end; i++)
        {
            int l = meetings[i][0], r = meetings[i][1];
            if (!flag[find(l)])   // 如果不是秘密集团的(记住这里很容易错，是找根节点而非找本身)
                parent[l] = l; // 则需要恢复自由身
            if (!flag[find(r)])
                parent[r] = r;
        }
    }
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        init(n);
        flag[0] = 1;
        parent[firstPerson] = 0;
        sort(meetings.begin(), meetings.end(), cmp);    // 按时间排序
        int l = 0, r = 0;
        for (; r < meetings.size(); l = r)
        {
            while (r < meetings.size() && meetings[r][2] == meetings[l][2])        // 当还在这个时间段中的时候
            {
                // 进行合并工作
                int expect1 = meetings[r][0], expect2 = meetings[r][1];
                unite(expect1, expect2);
                r++;
            }
            // 如果当前时间段已经结束，则复原未纳入秘密集团的专家
            recover(l, r, meetings);
        }
        vector<int> ans;
        for (int i = 0; i < n; i++)
        {
            if (flag[find(i)])
                ans.push_back(i);
        }
        return ans;
    }
};

int main()
{
    vector<vector<int>> meetings = {{1,4,3},{0,4,3}};
    Solution sol;
    vector<int> ans =  sol.findAllPeople(5, meetings, 3);
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << " ";
    return 0;
}