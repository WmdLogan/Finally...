//
// Created by logan on 2020/7/22.
//
// 1. Two Sum (Easy)
#include <stack>
#include <deque>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;
class Solution {
//1. Two Sum (Easy)
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<pair<int, int>> vec;
        int len = nums.size();
        for (int i = 0; i < len; ++i) {
            vec.push_back(make_pair(nums[i], i));
        }
        sort(vec.begin(), vec.end());
        vector<int> ans(2);
        int front = 0;
        int last = len - 1;
        while (front < last) {
            int temp_sum = vec[front].first + vec[last].first;
            if (temp_sum == target) {
                ans[0] = vec[front].second;
                ans[1] = vec[last].second;
                return ans;
            } else if (temp_sum < target) {
                front++;
            } else {
                last--;
            }
        }
        return ans;
    }
};
int main() {
    vector<int> vec;
    vec.push_back(4);
    vec.push_back(2);
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(1);
    Solution solution;
    solution.twoSum(vec, 6);

}