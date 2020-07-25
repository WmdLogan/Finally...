//
// Created by logan on 2020/7/22.
//
// 242. Valid Anagram (Easy)
// 409. Longest Palindrome (Easy)
// 205. Isomorphic Strings (Easy)
// 5. Longest Palindromic Substring (Medium)
// 647. Palindromic Substrings (Medium)
// 9. Palindrome Number
// 696. Count Binary Substrings (Easy)

#include <stack>
#include <deque>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
// 242. Valid Anagram (Easy)
    bool isAnagram(string s, string t) {
        unordered_map<char, int> m;
        int flag1 = 0, flag2 = 0;
        for (char c:s) {
            flag1++;
            m[c]++;
        }
        for (char c:t) {
            flag2++;
            if (m[c] != 0) {
                m[c]--;
            } else {
                return false;
            }
        }
        if (flag1 != flag2) return false;
        return true;
    }

// 409. Longest Palindrome (Easy)
    int longestPalindrome(string s) {
        int len = s.size();
        unordered_map<char, int> m;
        int long_sum = 0;
        for (char c:s) {
            m[c]++;
            if (m[c] % 2 == 0) {
                long_sum += 2;
            }
        }
        return len > long_sum ? long_sum + 1 : long_sum;
    }

// 205. Isomorphic Strings (Easy)
    bool isIsomorphic(string s, string t) {
        int len = s.size();
        for (int i = 0; i < len; i++) {
            if (s.find(s[i]) != t.find(t[i]))
                return false;
        }
        return true;
    }

// 5. Longest Palindromic Substring (Medium)
    string longestPalindrome_5(string s) {
        int len = s.size();
        if (s.empty()) return s;
        bool dp[len][len];
        int result[2] = {0, 0};
        int i, j;
        for (i = 0; i < len; i++) {
            dp[i][i] = true;
        }
        for (i = len - 1; i >= 0; i--) {
            for (j = i + 1; j < len; j++) {
                if (s[i] == s[j]) {
                    if (j - i == 1) {
                        dp[i][j] = true;
                    } else {
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                } else {
                    dp[i][j] = false;
                }
                if (dp[i][j]) {
                    if (result[1] - result[0] <= j - i) {
                        result[0] = i;
                        result[1] = j;
                    }
                }
            }
        }
        return s.substr(result[0], result[1] - result[0] + 1);
    }

// 647. Palindromic Substrings (Medium)
    int countSubstrings(string s) {

    }

// 9. Palindrome Number
    bool isPalindrome(int x) {
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }

        int revertedNumber = 0;
        while (x > revertedNumber) {
            revertedNumber = revertedNumber * 10 + x % 10;
            x /= 10;
        }

        return x == revertedNumber || x == revertedNumber / 10;

    }

// 696. Count Binary Substrings (Easy)
    int countBinarySubstrings(string s) {
/* 方法一
        int len = s.length();
        int vec[len];
        int t = 0;
        vec[0] = 1;
        for (int i = 1; i < len; ++i) {
            if (s[i] != s[i - 1]) {
                vec[++t] = 1;
            } else {
                vec[t]++;
            }
        }
        int ans = 0;
        for (int j = 1; j <= t; ++j) {
            ans += min(vec[j - 1], vec[j]);
        }
        return ans;*/
        int ans = 0, prev = 0, cur = 1;
        for (int i = 1; i < s.length(); ++i) {
            if (s[i] != s[i - 1]) {
                ans += min(prev, cur);
                prev = cur;
                cur = 1;
            } else {
                cur++;
            }
        }
        return ans + min(prev, cur);
    }
};

int main() {
    Solution s;
    s.longestPalindrome_5("abc");
}