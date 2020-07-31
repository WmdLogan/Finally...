//
// Created by logan on 2020/7/30.
//
// 461. Hamming Distance (Easy)
// 136. Single Number (Easy)
// 268. Missing Number (Easy)
// 260. Single Number III (Medium)

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
// 461. Hamming Distance (Easy)
    int hammingDistance(int x, int y) {
    /*    int x_y = x ^ y;
        int distance = 0;
        while (x_y != 0) {
            if (x_y % 2 == 1)
                distance += 1;
            x_y = x_y >> 1;
        }
        return distance;*/
        int x_y = x ^ y;
        int distance = 0;
        while (x_y != 0) {
            distance += 1;
            // remove the rightmost bit of '1'
            x_y = x_y & (x_y - 1);
        }
        return distance;

    }
// 136. Single Number (Easy)
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        for (int i = 0; i < nums.size(); ++i) {
            ans ^= nums[i];
        }
        return ans;
    }

// 268. Missing Number (Easy)
    int missingNumber(vector<int>& nums) {
        int len = nums.size();
        int ans = len;
        for (int i = 0; i < len; ++i) {
            ans ^= i;
            ans ^= nums[i];
        }
        return ans;
    }
// 260. Single Number III (Medium)
};