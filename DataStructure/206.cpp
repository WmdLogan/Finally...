// 206. Reverse Linked List
// Created by logan on 2020/6/23.
// Easy

/**
 * Definition for singly-linked list.*/
#include <iostream>

using namespace std;
struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

static const auto __ = []() // 最大子序列问题
{
    ios::sync_with_stdio(false);
// sync_with_stdio(false)是为了打断iostream输入输出到缓存，可以节约很多时间，使之与scanf相差无几。
    cin.tie(nullptr);
// tie是将两个stream板顶的函数，空参数的话返回当前的输出指针，即tie(0)与tie(nullptr)来解决cin与cout的绑定。
    return nullptr;
}();

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *re = NULL;
        while (head != NULL) {
            ListNode *temp = new ListNode(head->val);
            temp->next = re;
            re = temp;
            head = head -> next;
        }
        return re;
    }
};
int main(){
    ListNode a1(1);
    ListNode a2(2);
    ListNode c1(3);
    ListNode c2(4);
    ListNode c3(5);
    ListNode b1(5);
    ListNode b2(0);
    ListNode b3(1);
    a1.next = &a2;
    a2.next = &c1;
    c1.next = &c2;
    c2.next = &c3;

    b1.next = &b2;
    b2.next = &b3;
    b3.next = &c1;
    Solution a;
    ListNode *b = a.reverseList(&a1);
    while (b != NULL) {
        cout << b->val << " ";
        b = b->next;
    }
}