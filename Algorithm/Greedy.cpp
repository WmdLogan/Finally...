//
// Created by logan on 2020/8/5.
//
// 455. Assign Cookies (Easy)
// 435. Non-overlapping Intervals (Medium)
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
// 455. Assign Cookies (Easy)
    int findContentChildren(vector<int> &g, vector<int> &s) {
        int ans = 0;
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int i = 0, j = 0;
        int s_len = s.size();
        int g_len = g.size();
        while (j < s_len && i < g_len) {
            if (g[i] <= s[j]) {//胃口和饼干尺寸一样或者胃口比饼干尺寸小
                ans++;
                i++;
                j++;
            } else {//胃口比饼干尺寸大
                j++;
            }
        }
        return ans;
    }

// 435. Non-overlapping Intervals (Medium)
    static bool compare(vector<int> &a, vector<int> &b) {
        if (a[1] == b[1]) return a[0] > b[0];
        return a[1] < b[1];
    }

    int eraseOverlapIntervals(vector<vector<int>> &intervals) {
        int size = intervals.size();
        if (size == 0) return 0;
        sort(intervals.begin(), intervals.end(), compare);
        int ans = 1;//区间数量
        int right = intervals[0][1];//右边界
        for (auto m:intervals) {
            if (m[0] >= right) {//下一个范围的左边界在上一个范围右边
                ans++;//区间数量+1
                right = m[1];//更新区间右边界
            }
        }
        return size - ans;
    }
};

