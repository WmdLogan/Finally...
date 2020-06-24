// 21. Merge Two Sorted Lists
// Created by logan on 2020/6/24.
// Easy

/*Definition for singly-linked list.*/

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        auto *m = new ListNode(0);
        //insert tail
        ListNode *t = m;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val >= l2->val) {
                t->next = l2;
                l2 = l2->next;
            } else {
                t->next = l1;
                l1 = l1->next;
            }
            t = t->next;
        }
        l1 == nullptr ? t->next = l2 : t->next = l1;
        return m->next;
    }
};

int main() {
    ListNode a3 = ListNode(4);
    ListNode a2 = ListNode(2, &a3);
    ListNode a1 = ListNode(1, &a2);
    ListNode b3 = ListNode(4);
    ListNode b2 = ListNode(3, &b3);
    ListNode b1 = ListNode(1, &b2);
    Solution s;
    s.mergeTwoLists(&a1, &b1);
    return 0;
}