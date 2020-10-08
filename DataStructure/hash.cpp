//
// Created by logan on 2020/7/22.
//
// 1. Two Sum (Easy)
// 217. Contains Duplicate (Easy)
// 594. Longest Harmonious Subsequence (Easy)
// 128. Longest Consecutive Sequence (Hard)
#include <stack>
#include <deque>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
// 1. Two Sum (Easy)
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
                if (nums[end] == nums[end_next]) {
                    end++;
                    end_next++;
                } else break;
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

// 128. Longest Consecutive Sequence (Hard)
    int longestConsecutive(vector<int> &nums) {
        if (nums.empty()) return 0;
        map<int, int> m;
        int ans = 1;
        int longest = 1;
        for (vector<int>::iterator it = nums.begin(); it != nums.end(); it++) {
            m[*it] = 1;
        }
        map<int, int>::iterator m_it = m.begin();
        int last = m_it->first;
        m_it++;
        for (; m_it != m.end(); m_it++) {
            if ((m_it->first - last) == 1) {
                ans++;
            } else {
                longest = max(longest, ans);
                ans = 1;
            }
            last = m_it->first;
        }
        return max(longest, ans);
    }

    int twoSum_2(vector<int>& nums) {
        if (nums.empty()) return 0;
        map<int, int> m;
        int ans = 1;
        int longest = 1;
        for (int & num : nums) {
            m[num] = 1;
        }
        auto m_it = m.begin();
        int last = m_it->first;
        m_it++;
        for (; m_it != m.end(); m_it++) {
            if ((m_it->first - last) == 1) {
                ans++;
            } else {
                longest = max(longest, ans);
                ans = 1;
            }
            last = m_it->first;
        }
        return max(longest, ans);
    }
};

int main() {
    vector<int> vec;
    vec.push_back(3);
    vec.push_back(2);
    vec.push_back(4);
//    vec.push_back(3);
/*    vec.push_back(5);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(7);*/
    Solution solution;
    solution.twoSum_2(vec, 6);

}