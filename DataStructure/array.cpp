//
// Created by logan on 2020/7/25.
//
// 283. Move Zeroes (Easy)
// 566. Reshape the Matrix (Easy)

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
    vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {

    }
};

int main() {
    vector<int> vec;
    vec.push_back(0);
    vec.push_back(0);
    Solution s;
    s.moveZeroes(vec);
}