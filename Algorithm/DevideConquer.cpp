//
// Created by logan on 2020/8/10.
//
// 241. Different Ways to Add Parentheses (Medium)

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
            if (c == '+' || c == '-' || c == '*') {
                vector<int> left = diffWaysToCompute(input.substr(0, i));
                vector<int> right = diffWaysToCompute(input.substr(i + 1));
                for (int l : left) {
                    for (int r : right) {
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
            int num = stoi(input); //第一次触底进来的是字符串，要先转化为数字
            ways.push_back(num);
        }
        return ways;
    }
};