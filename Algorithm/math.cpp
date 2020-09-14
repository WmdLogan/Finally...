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
// 67. Add Binary (Easy)
// 415. Add Strings (Easy)
// 462. Minimum Moves to Equal Array Elements II (Medium)
// 169. Majority Element (Easy)
// 367. Valid Perfect Square (Easy)
// 326. Power of Three (Easy)
// 238. Product of Array Except Self (Medium)
#include <iostream>
#include <vector>
#include <algorithm>
#include <algorithm>
#include <map>

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

// 67. Add Binary (Easy)
    string addBinary(string a, string b) {
        int al = a.size(), bl = b.size();
        while (al < bl) //让两个字符串等长，若不等长，在短的字符串前补零，否则之后的操作会超出索引
        {
            a = '0' + a;
            ++al;
        }
        while (al > bl) {
            b = '0' + b;
            ++bl;
        }
        for (int j = a.size() - 1; j > 0; --j) //从后到前遍历所有的位数，同位相加
        {
            a[j] = a[j] - '0' + b[j];
            if (a[j] >= '2') //若大于等于字符‘2’，需要进一
            {
                a[j] = (a[j] - '0') % 2 + '0';//有可能是1、2
                a[j - 1] = a[j - 1] + 1;
            }
        }
        a[0] = a[0] - '0' + b[0]; //将ab的第0位相加
        if (a[0] >= '2') //若大于等于2，需要进一
        {
            a[0] = (a[0] - '0') % 2 + '0';
            a = '1' + a;
        }
        return a;
    }

// 415. Add Strings (Easy)
    string addStrings(string num1, string num2) {
        int i = num1.length() - 1, j = num2.length() - 1, add = 0;
        string ans = "";
        while (i >= 0 || j >= 0 || add != 0) {
            int x = i >= 0 ? num1[i] - '0' : 0;
            int y = j >= 0 ? num2[j] - '0' : 0;
            int result = x + y + add;
            ans.push_back('0' + result % 10);
            add = result / 10;
            i -= 1;
            j -= 1;
        }
        // 计算完以后的答案需要翻转过来
        reverse(ans.begin(), ans.end());
        return ans;
    }

// 462. Minimum Moves to Equal Array Elements II (Medium)
    int minMoves2(vector<int> &nums) {
        int len = nums.size();
        sort(nums.begin(), nums.end());
        int mid = nums[len / 2];
        int ans = 0;
        for (int a:nums) {
            ans += abs(a - mid);
        }
        return ans;
    }

// 169. Majority Element (Easy)
    int majorityElement(vector<int> &nums) {
        int ans = 0, len = nums.size() / 2;
        map<int, int> m;
        for (int a:nums) m[a]++;
        for (auto a:m) {
            if (a.second > len) {
                ans = a.first;
            }
        }
        return ans;
    }

// 367. Valid Perfect Square (Easy)
    bool isPerfectSquare(int num) {
//平方数1,4,9,16间隔为（3、5、7），为等差数列
        int root = 1;
        while (num > 0) {
            num -= root;
            root += 2;
        }
        return num == 0;
    }

// 326. Power of Three (Easy)
    bool isPowerOfThree(int n) {
        return n > 0 && 1162261467 % n == 0;        //1162261467为int型范围内最大的3的幂
    }

// 238. Product of Array Except Self (Medium)
    vector<int> productExceptSelf(vector<int> &nums) {
        int length = nums.size();
        vector<int> answer(length);

        // answer[i] 表示索引 i 左侧所有元素的乘积
        // 因为索引为 '0' 的元素左侧没有元素， 所以 answer[0] = 1
        answer[0] = 1;
        for (int i = 1; i < length; i++) {
            answer[i] = nums[i - 1] * answer[i - 1];
        }

        // R 为右侧所有元素的乘积
        // 刚开始右边没有元素，所以 R = 1
        int R = 1;
        for (int i = length - 1; i >= 0; i--) {
            // 对于索引 i，左边的乘积为 answer[i]，右边的乘积为 R
            answer[i] = answer[i] * R;
            // R 需要包含右边所有的乘积，所以计算下一个结果时需要将当前值乘到 R 上
            R *= nums[i];
        }
        return answer;
    }
};

int main() {
    Solution s;
    cout << s.convertToBase7(100);
    return 0;
};