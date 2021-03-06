//
// Created by logan on 2020/8/2.
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
// 215. Kth Largest Element in an Array (Medium)
    int findKthLargest(vector<int> &nums, int k) {
        int size = nums.size();
        build_heap(nums, size);
        int i = size - 1;
        while (k > 0) {
            swap(nums, i, 0);
            heapify(nums, 0, i);
            i--;
            k--;
        }
        return nums[i + 1];
    }

//建立大根堆
    void build_heap(vector<int> &nums, int size) {
        int last_father = (size - 2) / 2;
        for (int i = last_father; i >= 0; i--) {
            heapify(nums, i, size);
        }
    }

    void heapify(vector<int> &nums, int n, int size) {
        if (n >= size) return;
        int left_child = 2 * n + 1;
        int right_child = 2 * n + 2;
        int max = n;
        if (left_child < size && nums[left_child] > nums[max]) {
            max = left_child;
        }
        if (right_child < size && nums[right_child] > nums[max]) {
            max = right_child;
        }
        if (n != max) {
            swap(nums, max, n);
            heapify(nums, max, size);
        }
    }

    void swap(vector<int> &nums, int i, int j) {
        int a = nums[i];
        nums[i] = nums[j];
        nums[j] = a;
    }

// 451. Sort Characters By Frequency (Medium)
    string frequencySort(string s) {
        //第一次扫描，构造map
        unordered_map<char, int> count;
        for (char c:s) {
            count[c]++;//key-value,计每个字母出现的个数
        }
        vector<pair<char, int>> vec;
        for (auto m:count) {
            vec.push_back(m);//放数组里，pair比较方便
        }
        sort(vec.begin(), vec.end(), [](pair<char, int> p1, pair<char, int> p2) { return p1.second > p2.second; });
        string ans;
        for (auto v:vec) {
            ans = ans + string(v.second, v.first);
        }
        return ans;
    };

// 347. Top K Frequent Elements (Medium)
    vector<int> topKFrequent(vector<int> &nums, int k) {
        unordered_map<int, int> map;
        for (int i : nums) map[i]++; //遍历
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q; //最小堆
        for (auto it : map)
            if (q.size() == k) { //队列满了
                if (it.second > q.top().first) { //堆排
                    q.pop();
                    q.push(make_pair(it.second, it.first));
                }
            } else q.push(make_pair(it.second, it.first));
        vector<int> res;
        while (q.size()) { //将优先队列中k个高频元素存入vector
            res.push_back(q.top().second);
            q.pop();
        }
        return vector<int>(res.rbegin(), res.rend());
    }

// 75. Sort Colors (Medium)
    void swap_color(vector<int> &add, int i, int j) {
        int a = add[i];
        add[i] = add[j];
        add[j] = a;
    }

    void sortColors(vector<int> &nums) {//三向切分快速排序
        int zero = -1, one = 0, two = nums.size();
        while (one < two) {
            if (nums[one] == 0) {//小于切分元素
                swap_color(nums, ++zero, one++);
            } else if (nums[one] == 2) {//大于切分元素
                swap_color(nums, --two, one);
            } else {//等于切分元素
                ++one;
            }
        }
    }
};

int main() {
    Solution s;
    vector<int> add = {12, 1, 42, 3, 10, 4, 5, 14, 8, 20};
    cout << s.frequencySort("anccccc");
//    max_heap_increase(add, 10, 7, 50);

}
