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
#include <iostream>
#include <queue>

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
};
