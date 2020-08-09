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
                //小于等于key的都舍弃
                left = mid + 1;
            }
        }
        return letters[left % letters.size()];
    }

// 540. Single Element in a Sorted Array (Medium)
    int singleNonDuplicate(vector<int> &nums) {
        int r = nums.size() - 1;
        int l = 0;
        while (r > l) {//将查找范围缩小到3个数
            int mid = l + (r - l) / 2;
            if (mid % 2 == 1) {//mid为奇数
                if (nums[mid - 1] == nums[mid]) l = mid + 1;
                else r = mid - 1;
            } else {//mid为偶数
                if (nums[mid - 1] == nums[mid]) r = mid;
                else l = mid;
            }
        }
        return nums[l];
    }

// 278. First Bad Version (Easy)
    bool isBadVersion(int version) { return false; }

    int firstBadVersion(int n) {
        int l = 1;
        while (l < n) {
            int m = l + (n - l) / 2;
            if (isBadVersion(m)) {
                n = m;
            } else {
                l = m + 1;
            }
        }
        return l;
    }

// 153. Find Minimum in Rotated Sorted Array (Medium)
    int findMin(vector<int> &nums) {
        int l = 0, h = nums.size() - 1;
        while (l < h) {
            int m = l + (h - l) / 2;
            if (nums[m] <= nums[h]) {
                h = m;
            } else {
                l = m + 1;
            }
        }
        return nums[l];
    }

// 34. Find First and Last Position of Element in Sorted Array (Medium)
    vector<int> searchRange(vector<int> &nums, int target) {
        vector<int> ans(2, -1);
        int first = findFirst(nums, target);
        if (first == nums.size() || nums[first] != target) return ans;//当key比最后一个元素大，返回值越界
        ans[0] = first;
        ans[1] = findFirst(nums, target + 1) - 1;
        return ans;
    }

    int findFirst(vector<int> &nums, int target) {
        int l = 0, h = nums.size(); // h增大，这样可以返回末尾值
        while (l < h) {
            int m = l + (h - l) / 2;
            if (nums[m] >= target) {
                h = m;
            } else {
                l = m + 1;
            }
        }
        return l;
    }
};

int main() {
    Solution solution;
    vector<int> vec = {2, 2};
    cout << solution.singleNonDuplicate(vec);
    return 0;
}