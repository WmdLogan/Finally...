//
// Created by logan on 2020/7/30.
//
// 461. Hamming Distance (Easy)
// 136. Single Number (Easy)
// 268. Missing Number (Easy)
// 260. Single Number III (Medium)
// 190. Reverse Bits (Easy)

#include <iostream>
#include <vector>
#include <map>

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
    vector<int> singleNumber_t(vector<int>& nums) {
        int ans = 0;
        for (auto e :nums) {
            ans ^= e;
        }
        ans &= -ans;
        vector<int> re(2, 0);
        for (auto e :nums) {
           if ( (e & ans) == 0) re[0] ^= e;
           else re[1] ^= e;
        }
        return re;
    }
// 190. Reverse Bits (Easy)
    uint32_t reverseBits(uint32_t n) {
        n = (n >> 16) | (n << 16);
        n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
        n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
        n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
        n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
        return n;
    }

};