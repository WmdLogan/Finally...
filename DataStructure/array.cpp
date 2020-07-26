//
// Created by logan on 2020/7/25.
//
// 283. Move Zeroes (Easy)
// 566. Reshape the Matrix (Easy)
// 485. Max Consecutive Ones (Easy)
// 240. Search a 2D Matrix II (Medium)

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
    vector <vector<int>> matrixReshape(vector <vector<int>> &nums, int r, int c) {
        int r_ori = nums.size();
        int c_ori = nums[0].size();
        int r_count = 0, c_count = 0;
        if (r * c != r_ori * c_ori) return nums;
        vector <vector<int>> ans;
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
    bool searchMatrix(vector <vector<int>> &matrix, int target) {
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
};

int main() {
    vector <vector<int>> matrix;
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    matrix.push_back(vec);
    vector<int> vec1;
    vec1.push_back(6);
    vec1.push_back(7);
    vec1.push_back(8);
    vec1.push_back(9);
    vec1.push_back(10);
    matrix.push_back(vec1);
    vector<int> vec2;
    vec2.push_back(11);
    vec2.push_back(12);
    vec2.push_back(13);
    vec2.push_back(14);
    vec2.push_back(15);
    matrix.push_back(vec2);
    vector<int> vec3;
    vec3.push_back(16);
    vec3.push_back(17);
    vec3.push_back(18);
    vec3.push_back(19);
    vec3.push_back(20);
    matrix.push_back(vec3);
    vector<int> vec4;
    vec4.push_back(21);
    vec4.push_back(22);
    vec4.push_back(23);
    vec4.push_back(24);
    vec4.push_back(25);
    matrix.push_back(vec4);
    Solution s;
    cout << s.searchMatrix(matrix, 19);
}