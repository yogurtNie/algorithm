//
// Created by 12472 on 25-6-10.
//
// 本题最核心的思想就是，如何将一个问题用bfs展开
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    // 建一个图
    vector<vector<int>> G;
    string sub(string& a, string& b)
    {
        string res;
        int i = 0, j = 0, index = 0;
        while (i < a.length() && j < b.length())
        {
            if (a[i] == b[j])
            {
                i++, j++;       // 保留当前字符
            }
            else if (a[i] > b[j])   // 若当前字符比贴纸的字符大，说明目前贴纸无用
            {
                j++;
            }
            else if (a[i] < b[j])   // 如果当前字符比贴纸字符小，说明贴纸无法抵消这个字符
            {
                res += a[i];
                i++;
            }
        }
        while (i < a.length())
        {
            res += a[i++];
        }
        return res;
    }
    int minStickers(vector<string>& stickers, string target) {
        G.resize(27);
        for (int i = 0; i < stickers.size(); i++) {
            // 排好序
            sort(stickers[i].begin(), stickers[i].end());
            // 26个英文字母，每一个作为起点建原始图，用于前缀优化（即先处理这个字符串最前面的，先选能处理这个的）
            for (int j = 0; j < stickers[i].size(); j++)
            {
                if (j == 0 || stickers[i][j] != stickers[i][j-1])
                {
                    G[stickers[i][j] - 'a'].push_back(i);       // 对于这个字母来说，这个贴纸可以解决它
                }
            }
        }

        // 有了初始的图之后，可以开始bfs
        queue<string> q;
        set<string> s;
        sort(target.begin(), target.end());
        q.push(target);
        s.insert(target);       // 用于标识是否到达过这个状态
        int level = 0;          // 从第一层开始
        while (!q.empty())      // 按层来处理
        {
            int size = q.size();
            level++;
            // 来到下一层
            for (int i = 0; i < size; i++)
            {
                string now = q.front(); q.pop();
                int index = now[0] - 'a';
                for (int j = 0; j < G[index].size(); j++)
                {
                    string next = sub(now, stickers[G[index][j]]);
                    if (next == "") return level;
                    if (s.count(next) == 0)
                    {
                        q.push(next);
                        s.insert(next);
                    }
                }
            }
        }
        return -1;
    }
};

int main()
{
    vector<string> stickers = {"with","example","science"};
    Solution sol;
    cout << sol.minStickers(stickers, "thehat") << endl;
    return 0;
}