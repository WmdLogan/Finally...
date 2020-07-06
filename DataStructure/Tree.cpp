//
// Created by logan on 2020/7/6.
//104. Maximum Depth of Binary Tree (Easy)
// 110. Balanced Binary Tree (Easy)
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

    bool isBalanced(TreeNode* root) {
        if(!root) return true;

        int d = abs(maxDepth(root->left)-maxDepth(root->right)); //当前节点的左右子树的高度差

        return (d<=1) && (isBalanced(root->left)) && (isBalanced(root->right));
    }

};