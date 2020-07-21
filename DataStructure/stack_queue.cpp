//
// Created by logan on 2020/7/20.
// 232. Implement Queue using Stacks (Easy)
// 225. Implement Stack using Queues (Easy)
// 155. Min Stack (Easy)
// 20. Valid Parentheses (Easy)
// 739. Daily Temperatures (Medium)
#include <stack>
#include <deque>
#include <vector>
#include <set>
#include <map>

using namespace std;

// 232. Implement Queue using Stacks (Easy)
class MyQueue {
public:
    stack<int> stack1;
    stack<int> stack2;

    /** Initialize your data structure here. */
    MyQueue() {

    }

    /** Push element x to the back of queue. */
    void push(int x) {
        stack1.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                int temp = stack1.top();
                stack1.pop();
                stack2.push(temp);
            }
        }
        int result = stack2.top();
        stack2.pop();
        return result;
    }

    /** Get the front element. */
    int peek() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                int temp = stack1.top();
                stack1.pop();
                stack2.push(temp);
            }
        }
        return stack2.top();
    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return stack2.empty() && stack1.empty();
    }
};

// 225. Implement Stack using Queues (Easy)
class MyStack {
public:
    deque<int> deque;

    /** Initialize your data structure here. */
    MyStack() {

    }

    /** Push element x onto stack. */
    void push(int x) {
        deque.push_back(x);
        int num = deque.size();
        while (num > 1) {
            int temp = deque.front();
            deque.pop_front();
            deque.push_back(temp);
            num--;
        }
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int result = deque.front();
        deque.pop_front();
        return result;
    }

    /** Get the top element. */
    int top() {
        return deque.front();
    }

    /** Returns whether the stack is empty. */
    bool empty() {
        return deque.empty();
    }
};

// 155. Min Stack (Easy)
class MinStack {
public:
    stack<int> s;
    stack<int> stack_min;

    /** initialize your data structure here. */
    MinStack() {

    }

    void push(int x) {
        s.push(x);
        if (stack_min.empty()) stack_min.push(x);
        else {
            stack_min.push(min(x, stack_min.top()));
        }
    }

    void pop() {
        s.pop();
        stack_min.pop();
    }

    int top() {
        return s.top();
    }

    int getMin() {
        return stack_min.top();
    }
};

class Solution {
// 20. Valid Parentheses (Easy)
public:
    bool isValid(string s) {
        stack<char> pair;
        for (auto &c:s) {
            switch (c) {
                case '{' :
                    pair.push(c);
                    break;
                case '[' :
                    pair.push(c);
                    break;
                case '(' :
                    pair.push(c);
                    break;
                case '}' :
                    if (pair.empty()) {
                        pair.push(c);
                        break;
                    } else {
                        if (pair.top() == '{') {
                            pair.pop();
                            break;
                        } else {
                            pair.push(c);
                        }
                    }
                case ')' :
                    if (pair.empty()) {
                        pair.push(c);
                        break;
                    } else {
                        if (pair.top() == '(') {
                            pair.pop();
                            break;
                        } else {
                            pair.push(c);
                        }
                    }
                case ']' :
                    if (pair.empty()) {
                        pair.push(c);
                        break;
                    } else {
                        if (pair.top() == '[') {
                            pair.pop();
                            break;
                        } else {
                            pair.push(c);
                        }
                    }
                default:
                    break;
            }
        }
        return pair.empty();
    }

// 739. Daily Temperatures (Medium)
    vector<int> dailyTemperatures(vector<int>& T) {
        int n = T.size();
        vector<int> ans(n, 0);
        stack<int> s;
        for (int i = 0; i < n; ++i) {
            while (!s.empty() && T[i] > T[s.top()]) {
                int previousIndex = s.top();
                ans[previousIndex] = i - previousIndex;
                s.pop();
            }
            s.push(i);
        }
        return ans;
    }
};

int main() {
    string s = "]";
    Solution solution;
    solution.isValid(s);
}