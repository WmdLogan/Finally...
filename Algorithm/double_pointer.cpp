//
// Created by logan on 2020/8/2.
//
// 167. Two Sum II - Input array is sorted (Easy)
// 633. Sum of Square Numbers (Easy)
// 345. Reverse Vowels of a String (Easy)
// 680. Valid Palindrome II (Easy)
// 88. Merge Sorted Array (Easy)
// 524. Longest Word in Dictionary through Deleting (Medium)
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <cmath>
#include <set>

using namespace std;

class Solution {
public:
// 167. Two Sum II - Input array is sorted (Easy)
    vector<int> twoSum(vector<int> &numbers, int target) {
        vector<int> ans;
        int i = 0;
        int j = numbers.size() - 1;
        while (i < j) {
            int temp = numbers[i] + numbers[j];
            if (temp == target) {
                ans.push_back(i + 1);
                ans.push_back(j + 1);
                break;
            } else if (temp > target) j--;
            else i++;
        }
        return ans;
    }

// 633. Sum of Square Numbers (Easy)
    bool judgeSquareSum(int c) {
        long high = sqrt(c), low = 0;
        while (low <= high) {
            long sum = high * high + low * low;
            if (sum == c)
                return 1;
            else if (sum < c)
                low++;
            else
                high--;
        }
        return 0;
    }

// 345. Reverse Vowels of a String (Easy)
public:
    bool isOrigin(char c) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
            return true;
        else
            return false;
    }

public:
    string reverseVowels(string s) {
        int i = 0, j = s.size();
        while (i < j) {
            if (!isOrigin(s[i])) {
                i++;
                continue;
            }
            if (!isOrigin(s[j])) {
                j--;
                continue;
            }
            swap(s[i], s[j]);
            i++;
            j--;
        }
        return s;
    }

// 680. Valid Palindrome II (Easy)
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

// 88. Merge Sorted Array (Easy)
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
        int p = m + n;
        m--;
        n--;
        while (n >= 0 && m >= 0) {
            nums1[--p] = nums1[m] <= nums2[n] ? nums2[n--] : nums1[m--];
        }
        if (m < 0) {
            while (n >= 0) {
                nums1[--p] = nums2[n--];
            }
        }
    }

// 524. Longest Word in Dictionary through Deleting (Medium)
    string findLongestWord(string s, vector<string> &d) {
        int pos = 0, i = 0, j = 0, pos1 = 0, m = 0, length = 0, length1 = 0, flag = 0;
        int target = d.size() - 1;
        for (int k = 0; k <= target; k++) {
//从第一个字符串开始，i/j开始匹配
            while (i <= s.size() && j < d[k].size()) {
                if (s[i] == d[k][j]) {
                    i++;
                    j++;
                }
//如果匹配失败，下一个字符
                else i++;
            }
//如果d的字符串到最后，匹配成功，记录下位置字符串位置pos以及字符串长度lentgh，并比较更新
            if (j == d[k].size()) {
                flag = 1;
                pos1 = k;
                length1 = d[k].size();
                //相等，比较字典顺序
                if (length == length1) {
                    while (m < length1) {
                        //小于 更新字符串
                        if (d[k][m] < d[pos][m]) {
                            pos = pos1;
                            break;
                            //等于 比较下一个
                        } else if (d[k][m] == d[pos][m]) {
                            m++;
                            //大于 保持原字符串
                        } else {
                            break;
                        }
                    }
                    m = 0;
                    //长度更长，更新字符
                } else if (length1 > length) {
                    length = length1;
                    pos = pos1;
                }
            }
            i = 0;
            j = 0;
        }
        return flag == 0 ? "" : d[pos];
    }
};

int main() {
    Solution s;
}