//
// Created by logan on 2020/7/25.
//
// 283. Move Zeroes (Easy)
// 566. Reshape the Matrix (Easy)
// 485. Max Consecutive Ones (Easy)

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
                if (c_count == c_ori){
                    c_count = 0;
                    r_count++;
                }
            }
            ans.push_back(vec);
        }
        return ans;
    }
// 485. Max Consecutive Ones (Easy)
    int findMaxConsecutiveOnes(vector<int>& nums) {
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
};

int main() {
    vector<int> vec;
    vec.push_back(0);
    vec.push_back(0);
    Solution s;
    s.moveZeroes(vec);
}