//
// Created by logan on 2020/8/21.
//
// 70. Climbing Stairs (Easy)
// 198. House Robber (Easy)
// 213. House Robber II (Medium)
#include <iostream>
#include <vector>

using namespace std;

class Solution {
// 70. Climbing Stairs (Easy)
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        int pre2 = 1, pre1 = 2;
        for (int i = 2; i < n; i++) {
            int cur = pre1 + pre2;
            pre2 = pre1;
            pre1 = cur;
        }
        return pre1;
    }

// 198. House Robber (Easy)
    int rob(vector<int> &nums) {
        //pre2 = dp[i-2], pre1 = dp[i-1]
        int pre2 = 0, pre1 = 0;
        for (int i = 0; i < nums.size(); i++) {
            int cur = max(pre2 + nums[i], pre1);
            pre2 = pre1;
            pre1 = cur;
        }
        return pre1;
    }

// 213. House Robber II (Medium)
//分两种情况，偷第一间不偷最后一间、偷最后一间不偷第一间
    int rob_2(vector<int> &nums) {
        int size = nums.size();
        if (size == 1) return nums[0];
        return max(rob_range(nums, 0, size - 2),
                   rob_range(nums, 1, size - 1));
    }

    int rob_range(vector<int> &nums, int start, int end){
        int dp_i_1 = 0, dp_i_2 = 0;
        int dp_i = 0;
        for (int i = end; i >= start; i--) {
            dp_i = max(dp_i_1, nums[i] + dp_i_2);
            dp_i_2 = dp_i_1;
            dp_i_1 = dp_i;
        }
        return dp_i;
    }
};