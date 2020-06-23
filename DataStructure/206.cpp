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
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *re = new ListNode(0);
        while (head != NULL) {
            ListNode *temp = new ListNode(head->val);
            temp->next = re->next;
            re->next = temp;
            head = head->next;
        }
        return re->next;
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