//
// Created by logan on 2020/7/30.
//
// 461. Hamming Distance (Easy)
// 136. Single Number (Easy)
// 268. Missing Number (Easy)
// 260. Single Number III (Medium)
// 190. Reverse Bits (Easy)
// 231. Power of Two (Easy)
// 342. Power of Four (Easy)
// 693. Binary Number with Alternating Bits (Easy)
// 476. Number Complement (Easy)
// 371. Sum of Two Integers (Easy)
// 318. Maximum Product of Word Lengths (Medium)
// 338. Counting Bits (Medium)
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

class Solution {
public:
// 461. Hamming Distance (Easy)
    int hammingDistance(int x, int y) {
        bit_and<int> b_and;
        int ans = 0;
        while (x || y) {
            if (b_and.operator()(x, 1) != b_and.operator()(y, 1)) {
                ans++;
            }
            x >>= 1;
            y >>= 1;
        }
        return ans;
    }

// 136. Single Number (Easy)
    int singleNumber(vector<int> &nums) {
        int ans = 0;
        for (int &num : nums) {
            ans ^= num;
        }
        return ans;
    }

// 268. Missing Number (Easy)
    int missingNumber(vector<int> &nums) {
        int len = nums.size();
        int ans = len;
        for (int i = 0; i < len; ++i) {
            ans ^= i;
            ans ^= nums[i];
        }
        return ans;
    }

// 260. Single Number III (Medium)
    vector<int> singleNumber_t(vector<int> &nums) {
        vector<int> ans(2, 0);
        int temp = 0;
        for (int &num : nums) {
            temp ^= num;
        }
        temp &= (-temp);
        for (int &num : nums) {
            if ((num & temp) == 0) {
                ans[0] ^= num;
            } else {
                ans[1] ^= num;
            }
        }
        return ans;
    }

// 190. Reverse Bits (Easy)
    uint32_t reverseBits(uint32_t n) {
        uint32_t ans = 0;
        for (int i = 0; i < 32; ++i) {
            ans <<= 1;
            ans += n & 1;
            n >>= 1;
        }
        return ans;
    }

// 231. Power of Two (Easy)
    bool isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;
    }

// 342. Power of Four (Easy)
    bool isPowerOfFour(int num) {
        return num > 0 && (num & (num - 1)) == 0 && (num & 0xaaaaaaaa) == 0;
    }

// 693. Binary Number with Alternating Bits (Easy)
    bool hasAlternatingBits(int n) {
//如果是交替二进制，则错位异或为全1
        uint32_t temp = n ^(n >> 1);
        temp++;
        return (temp & (temp - 1)) == 0;
    }

// 476. Number Complement (Easy)
    int findComplement(int num) {

    }

// 371. Sum of Two Integers (Easy)
    int getSum(int a, int b) {

    }

// 318. Maximum Product of Word Lengths (Medium)
    int maxProduct(vector<string> &words) {

    }

// 338. Counting Bits (Medium)
    vector<int> countBits(int num) {

    }


};

int main() {
    Solution s;
    cout << s.hasAlternatingBits(10) << endl;
}