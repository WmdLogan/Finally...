//
// Created by logan on 2020/8/8.
//
// 69. Sqrt(x) (Easy)
// 744. Find Smallest Letter Greater Than Target (Easy)

#include <vector>

using namespace std;

class Solution {
public:
// 69. Sqrt(x) (Easy)
    int mySqrt(int x) {
        int l = 1, h = x;
        while (l <= h) {
            int mid = l + (h - l) / 2;
            int sqrt = x / mid;
            if (sqrt == mid) {
                return mid;
            } else if (mid > sqrt) {
                h = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return h;
    }

// 744. Find Smallest Letter Greater Than Target (Easy)
    char nextGreatestLetter(vector<char> &letters, char target) {
        int left = 0, right = letters.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (letters[mid] > target) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        if (left == letters.size()) return letters[0];
        return letters[left];
    }
};