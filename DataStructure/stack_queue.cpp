//
// Created by logan on 2020/7/20.
// 232. Implement Queue using Stacks (Easy)
// 225. Implement Stack using Queues (Easy)
#include <stack>
#include <deque>
#include <vector>

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
