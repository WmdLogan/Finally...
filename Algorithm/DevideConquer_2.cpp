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
// 241. 为运算表达式设计优先级
    vector<int> diffWaysToCompute(string input) {
        vector<int> ways;
        for (int i = 0; i < input.size(); ++i) {
            char c = input[i];
            //按照运算符号分割
            if (c == '+' || c == '-' || c == '*') {
                vector<int> left = diffWaysToCompute(input.substr(0, i));
                vector<int> right = diffWaysToCompute(input.substr(i + 1));
                for (int l:left) {
                    for (int r :right) {
                        switch (c) {
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
            int num = stoi(input);//第一次触底进来的是字符串，要先转化为数字
            ways.push_back(num);
        }
        return ways;
    }

// 95. 不同的二叉搜索树 II
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode() : val(0), left(nullptr), right(nullptr) {}

        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    vector<TreeNode *> generateTrees(int start, int end) {
        if (start > end) return {nullptr};
        vector<TreeNode *> allTrees;
        //枚举可行根节点
        for (int i = start; i <= end; ++i) {
            //获得所有可行的左子树集合
            vector<TreeNode *> leftTrees = generateTrees(start, i - 1);
            //获得所有可行的右子树集合
            vector<TreeNode *> rightTrees = generateTrees(i + 1, end);
            //从左子树集合中选出一棵左子树，从右子树中选出一棵右子树，拼接到根节点上
            for (auto &left : leftTrees) {
                for (auto &right:rightTrees) {
                    auto curTree = new TreeNode(i);
                    curTree->left = left;
                    curTree->right = right;
                    allTrees.emplace_back(curTree);
                }
            }
        }
        return allTrees;
    }

    vector<TreeNode *> generateTrees(int n) {
        if (n == 0) return {};
        return generateTrees(1, n);
    }

};

int main() {
    Solution s;
    string str = "2*3-4*5";
    s.diffWaysToCompute(str);
}