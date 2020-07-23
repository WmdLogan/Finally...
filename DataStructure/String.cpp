//
// Created by logan on 2020/7/22.
//
// 242. Valid Anagram (Easy)
// 409. Longest Palindrome (Easy)
// 205. Isomorphic Strings (Easy)

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
};

