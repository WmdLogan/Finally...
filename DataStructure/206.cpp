// Created by logan on 2020/6/23.
// 206. Reverse Linked List(Easy)
// 83. Remove Duplicates from Sorted List(Easy)
// 19. Remove Nth Node From End of List(Medium)
// 24. Swap Nodes in Pairs

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
    ListNode *reverseList(ListNode *head) {
        ListNode *re = NULL;
        while (head != NULL) {
            ListNode *temp = new ListNode(head->val);
            temp->next = re;
            re = temp;
            head = head->next;
        }
        return re;
    }

    ListNode *deleteDuplicates(ListNode *head) {
        if (head == nullptr || head->next == nullptr) { return head; }
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

    ListNode *removeNthFromEnd(ListNode *head, int n) {
        if (n == 0) {
            return head;
        }
        ListNode *h = head;
        ListNode *end = head;
        while (end != nullptr) {
            if (n >= 0) {
                end = end->next;
                n--;
            } else {
                h = h->next;
                end = end->next;
            }
        }
        if (n == 0) {
            return head->next;
        }
        h->next = h->next->next;
        return head;
    }

    ListNode *swapPairs(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode *pre = head;
        ListNode *cur = head->next;
        pre->next = cur->next;
        cur->next = pre;
        head = cur;
        while (pre->next != nullptr) {
            cur = pre->next;
            if (cur->next == nullptr) {
                break;
            }
            pre->next = pre->next->next;
            cur->next = cur->next->next;
            pre->next->next = cur;
            pre = cur;
        }
        return head;
    }
};

int main() {
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
    ListNode *b = a.swapPairs(&a1);

    while (b != NULL) {
        cout << b->val << " ";
        b = b->next;
    }
}