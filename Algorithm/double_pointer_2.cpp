//
// Created by logan on 2020/8/2.
//
// 167. 两数之和 II - 输入有序数组
// 633. 平方数之和
// 345. 反转字符串中的元音字母
// 680. 验证回文字符串 Ⅱ

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <cmath>
#include <set>

using namespace std;

class Solution {
public:
// 167. 两数之和 II - 输入有序数组
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> ans;
        int i = 0;
        int j = numbers.size() - 1;
        while (i < j) {
            int temp = numbers[i] + numbers[j];
            if (temp == target) {
                ans.push_back(i + 1);
                ans.push_back(j + 1);
                return ans;
            }
            else if (temp > target) j--;
            else i++;
        }
        return ans;
    }

// 633. 平方数之和
    bool judgeSquareSum(int c) {
        long high = sqrt(c), low = 0;
        while(low <= high) {
            long sum = high * high + low * low;
            if( sum == c )
                return true;
            else if(sum < c)
                low++;
            else
                high--;
        }
        return false;
    }

// 345. 反转字符串中的元音字母
    string reverseVowels(string s) {
        set<char> m = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
        int i = 0, j = s.size();
        while (i < j) {
            if (!m.count(s[i])) {
                i++;
                continue;
            }
            if (!m.count(s[j])) {
                j--;
                continue;
            }
            swap(s[i], s[j]);
            i++;
            j--;
        }
        return s;
    }

// 680. 验证回文字符串 Ⅱ
    bool validPalindrome(string s) {
        int l = 0;
        int r = s.size() - 1;
        while (l < r && s[l] == s[r]) {
            ++l;
            --r;
        }
        if (l >= r) return true;
        int l2 = l;
        int r2 = r - 1;
        l++;
        while (l < r && s[l] == s[r]) {
            ++l;
            --r;
        }
        if (l >= r) return true;
        while (l2 < r2 && s[l2] == s[r2]) {
            ++l2;
            --r2;
        }
        if (l2 >= r2) return true;
        return false;
    }
};

int main() {
    Solution s;
}