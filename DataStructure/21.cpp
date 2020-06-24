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
        if (l1 == nullptr && l2 != nullptr) {
            return l2;
        } else if (l1 != nullptr && l2 == nullptr) {
            return l1;
        } else if (l1 == nullptr && l2 == nullptr) {
            return nullptr;
        }
        //head
        ListNode *m = nullptr;
        if (l1->val >= l2->val) {
            m = new ListNode(l2->val);
            l2 = l2->next;
        } else {
            m = new ListNode(l1->val);
            l1 = l1->next;
        }
        //insert tail
        ListNode *t = m;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val >= l2->val) {
                auto *temp = new ListNode(l2->val);
                t->next = temp;
                t = temp;
                l2 = l2->next;
            } else {
                auto *temp = new ListNode(l1->val);
                t->next = temp;
                t = temp;
                l1 = l1->next;
            }
        }
        while (l1 != nullptr) {
            auto *temp = new ListNode(l1->val);
            t->next = temp;
            t = temp;
            l1 = l1->next;
        }
        while (l2 != nullptr) {
            auto *temp = new ListNode(l2->val);
            t->next = temp;
            t = temp;
            l2 = l2->next;
        }
        return m;
    }
};
int main(){
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