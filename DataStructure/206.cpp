// 206. Reverse Linked List
// Created by logan on 2020/6/23.
// Easy
//83. Remove Duplicates from Sorted List

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
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr || head->next == nullptr){ return head; }
        ListNode *pre = head;
        ListNode *cur = pre->next;
        while (cur != nullptr) {
            if (pre->val == cur->val) {
                pre->next = cur->next;
                cur = cur->next;
                continue;
            }
            pre = pre->next;
            cur = cur->next;
        }
        return head;
    }
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
    ListNode a2(1);
    ListNode c1(2);
    ListNode c2(3);
    ListNode c3(3);
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