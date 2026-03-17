//
// Created by 12472 on 25-12-7.
//
/*
* 珂珂喜欢吃香蕉。这里有 n 堆香蕉，第 i 堆中有 piles[i] 根香蕉。警卫已经离开了，将在 h 小时后回来。
珂珂可以决定她吃香蕉的速度 k （单位：根/小时）。每个小时，她将会选择一堆香蕉，从中吃掉 k 根。如果这堆香蕉少于 k 根，她将吃掉这堆的所有香蕉，然后这一小时内不会再吃更多的香蕉。
珂珂喜欢慢慢吃，但仍然想在警卫回来前吃掉所有的香蕉。
返回她可以在 h 小时内吃掉所有香蕉的最小速度 k（k 为整数）。
 */
// 最小速度
// 速度最小、最大是什么范围？
// e.g. piles = [3,6,7,11] 速度最小可以是1
// 速度最大是当前数组中最大的值，因为比它更大的其实效果一样
// [0, maxn]
// 有没有单调性？ -- 有，当速度变大的时候，小时数一定小于等于当前小时
// 所以只要有一个答案为n，可以满足警卫不会抓到，比其大的一定都可以满足
// 可以直接开始二分了。如果当前答案满足，去左侧的mid找，如果当前答案不满足，去右侧的mid找
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int l = 1, r = 0;
        for (int i = 0; i < piles.size(); i++)
        {
            if (r < piles[i]) r = piles[i];
        }
        int ans = 0;
        int m = 0;
        while (l <= r)
        {
            m = l + ((r - l) >> 1);         // 等价于 (r + l) / 2
            if ((f(piles, m)) <= h)         // changeable，这里是能够满足，我们去左侧
            {
                ans = m;                    // l...  m...r
                r = m - 1;                  // l..m-1
            }
            else                            // 不达标
            {
                l = m + 1;
            }
        }
        return ans;
    }

    int f(vector<int>& piles, int speed)
    {
        int time = 0;
        for (int i = 0; i < piles.size(); i++)
        {
            time += (piles[i] + speed - 1) / speed;
        }
        return time;
    }
};

int main()
{
    Solution s;
    vector<int> piles{3, 6, 7, 11};
    cout << s.minEatingSpeed(piles, 8);
    return 0;
}