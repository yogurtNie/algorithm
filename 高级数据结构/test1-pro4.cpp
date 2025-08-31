//
// Created by 12472 on 25-6-12.
//
#include<bits/stdc++.h>
using namespace std;
int main()
{
    set<int> s;
    int m, q; cin >> m >> q;
    for (int i = 0; i < q; i++)
    {
        char c; cin >> c;
        if (c == 'M')
        {
            int x; cin >> x;
            s.insert(x);
        }
        else if (c == 'C')
        {
            int l, r; cin >> l >> r;
            auto it = s.lower_bound(l);     // 找到比l小的最大的一个数
            vector<int> tmp;
            int cnt = 0;
            for (; it != s.end(); ++it)
            {
                if (*it > r) break;
                tmp.push_back(*it);
                cnt++;
            }

            cout << cnt << endl;

            for (int t : tmp) s.erase(t);
        }
    }
}