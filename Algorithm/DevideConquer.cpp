//
// Created by logan on 2020/8/10.
//
// 241. Different Ways to Add Parentheses (Medium)
// 95. Unique Binary Search Trees II (Medium)

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
// 241. Different Ways to Add Parentheses (Medium)
    vector<int> diffWaysToCompute(string input) {
        vector<int> ways;
        for (int i = 0; i < input.length(); i++) {
            char c = input[i];
            if (c == '+' || c == '-' || c == '*') {//在运算符号处分开多项式
                vector<int> left = diffWaysToCompute(input.substr(0, i));//计算运算符号左边多项式所有可能结果
                vector<int> right = diffWaysToCompute(input.substr(i + 1));//计算运算符号右边多项式所有可能结果
                for (int l : left) {
                    for (int r : right) {
                        switch (c) {//根据运算符号计算左右侧多项式的结果
                            case '+':
                                ways.push_back(l + r);
                                break;
                            case '-':
                                ways.push_back(l - r);
                                break;
                            case '*':
                                ways.push_back(l * r);
                                break;
                        }
                    }
                }
            }
        }
        if (ways.size() == 0) {
            int num = stoi(input); //数组空说明多项式为单个数字，要先转化为数字再入数组
            ways.push_back(num);
        }
        return ways;
    }

// 95. Unique Binary Search Trees II (Medium)
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode() : val(0), left(nullptr), right(nullptr) {}

        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    vector<vector<vector<TreeNode *>>> memo;

    vector<TreeNode *> generateTrees(int start, int end) {
        if (start > end) return {nullptr};
        if (!memo[start][end].empty()) return memo[start][end];
        vector<TreeNode *> allTrees;
        // 枚举可行根节点
        for (int i = start; i <= end; i++) {
            // 获得所有可行的左子树集合
            vector<TreeNode *> leftTrees = generateTrees(start, i - 1);

            // 获得所有可行的右子树集合
            vector<TreeNode *> rightTrees = generateTrees(i + 1, end);

            // 从左子树集合中选出一棵左子树，从右子树集合中选出一棵右子树，拼接到根节点上
            for (auto &left : leftTrees) {
                for (auto &right : rightTrees) {
                    TreeNode *currTree = new TreeNode(i);//根节点
                    currTree->left = left;
                    currTree->right = right;
                    allTrees.emplace_back(currTree);//pushback优化
                }
            }
        }
        return memo[start][end] = allTrees;
    }

    vector<TreeNode *> generateTrees(int n) {
        if (!n) return {};
        memo.resize(n + 1, vector<vector<TreeNode *>>(n + 1));
        return generateTrees(1, n);
    }

};

int main() {
    Solution s;
    s.generateTrees(1, 3);
}