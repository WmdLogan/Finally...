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

    void update(int value) {
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
    void find_mode_dfs(TreeNode *root) {
        if (root == nullptr) return;
        find_mode_dfs(root->left);
        update(root->val);
        find_mode_dfs(root->right);
    }

    vector<int> findMode(TreeNode *root) {
        find_mode_dfs(root);
        return findMode_ans;
    }

// 565. 数组嵌套
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

// 572. 另一个树的子树
    bool isSubtree(TreeNode *s, TreeNode *t) {
        stack<TreeNode *> st;
        st.push(s);
        while (!st.empty()) {
            int size = st.size();
            while (size) {
                TreeNode *temp = st.top();
                st.pop();
                if (temp->val == t->val) {
                    bool ans = isSubtree_help(temp, t);
                    if (ans) return true;
                }
                if (temp->left) st.push(temp->left);
                if (temp->right) st.push(temp->right);
                size--;
            }
        }
        return false;
    }

    bool isSubtree_help(TreeNode *s, TreeNode *t) {
        if (s == nullptr && t == nullptr) return true;
        if (!(s && t)) return false;
        if (s->val == t->val) return isSubtree_help(s->left, t->left) && isSubtree_help(s->right, t->right);
        return false;
    }

// 617. 合并二叉树
    TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2) {
        if (t1 == nullptr) return t2;
        if (t2 == nullptr) return t1;
        merge_help(t1, t2);
        return t1;
    }

    void merge_help(TreeNode *t1, TreeNode *t2) {
        t1->val += t2->val;
        if (t1->left == nullptr && t2->left != nullptr) t1->left = t2->left;
        else if (t1->left != nullptr && t2->left != nullptr) merge_help(t1->left, t2->left);

        if (t1->right == nullptr && t2->right != nullptr) t1->right = t2->right;
        else if (t1->right == nullptr && t2->right == nullptr) return;
        else if (t1->right != nullptr && t2->right != nullptr) merge_help(t1->right, t2->right);
    }

// 647. 回文子串
    int countSubstrings(string s) {
        int n = s.size(), ans = 0;
//长度为n的字符串，有（2*n -1）个中心
        for (int i = 0; i < 2 * n - 1; ++i) {
//确定左右中心，字符串有奇数和偶数两种情况
            int l = i / 2, r = i / 2 + i % 2;
//中心扩展
            while (l >= 0 && r < n && s[l] == s[r]) {
                --l;
                ++r;
                ++ans;
            }
        }
        return ans;
    }

// 667. 优美的排列 II
    vector<int> constructArray(int n, int k) {
        vector<int> ans(n, 1);
        for (int i = 1; i < n; ++i) {
            if (k > 0) {
                ans[i] = i % 2 == 1 ? ans[i - 1] + k : ans[i - 1] - k;
                k--;
            } else {
                ans[i] = i + 1;
            }
        }
        return ans;
    }

// 669. 修剪二叉搜索树
    TreeNode *trimBST(TreeNode *root, int low, int high) {
        if (root == nullptr) return root;
        if (root->val > high) {
            return trimBST(root->left, low, high);//剪掉右子树
        }
        if (root->val < low) {
            return trimBST(root->right, low, high);//剪掉左子树
        }
        root->left = trimBST(root->left, low, high);
        root->right = trimBST(root->right, low, high);
        return root;
    }

// 671. 二叉树中第二小的节点
    int findSecondMinimumValue(TreeNode *root) {
        if (!root || !root->left || !root->right) return -1;//空节点或不满足题意

        int left = root->left->val, right = root->right->val;
        //若根节点和左节点值相同，则递归找左子树的第二小节点，与右节点比谁小
        if (root->val == left) left = findSecondMinimumValue(root->left);
        //若根节点和右节点值相同，则递归找右子树的第二小节点，与左节点比谁小
        if (root->val == right) right = findSecondMinimumValue(root->right);

        //根据当前的根、左右节点的值继续判断
        int min_lr = min(left, right);

        if (root->val < min_lr) return min_lr;//根节点小于最小值，返回最小值
        else return max(left, right);//根节点等于最小值，返回最大值
    }

// 684. 冗余连接
    vector<int> findRedundantConnection(vector<vector<int>> &edges) {
        vector<int> father_set(edges.size() + 1);
//每个顶点的默认代表节点是自己
        for (int i = 0; i < edges.size(); ++i) {
            father_set[i] = i;
        }
        for (auto &edge:edges) {
            int left_re = find(father_set[edge[0]], father_set);
            int right_re = find(father_set[edge[1]], father_set);
            if (left_re == right_re) return edge;
            father_set[left_re] = right_re;
        }
        return {0, 0};
    }
//找代表节点
    int find(int n, vector<int> &rp) {
        int num = n;
        while (rp[num] != num)
            num = rp[num];
        return num;
    }

// 687. 最长同值路径
    int longest_ans = 0;
    int longestUnivaluePath(TreeNode *root) {
        help_longest(root);
        return longest_ans;
    }

    int help_longest(TreeNode *root){
        if (root == nullptr) return 0;
        int left = help_longest(root->left);//root左子树的最长同值路径
        int right = help_longest(root->right);;//root右子树的最长同值路径

        int leftPath = root->left != nullptr && root->left->val == root->val ? left + 1 : 0;
        int rightPath = root->right != nullptr && root->right->val == root->val ? right + 1 : 0;

        longest_ans = max(longest_ans, leftPath + rightPath);
        return max(leftPath, rightPath);//！！返回单向最长路径
    }

// 693. 交替位二进制数
    bool hasAlternatingBits(int n) {
//如果是交替二进制，则错位异或为全1
        uint32_t temp = n ^(n >> 1);
        temp++;
        return (temp & (temp - 1)) == 0;
    }

// 696. 计数二进制子串
    int countBinarySubstrings(string s) {
//将字符串按照0和1的连续段分组，每组记录连续的个数
        int len = s.length();
        vector<int> vec(len);
        int t = 0, ans = 0;
        vec[0] = 1;
        for (int i = 1; i < len; ++i) {
            if (s[i] != s[i - 1]) {
                vec[++t] = 1;
            } else {
                vec[t]++;
            }
        }
//共t组连续的0和1
        for (int i = 1; i <= t; ++i) {
            ans += min(vec[i - 1], vec[i]);
        }
        return ans;
    }

// 725. 分隔链表
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        vector<ListNode *> ans(k);
        int size = 0;
        auto l1 = root;
//求链表长度
        while(l1 != nullptr){
            size++;
            l1 = l1->next;
        }
        int aver_len = size / k;//平均长度
        int bonus = size % k;//有余数，长度+1
        auto *cur = root;
//i代表第i组
        for (int i = 0; i < k; ++i) {
            auto *head = cur;
            for (int j = 0; j < aver_len + (i < bonus ? 1 : 0) - 1; ++j) {
                if (cur != nullptr) cur = cur->next;
            }
            if (cur != nullptr) {
                auto* prev = cur;
                cur = cur->next;
                prev->next = nullptr;
            }
            ans[i] = head;
        }
        return ans;
    }

// 739. 每日温度
    vector<int> dailyTemperatures(vector<int>& T) {
        int size = T.size();
        vector<int> ans(size,0);
        stack<int> stack;
        stack.push(0);
        for (int i = 1; i < size; ++i) {
            while (!stack.empty() && T[i] > T[stack.top()]) {
                ans[stack.top()] = i - stack.top();
                stack.pop();
            }
            stack.push(i);
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<vector<int>> vec = {{1, 0}};
    cout << s.canFinish(2, vec);
}