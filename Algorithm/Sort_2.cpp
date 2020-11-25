//
// Created by logan on 2020/11/22.
//
// 215. Kth Largest Element in an Array (Medium)
// 451. Sort Characters By Frequency (Medium)
// 347. Top K Frequent Elements (Medium)
// 75. Sort Colors (Medium)
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <queue>


using namespace std;

class Solution {
public:
// 215. 数组中的第K个最大元素
    void swap(vector<int> &nums, int i, int j) {
        int a = nums[i];
        nums[i] = nums[j];
        nums[j] = a;
    }

    //建立大根堆
    void build_heap(vector<int> &nums, int size) {
        int last_father = (size - 2) / 2;
        for (; last_father >= 0; last_father--) {
            heapify(nums, size, last_father);
        }
    }

    void heapify(vector<int> &nums, int size, int i) {
        if (i >= size) return;
        int left_child = 2 * i + 1;
        int right_child = 2 * i + 2;
        int max_ans = i;
        if (left_child < size && nums[left_child] > nums[max_ans]) max_ans = left_child;
        if (right_child < size && nums[right_child] > nums[max_ans]) max_ans = right_child;
        if (max_ans != i) {
            swap(nums, i, max_ans);
            heapify(nums, size, max_ans);
        }
    }

    int findKthLargest(vector<int> &nums, int k) {
        int size = nums.size();
        build_heap(nums, size);
        int i = size - 1;
        while (k > 0) {
            swap(nums, i, 0);
            heapify(nums, i, 0);
            i--;
            k--;
        }
        return nums[i + 1];
    }

// 347. 前 K 个高频元素
    vector<int> topKFrequent(vector<int> &nums, int k) {
        unordered_map<int, int> map;
        vector<int> ans;
        for (int i:nums) {
            map[i]++;
        }
//维护长度为k的优先队列，升序序列（小顶堆）
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        for (auto it:map) {
            if (q.size() == k) {//队列中有k个元素
                if (it.second > q.top().first) {
                    q.pop();
                    q.push(make_pair(it.second, it.first));
                }
            } else {
                q.push(make_pair(it.second, it.first));
            }
        }
//将优先队列中的k个高频元素存入
        while (k) {
            ans.emplace_back(q.top().second);
            q.pop();
            k--;
        }
        return ans;
    }

// 451. 根据字符出现频率排序
    string frequencySort(string s) {
        unordered_map<char, int> map;
        string ans;
        for (char i: s) {
            map[i]++;
        }
        vector<pair<char, int>> vec;
        for (auto m:map) {
            vec.emplace_back(m);
        }
        sort(vec.begin(), vec.end(), [&](pair<char, int> &p1, pair<char, int> &p2) { return p1.second > p2.second; });
        for (auto v:vec) {
            ans += string(v.second, v.first);
        }
        return ans;
    }

// 75. 颜色分类
    void sortColors(vector<int>& nums) {
        int len = nums.size();
        if (len < 2) return;
// all in [0, p0) == 0
// all in [p0, i) == 1
// all in (p2, len - 1] == 2
        int p0 = 0;
        int i = 0;
        int p2 = len - 1;
        while (i <= p2) {
            if (nums[i] == 0) {
                swap(nums, i, p0);
                p0++;
                i++;
            } else if (nums[i] == 1) {
                i++;
            } else {
                //nums[i]==2
                swap(nums, i, p2);
                p2--;
            }
        }
    }

}
};

int main() {
    Solution s;
    vector<int> vac = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    s.findKthLargest(vac, 2);
}

