//
// Created by logan on 2020/7/6.
// 104. Maximum Depth of Binary Tree (Easy)
// 110. Balanced Binary Tree (Easy)
// 543. Diameter of Binary Tree (Easy)
// 226. Invert Binary Tree (Easy)
// 617. Merge Two Binary Trees (Easy)
// 112. Path Sum (Easy)
// 437. Path Sum III (Easy)
// 572. Subtree of Another Tree (Easy)
#include <iostream>
#include <deque>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
//104
    int maxDepth(TreeNode *root) {
        if (root == nullptr) return 0;
        deque<TreeNode *> q;
        q.push_back(root);
        int deep = 0;
        while (!q.empty()) {
            deep++;
            int num = q.size();
            for (int i = 1; i <= num; i++) {
                TreeNode *p = q.front();
                q.pop_front();
                if (p->left) q.push_back(p->left);
                if (p->right) q.push_back(p->right);
            }
        }
        return deep;
    }
//110
    bool isBalanced(TreeNode *root) {
        if (!root) return true;

        int d = abs(maxDepth(root->left) - maxDepth(root->right)); //当前节点的左右子树的高度差

        return (d <= 1) && (isBalanced(root->left)) && (isBalanced(root->right));
    }

public:
// 543. Diameter of Binary Tree (Easy)
    int Max;

    int depth(TreeNode *rt) {
        if (rt == nullptr) {
            return 0;
        }
        int L, R;
        L = depth(rt->left);
        R = depth(rt->right);
        if (L + R + 1 > Max) {
            Max = L + R + 1;
        }
        return max(L, R) + 1;
    }

    int diameterOfBinaryTree(TreeNode *root) {
        Max = 1;
        depth(root);
        return Max - 1;
    }

public:
// 226. Invert Binary Tree (Easy)
    TreeNode *invertTree(TreeNode *root) {
        if (root == nullptr) {
            return nullptr;
        }
        TreeNode *temp;
        if (root->right || root->left) {
            temp = root->left;
            root->left = root->right;
            root->right = temp;
            invertTree(root->left);
            invertTree(root->right);
        }
        return root;
    }

// 617. Merge Two Binary Trees (Easy)
    TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2) {
        if (t1 == nullptr && t2 == nullptr) {
            return nullptr;
        } else if (t1 == nullptr && t2 != nullptr) {
            return t2;
        } else if (t1 != nullptr && t2 == nullptr) {
            return t1;
        }
        t1->val += t2->val;
        if (t1->left && t2->left) {
            mergeTrees(t1->left, t2->left);
        }
        if (!t1->left && t2->left) {//t1左子树为空
            t1->left = t2->left;
        }
        if (t1->right && t2->right) {
            mergeTrees(t1->right, t2->right);
        }
        if (!t1->right && t2->right) {//t1右子树为空
            t1->right = t2->right;
        }
        return t1;
    }

public:
    int tree_sum = 0;
// 112. Path Sum (Easy)

    bool hasPathSum(TreeNode *root, int sum) {
        bool left_sum, right_sum;
        if (root == nullptr) {
            return false;
        }
        tree_sum += root->val;//加上当前节点的val
        if (!root->left && !root->right) {//叶子节点，判断sum是否相等
            if (sum == tree_sum) {
                return true;
            } else {
                tree_sum -= root->val;
                return false;
            }
        }
//没到叶子结点，继续递归
        left_sum = hasPathSum(root->left, sum);
        right_sum = hasPathSum(root->right, sum);
        tree_sum -= root->val;
        return left_sum || right_sum;
    }
    //最优递归：
/*    bool hasPathSum(TreeNode *root, int sum) {
        if (root == nullptr) {
            return false;
        }
        if (root->left == nullptr && root->right == nullptr) {
            return sum == root->val;
        }
        return hasPathSum(root->left, sum - root->val) ||
               hasPathSum(root->right, sum - root->val);
    }*/

public:
// 572. Subtree of Another Tree (Easy)

    int sum_count = 0;

    int pathSum(TreeNode* root, int sum) {
        if (root == nullptr) {
            return false;
        }
        hasPathSum(root, sum);
        pathSum(root->left, sum);
        pathSum(root->right, sum);
        return sum_count;
    }

    void pathSum_hasPathSum(TreeNode *root, int sum) {
        tree_sum += root->val;//加上当前节点的val
        if (tree_sum == sum) {
            sum_count++;
        }
        if (root->left) {
            pathSum_hasPathSum(root->left, sum);
        }
        if (root->right) {
            pathSum_hasPathSum(root->right, sum);
        }
        tree_sum -= root->val;
    }
};


int main() {
    TreeNode *a = new TreeNode(9);
    TreeNode *b = new TreeNode(-6);
    TreeNode *c = new TreeNode(5);
    TreeNode *root = new TreeNode(8);
    root->left = a;
    root->right = b;
    b->left = c;
    Solution test;
    cout << test.hasPathSum(root, 1);
}