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
    vector<vector<int>> reconstructQueue(vector<vector<int>> &people) {
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

// 121. 买卖股票的最佳时机
    int maxProfit(vector<int> &prices) {
        if (prices.empty()) return 0;
        int ans = 0;
        int lowest = prices[0];
        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] > lowest) ans = max(ans, prices[i] - lowest);
            else lowest = prices[i];
        }
        return ans;
    }

// 122. 买卖股票的最佳时机 II
    int maxProfit_2(vector<int> &prices) {
        int len = prices.size();
        int ans = 0;
        int single_profit = prices[0];
        for (int i = 0; i < len - 1; ++i) {
            if (prices[i] >= prices[i + 1]) {
                //下一天价格低于今天，卖出
                ans += (prices[i] - single_profit);
                single_profit = prices[i + 1];
            }
        }
        return prices[len - 1] > single_profit ? ans + prices[len - 1] - single_profit : ans;
    }

// 605. 种花问题
    bool canPlaceFlowers(vector<int> &flowerbed, int n) {
        int left = 0;//当前位置左侧是否有花
        int len = flowerbed.size();
        for (int i = 0; i < (len - 1) && n > 0; ++i) {
            if (left == 0 && flowerbed[i] == 0 && flowerbed[i + 1] == 0) {
                n--;
                left = 1;//种花
                continue;
            }
            left = flowerbed[i];
        }
        if (left == 0 && flowerbed[len] == 0) n--;
        return n < 1;
    }

// 392. 判断子序列
    bool isSubsequence(string s, string t) {
        int s_len = s.size();
        int t_len = t.size();
        int i = 0, j = 0;
        while (i < s_len && j < t_len) {
            if (s[i] == t[j]) {
                i++;
                j++;
            } else {
                j++;
            }
        }
        return i == s_len;
    }

// 665. 非递减数列
    bool checkPossibility(vector<int> &nums) {
        int count = 0;
        for (int i = 0; i < nums.size() - 1; ++i) {
            if (nums[i] > nums[i + 1]) {//降序
                //下一个结点值不需要改变
                if (i == 0 || nums[i - 1] <= nums[i + 1]) {
                    count++;
                } else {
                //下一个结点值等于当前结点
                    count++;
                    nums[i + 1] = nums[i];
                }
            }
        }
        return count < 2;
    }

// 53. 最大子序和
    int maxSubArray(vector<int>& nums) {
        int temp = nums[0];
        int ans = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            temp = max(nums[i] + temp, nums[i]);
            ans = max(temp, ans);
        }
        return ans;
    }

// 763. 划分字母区间
    vector<int> partitionLabels(string S) {
        
    }
};
