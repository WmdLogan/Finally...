//
// Created by logan on 2020/9/16.
//
// 160. Intersection of Two Linked Lists (Easy)
// 206. Reverse Linked List (Easy)
struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
// 160. Intersection of Two Linked Lists (Easy)
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *l1 = headA;
        ListNode *l2 = headB;
        while (l1 != l2) {
            l1 = (l1 == nullptr) ? headB : l1->next;
            l2 = (l2 == nullptr) ? headA : l2->next;
        }
        return l1;
    }

// 206. Reverse Linked List (Easy)
    ListNode* reverse(ListNode* pre,ListNode* cur){
        if(cur == nullptr) return pre;
        ListNode* temp = cur->next;
        cur->next = pre;
        // 可以和双指针法的代码进行对比，如下递归的写法，其实就是做了这两步
        // pre = cur;
        // cur = temp;
        return reverse(cur,temp);
    }
    ListNode* reverseList(ListNode* head) {
        // 和双指针法初始化是一样的逻辑
        // ListNode* cur = head;
        // ListNode* pre = NULL;
        return reverse(nullptr, head);
    }
};