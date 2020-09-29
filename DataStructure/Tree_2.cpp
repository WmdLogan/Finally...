//
// Created by logan on 2020/9/24.
//
// 104. Maximum Depth of Binary Tree (Easy)
// 110. Balanced Binary Tree (Easy)
// 543. Diameter of Binary Tree (Easy)
// 226. Invert Binary Tree (Easy)
// 617. Merge Two Binary Trees (Easy)
// 112. Path Sum (Easy)
// 437. Path Sum III (Medium)
// 572. Subtree of Another Tree (Easy)
// 101. Symmetric Tree (Easy)
// 111. Minimum Depth of Binary Tree (Easy)
// 404. Sum of Left Leaves (Easy)
// 687. Longest Univalue Path (Easy)
// 337. House Robber III (Medium)
// 671. Second Minimum Node In a Binary Tree (Easy)
// 637. Average of Levels in Binary Tree (Easy)
// 513. Find Bottom Left Tree Value (Medium)
// 144. Binary Tree Preorder Traversal (Medium)
// 145. Binary Tree Postorder Traversal (Medium)
// 94. Binary Tree Inorder Traversal (Medium)
// 669. Trim a Binary Search Tree (Easy)
// 230. Kth Smallest Element in a BST (Medium)
// 538. Convert BST to Greater Tree (Medium)
// 235. Lowest Common Ancestor of a Binary Search Tree (Easy)
#include <iostream>
#include <queue>
#include <map>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
// 104. Maximum Depth of Binary Tree (Easy)
    int maxDepth(TreeNode *root) {
        if (root == nullptr) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }

// 110. Balanced Binary Tree (Easy)
    int height(TreeNode *root, bool &ans) {
        if (root == nullptr) return 0;
        int leftHeight = height(root->left, ans);
        int rightHeight = height(root->right, ans);
        if (abs(leftHeight - rightHeight) > 1) {
            ans = false;
        }
        return max(leftHeight, rightHeight) + 1;

    }

    bool isBalanced(TreeNode *root) {
        bool ans = true;
        height(root, ans);
        return ans;
    }

// 543. Diameter of Binary Tree (Easy)
    int length;

    int diameterOfBinaryTree(TreeNode *root) {
        length = 0;
        find_max_length(root);
        return length;
    }

    int find_max_length(TreeNode *root) {
        if (root == nullptr) return 0;
        int left = find_max_length(root->left);
        int right = find_max_length(root->right);
        length = max(left + right, length);
        return max(left, right) + 1;
    }

// 226. Invert Binary Tree (Easy)
    TreeNode *invertTree(TreeNode *root) {
        single_invert(root);
        return root;
    }

    void single_invert(TreeNode *root) {
        if (root == nullptr) return;
        auto temp = root->left;
        root->left = root->right;
        root->right = temp;
        single_invert(root->left);
        single_invert(root->right);
        return;
    }

// 617. Merge Two Binary Trees (Easy)
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

// 112. Path Sum (Easy)
    bool hasPathSum(TreeNode *root, int sum) {
        if (root == nullptr) return false;
        if (root->left == nullptr && root->right == nullptr && sum == root->val) return true;
        return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }

// 437. Path Sum III (Medium)
    int pathSum_ans = 0;

    int pathSum(TreeNode *root, int sum) {
        if (root == nullptr) return pathSum_ans;
        if (root->left) pathSum(root->left, sum);
        if (root->right) pathSum(root->right, sum);
        help_pathSum(root, sum);
        return pathSum_ans;
    }

    void help_pathSum(TreeNode *root, int sum) {
        if (root == nullptr) return;
        if (sum == root->val) pathSum_ans++;
        if (root->left) help_pathSum(root->left, sum - root->val);
        if (root->right) help_pathSum(root->right, sum - root->val);
    }

// 572. Subtree of Another Tree (Easy)
    bool isSubtree(TreeNode *s, TreeNode *t) {
//遍历s，每个节点判断是否包含t
        if (s == nullptr) return false;
        return help_isSubtree(s, t) || isSubtree(s->left, t) || isSubtree(s->right, t);
    }

    bool help_isSubtree(TreeNode *s, TreeNode *t) {
        if (s == nullptr && t == nullptr) return true;
        if (s == nullptr || t == nullptr) return false;
        if (s->val != t->val) return false;
        return help_isSubtree(s->left, t->left) && help_isSubtree(s->right, t->right);
    }

// 101. Symmetric Tree (Easy)
    bool isSymmetric(TreeNode *root) {
        return help_isSymmetric(root, root);
    }

    bool help_isSymmetric(TreeNode *left, TreeNode *right) {
        if (left == nullptr && right == nullptr) return true;
        if (left == nullptr || right == nullptr) return false;
        if (left->val != right->val) return false;
        return help_isSymmetric(left->left, right->right) && help_isSymmetric(left->right, right->left);
    }

    bool isSymmetric_iteration(TreeNode *root) {
        queue<TreeNode *> q;
        q.push(root);
        q.push(root);
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            auto v = q.front();
            q.pop();
            if (!u && !v) continue;
            if ((!u || !v) || (u->val != v->val)) return false;

            q.push(u->left);
            q.push(v->right);

            q.push(u->right);
            q.push(v->left);
        }
        return true;
    }

// 111. Minimum Depth of Binary Tree (Easy)
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
                if (temp == nullptr) continue;
                if (temp->left == nullptr && temp->right == nullptr) return ans_depth;

                q.emplace(temp->left);
                q.emplace(temp->right);
            }
        }
        return ans_depth;
    }

// 404. Sum of Left Leaves (Easy)
    int left_sum = 0;

    int sumOfLeftLeaves(TreeNode *root) {
        if (root == nullptr) return 0;
        //输出
        if (root->left) {
            if (root->left->left == nullptr && root->left->right == nullptr)//左叶子节点
            {
                left_sum += root->left->val;
            } else {
                sumOfLeftLeaves(root->left);
            }
        }
        if (root->right) sumOfLeftLeaves(root->right);
        return left_sum;
    }

// 687. Longest Univalue Path (Easy)
    int longest_ans = 0;

    int longestUnivaluePath(TreeNode *root) {
        help_longest(root);
        return longest_ans;
    }

    int help_longest(TreeNode *root) {
        if (root == nullptr) return 0;
        int left = help_longest(root->left);//root左子树的最长同值路径
        int right = help_longest(root->right);;//root右子树的最长同值路径
        int leftPath = root->left != nullptr && root->left->val == root->val ? left + 1 : 0;
        int rightPath = root->right != nullptr && root->right->val == root->val ? right + 1 : 0;
        longest_ans = max(longest_ans, leftPath + rightPath);
        return max(leftPath, rightPath);//！！返回单向最长路径
    }

// 337. House Robber III (Medium)
    map<TreeNode *, int> rob_map;

    int rob(TreeNode *root) {
        if (root == nullptr) return 0;
//利用备忘录消除子问题
        if (rob_map.count(root) != 0) {
            return rob_map[root];
        }
//抢，然后去下下家
        int val1 = root->val;
        if (root->left != nullptr) val1 += rob(root->left->left) + rob(root->left->right);
        if (root->right != nullptr) val1 += rob(root->right->left) + rob(root->right->right);
//不抢，然后去下家
        int val2 = rob(root->left) + rob(root->right);
        int ans = max(val1, val2);
        rob_map[root] = ans;
        return ans;
    }

// 671. Second Minimum Node In a Binary Tree (Easy)
    int findSecondMinimumValue(TreeNode *root) {
//根节点是最小值，找到第一个大于最小值的节点
        if (root == nullptr) return -1;
        if (root->left == nullptr) return -1;
        int leftVal = root->left->val;//根节点左孩子值
        int rightVal = root->right->val;//根节点右孩子值
//左孩子和跟相等，找到左子树中第二小的和右孩子比
        if (leftVal == root->val) leftVal = findSecondMinimumValue(root->left);
//右孩子和跟相等，找到右子树中第二小的和右孩子比
        if (rightVal == root->val) rightVal = findSecondMinimumValue(root->right);
        if (leftVal != -1 && rightVal != -1) return min(leftVal, rightVal);
        return leftVal == -1 ? rightVal : leftVal;
    }

// 637. Average of Levels in Binary Tree (Easy)
    vector<double> averageOfLevels(TreeNode *root) {
        queue<TreeNode *> q;
        vector<double> ans;
        q.emplace(root);
        while (!q.empty()) {
            int size = q.size();
            double sum = 0;
            for (int i = 0; i < size; ++i) {
                auto *temp = q.front();
                q.pop();
                sum += temp->val;
                if (temp->left) q.emplace(temp->left);
                if (temp->right) q.emplace(temp->right);
            }
            ans.emplace_back(sum / size);
        }
        return ans;
    }

// 513. Find Bottom Left Tree Value (Medium)
    int findBottomLeftValue(TreeNode *root) {
        queue<TreeNode *> q;
        q.emplace(root);
        int ans;
        while (!q.empty()) {
            int size = q.size();
            auto *temp = q.front();
            q.pop();
            ans = temp->val;
            if (temp->left) q.emplace(temp->left);
            if (temp->right) q.emplace(temp->right);
            for (int i = 1; i < size; ++i) {
                auto *temp = q.front();
                q.pop();
                if (temp->left) q.emplace(temp->left);
                if (temp->right) q.emplace(temp->right);
            }
        }
        return ans;
    }

// 144. Binary Tree Preorder Traversal (Medium)
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> ans;
        stack<TreeNode *> st;
        if (root) st.push(root);
        while (!st.empty()) {
            auto *temp = st.top();
            st.pop();
            ans.emplace_back(temp->val);
            if (temp->right) st.emplace(temp->right);
            if (temp->left) st.emplace(temp->left);
        }
        return ans;
    }

// 145. Binary Tree Postorder Traversal (Medium)
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> ans;
        stack<TreeNode *> st;
        if (root) st.emplace(root);
        while (!st.empty()) {
            auto *temp = st.top();
            st.pop();
            if (temp != nullptr) {
                st.emplace(temp);
                st.emplace(nullptr);
                if (temp->right) st.emplace(temp->right);
                if (temp->left) st.emplace(temp->left);
            } else {
                ans.emplace_back(st.top()->val);
                st.pop();
            }
        }
        return ans;
    }

// 94. Binary Tree Inorder Traversal (Medium)
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> ans;
        stack<TreeNode *> st;
        if (root) st.emplace(root);
        while (!st.empty()) {
            auto *temp = st.top();
            st.pop();
            if (temp != nullptr) {
                st.emplace(temp);
                st.emplace(nullptr);
                if (temp->left) st.emplace(temp->left);
            } else {
                auto *r_node = st.top();
                st.pop();
                ans.push_back(r_node->val);
                if (r_node->right) st.emplace(r_node->right);
            }
        }
        return ans;
    }

// 669. Trim a Binary Search Tree (Easy)
    TreeNode *trimBST(TreeNode *root, int low, int high) {
        if (root == nullptr) {
            return root;
        }
        if (root->val > high) {
            return trimBST(root->left, low, high); //只处理左子树，相当于剪掉了root及其右子树
        }

        if (root->val < low) {
            return trimBST(root->right, low, high); //只处理右子树，相当于剪掉了root及其左子树
        }

        root->left = trimBST(root->left, low, high);
        root->right = trimBST(root->right, low, high);

        return root;
    }

// 230. Kth Smallest Element in a BST (Medium)
    int kthSmallest(TreeNode *root, int k) {
        stack<TreeNode *> st;
        if (root) st.emplace(root);
        while (!st.empty()) {
            auto *temp = st.top();
            st.pop();
            if (temp != nullptr) {
                st.emplace(temp);
                st.emplace(nullptr);
                if (temp->left) st.emplace(temp->left);
            } else {
                auto *r_node = st.top();
                st.pop();
                k--;
                if (k == 0) return r_node->val;
                if (r_node->right) st.emplace(r_node->right);
            }
        }
        return 0;
    }

// 538. Convert BST to Greater Tree (Medium)
    TreeNode *convertBST(TreeNode *root) {
        add_BST(root, 0);
        return root;
    }

        int add_BST(TreeNode *root, int sum){
            if (root->right) sum = add_BST(root->right, sum);
            root->val += sum;
            if (root->left) sum = add_BST(root->left, root->val);
            return sum;
        }

// 235. Lowest Common Ancestor of a Binary Search Tree (Easy)
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

    }
};
