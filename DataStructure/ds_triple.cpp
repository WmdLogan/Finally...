//
// Created by logan on 2020/10/27.
//
#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <unordered_map>
#include <map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
// 101. Symmetric Tree
public:
    bool isSymmetric(TreeNode *root) {
        queue<TreeNode *> queue;
        queue.push(root);
        queue.push(root);
        while (!queue.empty()) {
            TreeNode *left = queue.front();
            queue.pop();
            TreeNode *right = queue.front();
            queue.pop();
            if (!left && !right) continue;
            if (!left || !right) return false;
            if (left->val != right->val) return false;
            queue.push(left->right);
            queue.push(right->left);
            queue.push(left->left);
            queue.push(right->right);
        }
        return true;
    }

// 109. Convert Sorted List to Binary Search Tree
    TreeNode *helper(vector<int> &nums, int left, int right) {
        if (left > right) return nullptr;
        int mid = (left + right) / 2;
//总是选择中间位置左边的数字作为根节点
        auto root = new TreeNode(nums[mid]);
        root->left = helper(nums, left, mid - 1);
        root->right = helper(nums, mid + 1, right);
        return root;
    }

    TreeNode *sortedListToBST(ListNode *head) {
        vector<int> nums;
        while (head) {
            nums.emplace_back(head->val);
            head = head->next;
        }
        return helper(nums, 0, nums.size() - 1);
    }

// 110. Balanced Binary Tree
    int height(TreeNode *root) {
        if (root == nullptr) return 0;
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        if (leftHeight == -1 || rightHeight == -1 || abs(leftHeight - rightHeight) > 1) {
            return -1;
        } else {
            return max(leftHeight, rightHeight) + 1;
        }
    }

    bool isBalanced(TreeNode *root) {
        return height(root) >= 0;
    }

// 111. Minimum Depth of Binary Tree
    int minDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        int ans_depth = 0;
        queue<TreeNode*> q;
        q.emplace(root);
        while (!q.empty()) {
            ans_depth++;
            int size = q.size();
            while (size > 0 ){
                size--;
                auto temp = q.front();
                q.pop();
                if (temp->left == nullptr && temp->right == nullptr) return ans_depth;
                if (temp->left) q.emplace(temp->left);
                if (temp->right) q.emplace(temp->right);
            }
        }
        return ans_depth;
    }

// 205. Isomorphic Strings
    bool isIsomorphic(string s, string t) {
        int len = s.size();
        for (int i = 0; i < len; i++) {
            if (s.find(s[i]) != t.find(t[i]))
                return false;
        }
        return true;
    }

// 207. Course Schedule
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> in_degree(numCourses, 0);//入度表
        vector<vector<int>> in_list(numCourses);
        queue<int> class_queue;
        int flag = 0;
//构造入度表
        for (auto prerequisite:prerequisites) {
            in_degree[prerequisite[0]]++;
            in_list[prerequisite[1]].emplace_back(prerequisite[0]);
        }
//入度为0的课，入队列
        for (int i = 0; i < numCourses; ++i) {
            if (in_degree[i] == 0){
                flag++;
                class_queue.push(i);
            }
        }
        while (!class_queue.empty()) {
            int size = class_queue.size();
            while (size) {
                int temp = class_queue.front();
                class_queue.pop();
                for (int i = 0; i < in_list[temp].size(); ++i) {
                    in_degree[in_list[temp][i]]--;
                    if (in_degree[in_list[temp][i]] == 0) {
                        class_queue.push(in_list[temp][i]);
                        flag++;
                    }
                }
                size--;
            }
        }
        return flag == numCourses;
    }


};
int main(){
    Solution s;
    vector<vector<int>> vec = {{1, 0}};
    cout << s.canFinish(2, vec);
}