//
// Created by logan on 2020/8/8.
//
// 69. Sqrt(x) (Easy)
// 744. Find Smallest Letter Greater Than Target (Easy)
// 540. Single Element in a Sorted Array (Medium)
// 278. First Bad Version (Easy)
// 153. Find Minimum in Rotated Sorted Array (Medium)
// 34. Find First and Last Position of Element in Sorted Array (Medium)

#include <vector>
#include <iostream>


using namespace std;

class Solution {
// 744. 寻找比目标字母大的最小字母
    char nextGreatestLetter(vector<char> &letters, char target) {
//寻找右侧边界的二分查找
        int left = 0, right = letters.size();
        while (left < right) {
            int mid = (right - left) / 2 + left;
            if (letters[mid] > target) {
                right = mid;
            } else if (letters[mid] == target) {
                left = mid + 1;
            } else {
                left = mid + 1;
            }
        }
//left - 1为右侧边界
        return letters[left % letters.size()];
    }

// 540. 有序数组中的单一元素
    int singleNonDuplicate(vector<int> &nums) {
//基本的二分查找
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (mid % 2 == 1) {
                //mid是奇数
                if (nums[mid - 1] == nums[mid]) l = mid + 1;
                else r = mid - 1;
            } else {
                //mid是偶数
                if (nums[mid - 1] == nums[mid])r = mid;
                else l = mid;
            }
        }
        return nums[l];
    }

// 278. 第一个错误的版本
    bool isBadVersion(int version);

    int firstBadVersion(int n) {
//寻找左侧边界
        int l = 1, r = n;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (isBadVersion(mid) == false) l = mid + 1;
            else r = mid;
        }
        return l;
    }

// 153. 寻找旋转排序数组中的最小值
    int findMin(vector<int> &nums) {
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] < nums[r]) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return nums[l];
    }

// 34. 在排序数组中查找元素的第一个和最后一个位置
    vector<int> searchRange(vector<int> &nums, int target) {
        vector<int> ans(2, -1);
        int first = findFirst(nums, target);
        if (first == nums.size() || nums[first] != target) return ans;
        ans[0] = first;
        ans[1] = findFirst(nums, target + 1) - 1;
        return ans;
    }

    int findFirst(vector<int> &nums, int target) {
        int l = 0, r = nums.size();
        while (l < r) {
            int m = l + (r - l) / 2;
            if (nums[m] >= target) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        return l;
    }
}

};
