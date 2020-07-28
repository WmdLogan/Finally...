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
        int len = nums.size();
        int num = 0;
        vector<int>::iterator it = nums.begin();
        for (it; it != nums.end(); it++) {
            if (*it == 0) {
                num++;
                nums.erase(it);
                it--;
            }
        }
        for (int i = 0; i < num; ++i) {
            nums.push_back(0);
        }
    }

// 566. Reshape the Matrix (Easy)
    vector<vector<int>> matrixReshape(vector<vector<int>> &nums, int r, int c) {
        int r_ori = nums.size();
        int c_ori = nums[0].size();
        int r_count = 0, c_count = 0;
        if (r * c != r_ori * c_ori) return nums;
        vector<vector<int>> ans;
        for (int j = 0; j < r; ++j) {
            vector<int> vec;
            for (int i = 0; i < c; ++i) {
                vec.push_back(nums[r_count][c_count]);
                c_count++;
                if (c_count == c_ori) {
                    c_count = 0;
                    r_count++;
                }
            }
            ans.push_back(vec);
        }
        return ans;
    }

// 485. Max Consecutive Ones (Easy)
    int findMaxConsecutiveOnes(vector<int> &nums) {
        short max_length = 0;
        short single_length = 0;
        for (short i = 0; i < nums.size(); ++i) {
            if (nums[i] == 1) single_length++;
            else {
                max_length = max(max_length, single_length);
                single_length = 0;
            }
        }
        return max(max_length, single_length);
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
            if (matrix[i][j] <= m) {
                count += j + 1;
                ++i;
            } else {
                --j;
            }
        }
        return count;

    }

    int kthSmallest(vector<vector<int>> &matrix, int k) {
        if (matrix.empty() || matrix[0].empty())
            return -1;

        int l = matrix[0][0], r = matrix.back().back();
        while (l < r) {
            int m = l + r >> 1;//(l + r)/2
            if (numbers_less_than_or_equal(matrix, m) >= k)
                r = m;
            else
                l = m + 1;
        }
        return l;
    }

// 645. Set Mismatch (Easy)
    vector<int> findErrorNums(vector<int> &nums) {
        int n = nums.size();
        int sum = 0, xor1 = 0, xor2 = 0;
        int dup = -1, mis = 1;
        vector<int> ans(2);
//得到sum = dup ^ mis
        for (int i = 0; i < n; ++i) {
            sum ^= (i + 1) ^ nums[i];
        }
        int t = sum & -sum; //将sum二进制表示下除最靠右的1保留外，其余都置为0
// sum中为1的位即是dup和mis不同的位置，通过最靠右的1来将nums分成两组，一组包含dup不包含mis，另一组包含mis不包含dup
        for (int i = 1; i < n + 1; ++i) {
            if (t & i)
                xor1 ^= i;
            else
                xor2 ^= i;
        }
//xor1和xor2一个为^三次的数（dup），一个为^一次的数（mis）
        for (int i = 0; i < n; ++i) {
            if (t & nums[i])
                xor1 ^= nums[i];
            else
                xor2 ^= nums[i];
        }
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == xor1)
                count++;
        }
        if (count == 0) {
            dup = xor2;
            mis = xor1;
        } else {
            dup = xor1;
            mis = xor2;
        }

        ans[0] = dup;
        ans[1] = mis;
        return ans;
    }

// 287. Find the Duplicate Number (Medium)
    int findDuplicate(vector<int> &nums) {
        int slow = 0, fast = 0;
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);
        slow = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }

// 667. Beautiful Arrangement II (Medium)
    vector<int> constructArray(int n, int k) {
        vector<int> v(n);
        v[0] = 1;
//1, k+1, 2, k, 3, k-1, ...., k/2, k/2+1
        for (int i = 1, interval = k; i <= k; i++, interval--) {
            v[i] = (i % 2 == 1 ? v[i - 1] + interval : v[i - 1] - interval);
        }
        for (int i = k + 1; i < n; i++) {
            v[i] = i + 1;
        }
        return v;
    }

// 697. Degree of an Array (Easy)
    int findShortestSubArray(vector<int> &nums) {
        int len = nums.size();
        unordered_map<int, int> left;
        unordered_map<int, int> right;
        unordered_map<int, int> du;
        for (int i = 0; i < len; ++i) {
            if (left.count(nums[i]) == 0) {
                left[nums[i]] = i;
            }
            right[nums[i]] = i;
            du[nums[i]]++;
        }
        int max_du = 1;
        unordered_map<int, int>::iterator it = du.begin();
        while (it != du.end()) {
            max_du = max(max_du, it->second);
            it++;
        }
        int ans = len;
        unordered_map<int, int>::iterator left_it = left.begin();
        unordered_map<int, int>::iterator right_it = right.begin();
        while (left_it != left.end()) {
            if (du[left_it->first] == max_du) {
                ans = min(ans, right_it->second - left_it->second + 1);
            }
            left_it++;
            right_it++;
        }
        return ans;
    }

};

int main() {
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(4);
    vec.push_back(2);

    Solution s;
    cout << s.findShortestSubArray(vec);
}