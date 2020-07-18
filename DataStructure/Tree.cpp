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
// 101. Symmetric Tree (Easy)
// 111. Minimum Depth of Binary Tree (Easy)
// 404. Sum of Left Leaves (Easy)
// 687. Longest Univalue Path (Easy)
// 337. House Robber III (Medium)
// 671. Second Minimum Node In a Binary Tree (Easy)
// 637. Average of Levels in Binary Tree (Easy)
// 513. Find Bottom Left Tree Value (Easy)
// 144. Binary Tree Preorder Traversal (Medium)
// 145. Binary Tree Postorder Traversal (Medium)
// 94. Binary Tree Inorder Traversal (Hard)
// 669. Trim a Binary Search Tree (Easy)
// 230. Kth Smallest Element in a BST (Medium)
// 538. Convert BST to Greater Tree (Easy)
// 235. Lowest Common Ancestor of a Binary Search Tree (Easy)
// 236. Lowest Common Ancestor of a Binary Tree (Medium)
// 108. Convert Sorted Array to Binary Search Tree (Easy)
// 109. Convert Sorted List to Binary Search Tree (Medium)
// 653. Two Sum IV - Input is a BST (Easy)
#include <iostream>
#include <deque>
#include <set>
#include <vector>
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
// 437. Path Sum III (Easy)
    int sum_count = 0;

    int pathSum(TreeNode *root, int sum) {
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

// 572. Subtree of Another Tree (Easy)
    bool traverse(TreeNode *s, TreeNode *t) {//判断t是否为s的子树
        bool l_result = false;
        bool r_result = false;
        if (s && t) {//s和t都存在，判断是否相等
            if (s->val == t->val) {
                l_result = traverse(s->left, t->left);
                r_result = traverse(s->right, t->right);
                return r_result && l_result;
            }
        } else if (!s && !t) {//s和t都不存在,true
            return true;
        }
        return false;
    }

    bool re = false;

    bool isSubtree(TreeNode *s, TreeNode *t) {
        bool result = false;
        if (s == nullptr) {
            return false;
        }
        if (s->val == t->val) {
            result = traverse(s, t);
            if (result) {
                re = true;
            }
        }
        isSubtree(s->left, t);
        isSubtree(s->right, t);
        return re;
    }

//101. Symmetric Tree
    bool check(TreeNode *p, TreeNode *q) {
        if (!p && !q) return true;
        if (!p || !q) return false;
        return p->val == q->val && check(p->left, q->right) && check(p->right, q->left);
    }

    bool isSymmetric(TreeNode *root) {
        return check(root, root);
    }

//111. Minimum Depth of Binary Tree

    int minDepth(TreeNode *root) {
        deque<TreeNode *> min_depth;
        if (root == nullptr) { return 0; }
        min_depth.push_back(root);
        int depth = 0;
        while (1) {
            depth++;
            int num = min_depth.size();
            for (int i = 1; i <= num; i++) {
                TreeNode *p = min_depth.front();
                min_depth.pop_front();
                if (!p->left && !p->right) { return depth; }
                if (p->right) {
                    min_depth.push_back(p->right);
                }
                if (p->left) {
                    min_depth.push_back(p->left);
                }
            }
        }
    }

//404. Sum of Left Leaves
    int left_sum = 0;

    int sumOfLeftLeaves(TreeNode *root) {
        if (!root) { return 0; }
        sumOfLeftLeaves_pre(root);
        return left_sum;
    }

    void sumOfLeftLeaves_pre(TreeNode *root) {
        if (root->left) {
            if (!root->left->left && !root->left->right) {
                left_sum += root->left->val;
            }
            sumOfLeftLeaves_pre(root->left);
        }
        if (root->right) {
            sumOfLeftLeaves_pre(root->right);
        }
    }

//！！！ 687. Longest Univalue Path  ！！！
    int help(TreeNode *node, int &ans) {
        if (node == nullptr) return 0;

        int left = help(node->left, ans);
        int right = help(node->right, ans);

        left = (node->left != nullptr && node->val == node->left->val) ? left + 1 : 0;
        right = (node->right != nullptr && node->val == node->right->val) ? right + 1 : 0;

        ans = max(ans, left + right);
        return max(left, right);
    }

    int longestUnivaluePath(TreeNode *root) {
        int ans = 0;
        help(root, ans);
        return ans;
    }

//337. House Robber III (Medium)：未通过（动态规划）
    int rob(TreeNode *root) {
        if (root == nullptr) return 0;

        int money = root->val;
        if (root->left != nullptr) {
            money += (rob(root->left->left) + rob(root->left->right));
        }

        if (root->right != nullptr) {
            money += (rob(root->right->left) + rob(root->right->right));
        }

        return max(money, rob(root->left) + rob(root->right));

    }

//671. Second Minimum Node In a Binary Tree (Easy)
    int findSecondMinimumValue(TreeNode *root) {
        set<int> s;
        if (root == nullptr) { return 0; }
        deque<TreeNode *> deque;
        deque.push_back(root);
        while (!deque.empty()) {
            int num = deque.size();
            for (int i = 0; i < num; ++i) {
                TreeNode *temp = deque.front();
                s.insert(temp->val);
                deque.pop_front();
                if (temp->left) deque.push_back(temp->left);
                if (temp->right) deque.push_back(temp->right);
            }
        }
        set<int>::iterator it = s.begin();
        return s.size() > 1 ? *++it : -1;
    }

//637. Average of Levels in Binary Tree (Easy)
    vector<double> averageOfLevels(TreeNode *root) {
        vector<double> vector;
        if (root == nullptr) { return vector; }
        deque<TreeNode *> deque;
        deque.push_back(root);
        while (!deque.empty()) {
            int num = deque.size();
            double sum = 0.0;
            for (int i = 0; i < num; ++i) {
                TreeNode *temp = deque.front();
                sum += temp->val;
                deque.pop_front();
                if (temp->left) deque.push_back(temp->left);
                if (temp->right) deque.push_back(temp->right);
            }
            sum /= num;
            vector.push_back(sum);
        }
        return vector;
    }

//513. Find Bottom Left Tree Value (Easy)
    int findBottomLeftValue(TreeNode *root) {
        deque<TreeNode *> deque;
        deque.push_back(root);
        int left;
        while (!deque.empty()) {
            int num = deque.size();
            for (int i = 0; i < num; ++i) {
                TreeNode *temp = deque.front();
                if (i == 0) {
                    left = temp->val;
                }
                deque.pop_front();
                if (temp->left) deque.push_back(temp->left);
                if (temp->right) deque.push_back(temp->right);
            }
        }
        return left;
    }

//144. Binary Tree Preorder Traversal (Medium)
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> res;  //保存结果
        int num;
        if (root == nullptr) { return res; }
        stack<TreeNode *> call;  //调用栈
        call.push(root);  //首先介入root节点
        while (!call.empty()) {
            num = call.size();
            for (int i = 0; i < num; ++i) {
                TreeNode *t = call.top();
                call.pop();  //访问过的节点弹出
                res.push_back(t->val);
                if (t->right) call.push(t->right);  //右节点先压栈，最后处理
                if (t->left) call.push(t->left);
            }
        }
        return res;
    }

//145. Binary Tree Postorder Traversal (Hard)
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> res;
        stack<TreeNode *> call;
        if (root != nullptr) call.push(root);
        while (!call.empty()) {
            TreeNode *t = call.top();
            call.pop();
            if (t != nullptr) {
                call.push(t);  //在右节点之前重新插入该节点，以便在最后处理（访问值）
                call.push(nullptr); //nullptr跟随t插入，标识已经访问过，还没有被处理
                if (t->right) call.push(t->right);
                if (t->left) call.push(t->left);
            } else {
                res.push_back(call.top()->val);
                call.pop();
            }
        }
        return res;
    }

// 94. Binary Tree Inorder Traversal (Medium)
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> res;
        stack<TreeNode *> call;
        if (root != nullptr) call.push(root);
        while (!call.empty()) {
            TreeNode *t = call.top();
            call.pop();
            if (t != nullptr) {
                if (t->right) call.push(t->right);
                call.push(t);  //在左节点之前重新插入该节点，以便在左节点之后处理（访问值）
                call.push(nullptr); //nullptr跟随t插入，标识已经访问过，还没有被处理
                if (t->left) call.push(t->left);
            } else {
                res.push_back(call.top()->val);
                call.pop();
            }
        }
        return res;
    }

//669. Trim a Binary Search Tree (Easy)
    TreeNode *trimBST(TreeNode *root, int L, int R) {
        if (root == nullptr) {
            return root;
        }
        if (root->val > R) {
            return trimBST(root->left, L, R); //只处理左子树，相当于剪掉了root及其右子树
        }
        if (root->val < L) {
            return trimBST(root->right, L, R); //只处理右子树，相当于剪掉了root及其左子树
        }

        root->left = trimBST(root->left, L, R);
        root->right = trimBST(root->right, L, R);

        return root;
    }

//230. Kth Smallest Element in a BST (Medium)
    int kthSmallest(TreeNode *root, int k) {
        if (root == nullptr) {
            return 0;
        }
        int result;
        stack<TreeNode *> call;
        call.push(root);
        while (k > 0) {
            TreeNode *temp = call.top();
            call.pop();
            if (temp) {
                if (temp->right) call.push(temp->right);
                call.push(temp);
                call.push(nullptr);
                if (temp->left) call.push(temp->left);
            } else {
                k--;
                result = call.top()->val;
                call.pop();
            }
        }
        return result;
    }

// 538. Convert BST to Greater Tree (Easy)
    TreeNode *convertBST(TreeNode *root) {
        if (root == nullptr) { return root; }
        stack<TreeNode *> call;
        call.push(root);
        int last_sum = 0;
        while (!call.empty()) {
            TreeNode *temp = call.top();
            call.pop();
            if (temp) {
                if (temp->left) call.push(temp->left);
                call.push(temp);
                call.push(nullptr);
                if (temp->right) call.push(temp->right);
            } else {
                call.top()->val += last_sum;
                last_sum = call.top()->val;
                call.pop();
            }
        }
        return root;
    }

// 235. Lowest Common Ancestor of a Binary Search Tree (Easy)
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (root == nullptr) return root;
        while ((root->val > p->val && root->val > q->val) || (root->val < p->val && root->val < q->val)) {
            if ((root->val > p->val && root->val > q->val)) root = root->left;
            if ((root->val < p->val && root->val < q->val)) root = root->right;
        }
        return root;
    }

// 236. Lowest Common Ancestor of a Binary Tree (Medium)
    TreeNode *ans;

    bool dfs(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (root == nullptr) return false;
        bool lson = dfs(root->left, p, q);
        bool rson = dfs(root->right, p, q);
        if ((lson && rson) || ((root->val == p->val || root->val == q->val) && (lson || rson))) {
            ans = root;
        }
        return lson || rson || (root->val == p->val || root->val == q->val);
    }

    TreeNode *lowestCommonAncestor_bt(TreeNode *root, TreeNode *p, TreeNode *q) {
        dfs(root, p, q);
        return ans;
    }

//108. Convert Sorted Array to Binary Search Tree (Easy)
    TreeNode *sortedArrayToBST(vector<int> &nums) {
        return helper(nums, 0, nums.size() - 1);
    }

    TreeNode *helper(vector<int> &nums, int left, int right) {
        if (left > right) {
            return nullptr;
        }

        // 总是选择中间位置左边的数字作为根节点
        int mid = (left + right) / 2;

        TreeNode *root = new TreeNode(nums[mid]);
        root->left = helper(nums, left, mid - 1);
        root->right = helper(nums, mid + 1, right);
        return root;
    }

// 109. Convert Sorted List to Binary Search Tree (Medium)
    struct ListNode {
        int val;
        ListNode *next;

        ListNode(int x) : val(x), next(NULL) {}
    };

    TreeNode *sortedListToBST(ListNode *head) {
        vector<int> nums;
        while (head) {
            nums.push_back(head->val);
            head = head->next;
        }
        return helper(nums, 0, nums.size() - 1);
    }

// 653. Two Sum IV - Input is a BST (Easy)
    bool findTarget(TreeNode *root, int k) {
        if (root == nullptr) return false;
        vector<int> tree;
        InOrderTraverse(root, k, tree);
        int first = 0;
        int last = tree.size() - 1;
        while (first != last) {
            int result = tree[first] + tree[last];
            if (result == k) return true;
            else if (result > k) last--;
            else first++;
        }
        return false;
    }

    void InOrderTraverse(TreeNode *root, int k, vector<int>& tree) {
        stack<TreeNode *> call;
        call.push(root);
        while (!call.empty()) {
            TreeNode *temp = call.top();
            call.pop();
            if (temp) {
                if (temp->right) call.push(temp->right);
                call.push(temp);
                call.push(nullptr);
                if (temp->left) call.push(temp->left);
            } else {
                int curr = call.top()->val;
                tree.push_back(curr);
                call.pop();
            }
        }
    }
};


int main() {
    TreeNode *a = new TreeNode(1);
    TreeNode *b = new TreeNode(3);
    TreeNode *c = new TreeNode(2);
    TreeNode *d = new TreeNode(4);
    TreeNode *root = new TreeNode(2);
    root->left = a;
    root->right = b;
    // a->left = c;
    //a->right = d;
    Solution test;
    test.findTarget(root, 1);
}