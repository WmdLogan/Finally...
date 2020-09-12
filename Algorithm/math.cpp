//
// Created by logan on 2020/9/10.
//
// 204. Count Primes (Easy)
//最大公约数，辗转相除法
//最小公倍数：两数的乘积除以最大公约数。
// 504. Base 7 (Easy)
// 405. Convert a Number to Hexadecimal (Easy)
// 168. Excel Sheet Column Title (Easy)
// 172. Factorial Trailing Zeroes (Easy)
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
// 204. Count Primes (Easy)
//埃拉托斯特尼筛法
public:
    int countPrimes(int n) {
        vector<bool> isPrim(n, true);
//标记每个数的整数倍为合数
        for (int i = 2; i * i < n; i++)
            if (isPrim[i])
                for (int j = i * i; j < n; j += i)
                    isPrim[j] = false;
//统计素数个数
        int count = 0;
        for (int i = 2; i < n; i++)
            if (isPrim[i]) count++;
        return count;
    }

//最大公约数，辗转相除法
    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }

//最小公倍数：两数的乘积除以最大公约数。
    int lcm(int a, int b) {
        return a * b / gcd(a, b);
    }

// 504. Base 7 (Easy)
    string convertToBase7(int num) {
        if (num == 0) return "0";
        string ans;
        short flag = 0;
        if (num < 0) {
            flag = 1;
            num = -num;
        }
        while (num != 0) {
            ans.push_back(char(num % 7 + '0'));
            num /= 7;
        }
        if (flag) ans += '-';
        reverse(ans.begin(), ans.end());
        return ans;
    }

// 405. Convert a Number to Hexadecimal (Easy)
    string toHex(int num) {
// 提取目标数的最后四位，然后将每个四位转化成十六进制
// 根据hex数组获取相应的数值，得到后存储拼接在结果r中，
        string ans;
        int p = -1;
        string hex[16] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f"};
        if (num == 0) return "0";
        else if (num < 0) p = 8;
        while (num) {
            if (p == 0) break;
            int c = 0;
            c = (num & 0x0000000f);
            ans = hex[c] + ans;//按顺序拼接
            num >>= 4;
            --p;
        }
        return ans;
    }

// 168. Excel Sheet Column Title (Easy)
    string convertToTitle(int n) {
        if (n == 0) return "";
        n--;
        return convertToTitle(n / 26) + (char) (n % 26 + 'A');
    }

// 172. Factorial Trailing Zeroes (Easy)
    int trailingZeroes(int n) {
        return n == 0 ? 0 : n / 5 + trailingZeroes(n / 5);
    }
};

int main() {
    Solution s;
    cout << s.convertToBase7(100);
    return 0;
};