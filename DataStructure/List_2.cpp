//
// Created by logan on 2020/9/16.
//
// 160. Intersection of Two Linked Lists (Easy)
// 206. Reverse Linked List (Easy)
// 21. Merge Two Sorted Lists (Easy)
// 83. Remove Duplicates from Sorted List (Easy)
// 19. Remove Nth Node From End of List (Medium)
struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
// 160. Intersection of Two Linked Lists (Easy)
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
//利用链表长度
        ListNode *l1 = headA;
        ListNode *l2 = headB;
        while (l1 != l2) {
            l1 = (l1 == nullptr) ? headB : l1->next;
            l2 = (l2 == nullptr) ? headA : l2->next;
        }
        return l1;
    }

// 206. Reverse Linked List (Easy)
    ListNode *reverse(ListNode *pre, ListNode *cur) {
        if (cur == nullptr) return pre;
        ListNode *temp = cur->next;
        cur->next = pre;
        // 可以和双指针法的代码进行对比，如下递归的写法，其实就是做了这两步
        // pre = cur;
        // cur = temp;
        return reverse(cur, temp);
    }

    ListNode *reverseList(ListNode *head) {
        // 和双指针法初始化是一样的逻辑
        // ListNode* cur = head;
        // ListNode* pre = NULL;
        return reverse(nullptr, head);
    }

// 21. Merge Two Sorted Lists (Easy)
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        auto *preHead = new ListNode(-1);
//维护preHead的next。调整其指向
        ListNode *prev = preHead;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val < l2->val) {
                prev->next = l1;
                l1 = l1->next;
            } else {
                prev->next = l2;
                l2 = l2->next;
            }
            prev = prev->next;
        }

        // 合并后 l1 和 l2 最多只有一个还未被合并完，我们直接将链表末尾指向未合并完的链表即可
        prev->next = l1 == nullptr ? l2 : l1;

        return preHead->next;
    }

// 83. Remove Duplicates from Sorted List (Easy)
    ListNode *deleteDuplicates(ListNode *head) {
        if (head == nullptr) return head;
        auto l = head;
        auto cur = head->next;
        while (cur != nullptr) {
            if (l->val == cur->val) {
                l->next = cur->next;
                cur = cur->next;
            } else {
                l = l->next;
                cur = cur->next;
            }
        }
        return head;
    }

// 19. Remove Nth Node From End of List (Medium)
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        auto pre = head;
        auto cur = head->next;
        while (n != 1) {
            cur = cur->next;
            n--;
        }
        while (cur != nullptr) {
            pre = pre->next;
            cur = cur->next;
        }
        if (pre == nullptr) return pre;
        pre->next = pre->next->next;
        return head;
    }
};