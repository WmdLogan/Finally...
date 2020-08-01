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
        /*    int x_y = x ^ y;
            int distance = 0;
            while (x_y != 0) {
                if (x_y % 2 == 1)
                    distance += 1;
                x_y = x_y >> 1;
            }
            return distance;*/
        int x_y = x ^y;
        int distance = 0;
        while (x_y != 0) {
            distance += 1;
            // remove the rightmost bit of '1'
            x_y = x_y & (x_y - 1);
        }
        return distance;

    }

// 136. Single Number (Easy)
    int singleNumber(vector<int> &nums) {
        int ans = 0;
        for (int i = 0; i < nums.size(); ++i) {
            ans ^= nums[i];
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
        int ans = 0;
        for (auto e :nums) {
            ans ^= e;
        }
        ans &= -ans;
        vector<int> re(2, 0);
        for (auto e :nums) {
            if ((e & ans) == 0) re[0] ^= e;
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

// 231. Power of Two (Easy)
    bool isPowerOfTwo(int n) {
        if (n == 0) return false;
        long x = n;
        return (x & (x - 1)) == 0;
    }

// 342. Power of Four (Easy)
    bool isPowerOfFour(int num) {
        if (num <= 0) return false;
        return (num & (num - 1)) == 0 && (num & 0xaaaaaaaa) == 0;
    }

// 693. Binary Number with Alternating Bits (Easy)
    bool hasAlternatingBits(int n) {
        n = (n ^ (n >> 1));
        return (n & ((long) n + 1)) == 0;
    }

// 476. Number Complement (Easy)
    int findComplement(int num) {
        long x = num;
        int count = 1;
        while (x >> 1 > 0) {
            count++;
            x = x >> 1;
        }

        long tmp = 1 << count;
        long res = num ^(tmp - 1);
        return res;
    }

// 371. Sum of Two Integers (Easy)
    int getSum(int a, int b) {
        while (b) {
            auto carry = ((unsigned int) (a & b)) << 1;
            a ^= b;
            b = carry;
        }
        return a;
    }

// 318. Maximum Product of Word Lengths (Medium)
    int maxProduct(vector<string> &words) {
        int len = words.size();
// 每个字符串的掩码数组
        vector<int> mask(len, 0);
//每个字符串的长度数组
        vector<int> s_len(len, 0);
        int i = 0;
        for (auto str : words) {
            s_len[i] = str.size();//每个字符串的长度
            for (auto c:str) {//构造每个字符串的掩码
                int loc = (int) c - (int) 'a';
                mask[i] |= 1 << loc;
            }
            i++;
        }
//&掩码，为0说明没有公共字母，算长度乘积
        int ans = 0;
        for (i = 0; i < len; i++) {
            for (int j = i + 1; j < len; j++) {
                if ((mask[i] & mask[j]) == 0) {
                    ans = max(ans, s_len[i] * s_len[j]);
                }
            }
        }
        return ans;
    }

// 338. Counting Bits (Medium)
    vector<int> countBits(int num) {
        vector<int> ret(num + 1, 0);
        for (int i = 1; i <= num; i++) {
            ret[i] = ret[i & (i - 1)] + 1;
        }
        return ret;
    }

    int one_number(int n) {
        int sum = 0;
        while (n != 0) {
            sum++;
            n &= (n - 1);
        }
        return sum;
    }


};

int main() {
    Solution s;
    vector<string> vector;
    vector.push_back("abcde");
    vector.push_back("fghij");

    cout << s.maxProduct(vector);

}