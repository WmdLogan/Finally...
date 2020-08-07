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

// 452. Minimum Number of Arrows to Burst Balloons (Medium)
    static bool compare_balloon(vector<int> &a, vector<int> &b) {
        return a[0] < b[0];
    }

    int findMinArrowShots(vector<vector<int>> &points) {
        if (points.empty()) return 0;
        int ans = 1;
        sort(points.begin(), points.end(), compare_balloon);
        int right = points[0][1];
        for (auto m:points) {
            if (m[1] <= right) {
                //左右点都在边界中,更新右边界
                right = m[1];
                //左点在右点不在，右边界不变
            }
                //左右点都不在
            else if (m[0] > right) {
                ans++;
                right = m[1];
            }
        }
        return ans;
    }

// 406. Queue Reconstruction by Height(Medium)
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

// 121. Best Time to Buy and Sell Stock (Easy)
    int maxProfit(vector<int> &prices) {
        if (prices.empty()) return 0;
        int min_price = prices[0], max_profit = 0;
        for (int price: prices) {
            max_profit = max(max_profit, price - min_price);
            min_price = min(price, min_price);
        }
        return max_profit;
    }

// 122. Best Time to Buy and Sell Stock II (Easy)
    int maxProfit_2(vector<int> &prices) {
        int len = prices.size();
        if (len == 0) return 0;
        int ans = 0;
        int single_profit = prices[0];
        for (int i = 0; i < len - 1; ++i) {
            if (prices[i] >= prices[i + 1]) {//下一天价格大于今天价格，卖出，买新的
                ans += (prices[i] - single_profit);
                single_profit = prices[i + 1];
            }
        }
        return prices[len - 1] > single_profit ? ans + prices[len - 1] - single_profit : ans;
    }

// 605. Can Place Flowers (Easy)
    bool canPlaceFlowers(vector<int> &flowerbed, int n) {
        int len = flowerbed.size();
        int i = 0;
        int left = 0;//记录当前位置左边是否有花
        for (; i < len - 1; i++) {
            if (flowerbed[i] == 0 && left == 0 && flowerbed[i + 1] == 0) {
                //当前位置空,左边空,右边空，种花
                n--;
                if (n <= 0) return true;
                left = 1;
            } else left = flowerbed[i];
        }
        if (n == 0 || n == 1 && left == 0 && flowerbed[i] == 0) return true;
        return false;
    }

// 392. Is Subsequence (Medium)
    bool isSubsequence(string s, string t) {
        int s_len = s.length();
        int t_len = t.length();
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

// 665. Non-decreasing Array (Easy)
    bool checkPossibility(vector<int> &nums) {
        int count = 0;
        for (int i = 0; i < nums.size() - 1; ++i) {
            if (nums[i] > nums[i + 1]) {
                if (i == 0 || nums[i - 1] <= nums[i + 1]) {//第一个结点不满足
                    count++;
                    if (count == 2) return false;
                } else {
                    //其他情况，下一个结点等于当前结点
                    count++;
                    nums[i + 1] = nums[i];
                    if (count == 2) return false;
                }
            }
        }
        return true;
    }

// 53. Maximum Subarray (Easy)
    int maxSubArray(vector<int>& nums) {
        int ans = nums[0];
        int cur = nums[0];
        int len = nums.size();
        for (int i = 1; i < len; ++i) {
            cur = max(nums[i], nums[i] + cur);
            ans = max(ans, cur);
        }
        return ans;
    }

// 763. Partition Labels (Medium)
    vector<int> partitionLabels(string S) {
        vector<int> last(26);//字母最后一次出现的下标
        for (int i = 0; i < S.length(); ++i)
            last[S[i] - 'a'] = i;

        int j = 0, anchor = 0;//当前区间首尾
        vector<int> ans;
        for (int i = 0; i < S.length(); ++i) {
            j = max(j, last[S[i] - 'a']);//获得当前字母最后一次出现的位置
            if (i == j) {//当前字母到达了最后一次出现的位置
                ans.push_back(i - anchor + 1);
                anchor = i + 1;
            }
        }
        return ans;
    }
};

int main() {
    string s = "ababcbacadefegdehijhklij";
    Solution solution;
    solution.partitionLabels(s);
}
