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
    int minDepth(TreeNode *root) {
        if (root == nullptr) return 0;
        int ans_depth = 0;
        queue<TreeNode *> q;
        q.emplace(root);
        while (!q.empty()) {
            ans_depth++;
            int size = q.size();
            while (size > 0) {
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
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
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
            if (in_degree[i] == 0) {
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

// 210. Course Schedule II
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
        vector<int> in_degree(numCourses, 0);//入度表
        vector<vector<int>> in_list(numCourses);
        vector<int> ans;
        queue<int> class_queue;
//构造入度表
        for (auto prerequisite:prerequisites) {
            in_degree[prerequisite[0]]++;
            in_list[prerequisite[1]].emplace_back(prerequisite[0]);
        }
//入度为0的课，入队列
        for (int i = 0; i < numCourses; ++i) {
            if (in_degree[i] == 0) {
                ans.emplace_back(i);
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
                        ans.emplace_back(in_list[temp][i]);
                    }
                }
                size--;
            }
        }
        if (ans.size() != numCourses) return {};
        return ans;
    }

// 234. Palindrome Linked List
    bool isPalindrome(ListNode *head) {
        ListNode *fast = head;
        ListNode *slow = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        // 反转后半部分
        ListNode *curNode = slow, *nextNode = slow->next;
        while (nextNode) {
            ListNode *tmp = nextNode->next;
            nextNode->next = curNode;
            curNode = nextNode;
            nextNode = tmp;

        }
        slow->next = nullptr;
        // 开始比较是否相等
        while (head && curNode) {
            if (head->val != curNode->val)
                return false;
            head = head->next;
            curNode = curNode->next;
        }
        return true;
    }

// 235. Lowest Common Ancestor of a Binary Search Tree
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (root->val > p->val && root->val > q->val) return lowestCommonAncestor(root->left, p, q);
        if (root->val < p->val && root->val < q->val) return lowestCommonAncestor(root->right, p, q);
        return root;
    }

// 236. Lowest Common Ancestor of a Binary Tree
    TreeNode *lowestCommonAncestor1(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (root == p || root == q || root == nullptr) return root;
        TreeNode *left = lowestCommonAncestor1(root->left, p, q);
        TreeNode *right = lowestCommonAncestor1(root->right, p, q);
        return left == nullptr ? right : right == nullptr ? left : root;
    }

// 260. Single Number III
    vector<int> singleNumber(vector<int> &nums) {
        vector<int> ans(2, 0);
        int flag = 0;
        for (auto num : nums) {
            flag ^= num;
        }
        flag &= -flag;
        for (int &num : nums) {
            if ((num & flag) == 0) {
                ans[0] ^= num;
            } else {
                ans[1] ^= num;
            }
        }
        return ans;
    }

// 287. Find the Duplicate Number
    int findDuplicate(vector<int> &nums) {
//龟兔赛跑
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

// 337. House Robber III
    map<TreeNode *, int> rob_map;

    int rob(TreeNode *root) {
        if (root == nullptr) return 0;
//利用备忘录消除子问题
        if (rob_map.count(root) != 0) return rob_map[root];
        int ans1 = root->val, ans2 = 0;
//抢，然后去下下家
        if (root->left) ans1 += rob(root->left->left) + rob(root->left->right);
        if (root->right) ans1 += rob(root->right->left) + rob(root->right->right);
//不抢，然后去下家
        ans2 = rob(root->left) + rob(root->right);
        ans1 = max(ans1, ans2);
        rob_map[root] = ans1;
        return ans1;
    }

// 342. 4的幂
    bool isPowerOfFour(int num) {
        return num > 0 && (num & (num - 1)) == 0 && (num & 0xaaaaaaaa) == 0;
    }

// 371. 两整数之和
    int getSum(int a, int b) {
        return b == 0 ? a : getSum(a ^ b, (uint32_t) (a & b) << 1);
    }

// 378. 有序矩阵中第K小的元素
    int numbers_less_than_or_equal(const vector<vector<int>> &matrix, int m) {
        int count = 0, i = 0, j = matrix[0].size() - 1;
//从右上角结点开始
        while (i < matrix.size() && j >= 0) {
//大于目标值，左移
            if (matrix[i][j] > m) {
                j--;
            } else {
//小于目标值，这一行左侧的值全计算；下移
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

// 404. 左叶子之和
    int sumOfLeftLeaves(TreeNode *root) {
        if (!root) return 0;
        int ans = 0;
        queue<TreeNode *> queue_t;
        queue_t.push(root);
        while (!queue_t.empty()) {
            TreeNode *temp = queue_t.front();
            queue_t.pop();
            if (temp->left) {
                if (!temp->left->left && !temp->left->right) ans += temp->left->val;
                else queue_t.push(temp->left);
            }
            if (temp->right) {
                if (!temp->right->left && !temp->right->right) continue;
                queue_t.push(temp->right);
            }

        }
        return ans;
    }

// 501. 二叉搜索树中的众数
    vector<int> findMode_ans;
    int max_count, count;
    int cur;

    void update(int value){
        if (value == cur) count++;
        else count = 1;

        if (count == max_count) findMode_ans.emplace_back(value);
        else if (count > max_count) {
            max_count = count;
            findMode_ans = vector<int>{value};
        }
        cur = value;
    }
//中序遍历
    void find_mode_dfs(TreeNode* root){
        if (root == nullptr) return;
        find_mode_dfs(root->left);
        update(root->val);
        find_mode_dfs(root->right);
    }

    vector<int> findMode(TreeNode* root) {
        find_mode_dfs(root);
        return findMode_ans;
    }

// 565. 数组嵌套
    int arrayNesting(vector<int>& nums) {

    }
};

int main() {
    Solution s;
    vector<vector<int>> vec = {{1, 0}};
    cout << s.canFinish(2, vec);
}