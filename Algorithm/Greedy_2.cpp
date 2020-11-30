//
// Created by logan on 2020/8/5.
//
// 455. Assign Cookies (Easy)
// 435. Non-overlapping Intervals (Medium)
// 452. Minimum Number of Arrows to Burst Balloons (Medium)
// 406. Queue Reconstruction by Height(Medium)
// 121. Best Time to Buy and Sell Stock (Easy)
// 122. Best Time to Buy and Sell Stock II (Easy)
// 605. Can Place Flowers (Easy)
// 392. Is Subsequence (Medium)
// 665. Non-decreasing Array (Easy)
// 53. Maximum Subarray (Easy)
// 763. Partition Labels (Medium)
#include <vector>
#include <algorithm>
#include <list>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
// 455. 分发饼干
    int findContentChildren(vector<int> &g, vector<int> &s) {
        int ans = 0;
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int i = 0, j = 0;
        int s_len = s.size();
        int g_len = g.size();
        while (j < s_len && i < g_len) {
            if (g[i] <= s[j]) {
                ans++;
                i++;
                j++;
            } else {
                j++;
            }
        }
        return ans;
    }

// 435. 无重叠区间
    int eraseOverlapIntervals(vector<vector<int>> &intervals) {
        if (intervals.empty()) return 0;
        int ans = 0;
        sort(intervals.begin(), intervals.end(), [&](vector<int> &a, vector<int> &b) {
            if (a[1] == b[1]) return a[0] > b[0];
            return a[1] < b[1];
        });
        int last_right = intervals[0][1];
        for (int i = 1; i < intervals.size(); ++i) {
            if (last_right > intervals[i][0]) ans++;
            else last_right = intervals[i][1];
        }
        return ans;
    }

// 406. 根据身高重建队列
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), [](vector<int> &a, vector<int> &b) {
            return a[0] == b[0] ? a[1] < b[1] : a[0] > b[0];
        });
        list<vector<int>> ans;
        list<vector<int>>::iterator loc;
        for (auto m:people) {
            loc = ans.begin();
            advance(loc, m[1]);
            ans.insert(loc, m);
        }
        return vector<vector<int>>(ans.begin(), ans.end());
    }
};
