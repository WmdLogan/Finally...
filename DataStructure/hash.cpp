//
// Created by logan on 2020/7/22.
//
// 1. Two Sum (Easy)
#include <stack>
#include <deque>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
// 1. Two Sum (Easy)
// 217. Contains Duplicate (Easy)
// 594. Longest Harmonious Subsequence (Easy)
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        vector<pair<int, int>> vec;
        int len = nums.size();
        for (int i = 0; i < len; ++i) {
            vec.push_back(make_pair(nums[i], i));
        }
        sort(vec.begin(), vec.end());
        vector<int> ans(2);
        int front = 0;
        int last = len - 1;
        while (front < last) {
            int temp_sum = vec[front].first + vec[last].first;
            if (temp_sum == target) {
                ans[0] = vec[front].second;
                ans[1] = vec[last].second;
                return ans;
            } else if (temp_sum < target) {
                front++;
            } else {
                last--;
            }
        }
        return ans;
    }

// 217. Contains Duplicate (Easy)
    bool containsDuplicate(vector<int> &nums) {
/*        set<int> s;
        int len = nums.size();
        for (int i = 0; i < len; ++i) {
            s.insert(nums[i]);
        }
        return !(s.size() == len);*/
        int len = nums.size() - 1;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < len; ++i) {
            if (nums[i] == nums[i + 1]) {
                return true;
            }
        }
        return false;
    }

// 594. Longest Harmonious Subsequence (Easy)
    int findLHS(vector<int> &nums) {
/*        map<int, int> m;
        int LHS = 0;
        int len = nums.size();
        if (len == 0) return 0;
        for (int i = 0; i < len; ++i) {
            m[nums[i]]++;
        }
        map<int, int>::iterator it = m.begin();
        map<int, int>::iterator it_next = ++m.begin();
        for (; it_next != m.end(); it++, it_next++) {
            if ((it_next->first - it->first) == 1) {
                int sum = it->second + it_next->second;
                LHS = sum > LHS ? sum : LHS;
            }
        }
        return LHS;*/
        sort(nums.begin(), nums.end());
        int start = 0, mid = 0, end = 0;
        int sum, LHS = 0;
        int len = nums.size();
        while (start < len - 1) {
            if (nums[start] == nums[start + 1]) start++;
            else break;
        }
        if (start == len - 1) return 0;
        mid = start + 1;
        start = 0;
        while (mid < len) {
            end = mid;
            int end_next = end + 1;
            while (end_next < len) {
                if (nums[end] == nums[end_next]){
                    end++;
                    end_next++;
                }
                else break;
            }
            if ((nums[end] - nums[start]) == 1) {
                sum = end - start + 1;
                LHS = max(sum, LHS);
            }
            start = mid;
            mid = end + 1;
        }
        return LHS;
    }
};

int main() {
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(1);
    vec.push_back(3);
/*    vec.push_back(5);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(7);*/
    Solution solution;
    cout << solution.findLHS(vec);

}