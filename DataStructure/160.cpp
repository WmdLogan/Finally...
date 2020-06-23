// 160. Intersection of Two Linked Lists
// Created by logan on 2020/6/22.
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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* l1 = headA;
        ListNode* l2 = headB;
        while (l1 != l2) {
            l1 = (l1 == NULL) ? headB : l1->next;
            l2 = (l2 == NULL) ? headA : l2->next;
        }
        return l1;
    }
};
int main(){
    ListNode a1(4);
    ListNode a2(1);
    ListNode c1(8);
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
    ListNode *re = a.getIntersectionNode(&a1, &b1);
    cout << re->val;
}