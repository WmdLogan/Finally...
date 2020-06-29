// 21. Merge Two Sorted Lists(Easy)
// Created by logan on 2020/6/24.
// 328. Odd Even Linked List(Medium)

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

    ListNode *oddEvenList(ListNode *head) {
        if (!head) {//空链表
            return head;
        }
        ListNode *p = head;
        ListNode *k_pre = head->next;//1个结点时，k_pre 为 nullptr
        ListNode *k;
        while (k_pre) {
            k = k_pre->next;
            //取出k结点
            if (k == nullptr) {//k_pre是最后一个结点
                break;
            }
            k_pre->next = k->next;
            //k结点插入到p后,p向后移动1个节点
            k->next = p->next;
            p->next = k;
            p = k;
            k_pre = k_pre->next;
        }
        return head;
    }
};

int main() {
    ListNode *d = nullptr;
    ListNode a1(1);
    ListNode a2(2);
    ListNode c1(3);
    ListNode c2(4);
    ListNode c3(5);
    ListNode b1(9);
    ListNode b2(0);
    ListNode b3(1);
    a1.next = &a2;
    a2.next = &c1;
    c1.next = &c2;
    c2.next = &c3;

    b1.next = &b2;
    b2.next = &b3;
//    b3.next = &c1;
    Solution a;
    a.oddEvenList(&a1);
    return 0;
}