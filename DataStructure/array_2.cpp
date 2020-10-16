//
// Created by logan on 2020/7/25.
//
// 283. Move Zeroes (Easy)
// 566. Reshape the Matrix (Easy)
// 485. Max Consecutive Ones (Easy)
// 240. Search a 2D Matrix II (Medium)
// 378. Kth Smallest Element in a Sorted Matrix ((Medium))
// 645. Set Mismatch (Easy)
// 287. Find the Duplicate Number (Medium)
// 667. Beautiful Arrangement II (Medium)
// 697. Degree of an Array (Easy)
// 766. Toeplitz Matrix (Easy)
// 565. Array Nesting (Medium)
// 769. Max Chunks To Make Sorted (Medium)

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
// 283. Move Zeroes (Easy)
    void moveZeroes(vector<int> &nums) {
        int num = 0;
        auto it = nums.begin();
        for (; it != nums.end(); it++) {
            if (*it == 0) {
                num++;
                nums.erase(it);
                it--;
            }
        }
        for (int i = 0; i < num; ++i) {
            nums.emplace_back(0);
        }
    }

// 566. Reshape the Matrix (Easy)
    vector<vector<int>> matrixReshape(vector<vector<int>> &nums, int r, int c) {

    }

// 485. Max Consecutive Ones (Easy)
    int findMaxConsecutiveOnes(vector<int> &nums) {

    }

// 240. Search a 2D Matrix II (Medium)
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        if (matrix.empty()) return false;
        if (matrix[0].empty()) return false;
        int m = matrix.size();
        int n = matrix[0].size();
        int row = 0, col = n - 1;
        while (row < m && col >= 0) {
            if (target == matrix[row][col]) return true;
            else if (target < matrix[row][col]) col--;
            else row++;
        }
        return false;
    }

// 378. Kth Smallest Element in a Sorted Matrix ((Medium))
    int numbers_less_than_or_equal(const vector<vector<int>> &matrix, int m) {
        int count = 0, i = 0, j = matrix[0].size() - 1;
        while (i < matrix.size() && j >= 0) {
            if (matrix[i][j] > m) {
                j--;
            } else {
                count += j + 1;
                i++;
            }
        }
        return count;
    }

    int kthSmallest(vector<vector<int>> &matrix, int k) {
        if (matrix.empty() || matrix[0].empty()) return -1;
        int l = matrix[0][0], r = matrix.back().back();
        while (l < r) {
            int m = (l + r) >> 1;//(l + r)/2
            if (numbers_less_than_or_equal(matrix, m) >= k) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        return l;
    }

// 645. Set Mismatch (Easy)
    vector<int> findErrorNums(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        vector<int> ans(2);
        for (int i = 0; i < nums.size(); ++i) {
            if ((i + 1) != nums[i]) {
                ans[1] = i + 1;
                ans[0] = nums[i];
                return ans;
            }
        }
        return ans;
    }

// 287. Find the Duplicate Number (Medium)
    int findDuplicate(vector<int> &nums) {

    }

// 667. Beautiful Arrangement II (Medium)
    vector<int> constructArray(int n, int k) {

    }

// 697. Degree of an Array (Easy)
    int findShortestSubArray(vector<int> &nums) {
    }

// 766. Toeplitz Matrix (Easy)
    bool isToeplitzMatrix(vector<vector<int>> &matrix) {

    }

// 565. Array Nesting (Medium)
    int arrayNesting(vector<int> &nums) {
        int ans = 0;
        int count = 0;
        int len = nums.size();
        int first;
        for (int i = 0; i < len; i++) {
            if (nums[i] != 30000) {
//未被标记过
                first = nums[i];
                nums[i] = 30000;
                count = 0;
                do {
                    int temp = nums[first];
                    nums[first] = 30000;
                    first = temp;
                    count++;
                } while (nums[i] != first);
                ans = max(ans, count);
            }
        }
        return ans;
    }

// 769. Max Chunks To Make Sorted (Medium)
    int maxChunksToSorted(vector<int> &arr) {
        int ans = 0, max_n = 0;
        for (int i = 0; i < arr.size(); ++i) {
            max_n = max(max_n, arr[i]);
            if (max_n == i) ans++;
        }
        return ans;
    }
};

int main() {
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(0);
    vec.push_back(4);
    vec.push_back(3);
    vec.push_back(2);
    vec.push_back(6);
    vec.push_back(5);

    Solution s;
    cout << s.maxChunksToSorted(vec);
}