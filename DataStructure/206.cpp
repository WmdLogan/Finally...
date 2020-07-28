// Created by logan on 2020/6/23.
// 206. Reverse Linked List(Easy)
// 83. Remove Duplicates from Sorted List(Easy)
// 19. Remove Nth Node From End of List(Medium)
// 24. Swap Nodes in Pairs(Medium)
// !!! 445. Add Two Numbers II(Medium) !!!
// 234. Palindrome Linked List(Easy) 快慢指针一次遍历找到链表中点
// 725. Split Linked List in Parts(Medium)
// 142. Linked List Cycle II

/**
 * Definition for singly-linked list.*/
#include <iostream>
#include <stack>
#include <deque>
#include <vector>
#include <cmath>

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
        head = cur;//确定头节点
        while (pre->next != nullptr) {
            cur = pre->next;
            if (cur->next == nullptr) {//奇数个结点跳出
                break;
            }
            pre->next = pre->next->next;
            cur->next = cur->next->next;
            pre->next->next = cur;
            pre = cur;
        }
        return head;
    }

    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        stack<int> stack1;
        stack<int> stack2;
        while (l1 && l2) {
            stack1.push(l1->val);
            stack2.push(l2->val);
            l1 = l1->next;
            l2 = l2->next;
        }
        while (l1) {
            stack1.push(l1->val);
            l1 = l1->next;
        }
        while (l2) {
            stack2.push(l2->val);
            l2 = l2->next;
        }
        int pre = 0;//进位符
        int a1, a2;
        ListNode *re = nullptr;
        while (!stack1.empty() || !stack2.empty() || pre) {
            if (stack1.empty()) {
                a1 = 0;
            } else {
                a1 = stack1.top();
                stack1.pop();
            }
            if (stack2.empty()) {
                a2 = 0;
            } else {
                a2 = stack2.top();
                stack2.pop();
            }
            int sum = a1 + a2 + pre;
            pre = sum / 10;
            sum %= 10;
            auto *node = new ListNode(sum);
            node->next = re;
            re = node;
        }
        return re;
    }

    bool isPalindrome(ListNode *head) {
        int size = 0;
        ListNode *new_head = head;
        ListNode *r = nullptr;
        while (head) {//得到反转链表和链表长度 o(N)
            ListNode *temp = new ListNode(head->val);
            temp->next = r;
            r = temp;
            size++;
            head = head->next;
        }
        int half = size / 2;
        //比较两个链表前半部分是否相同 o(N)
        while (half > 0) {
            if (new_head->val == r->val) {
                half--;
                new_head = new_head->next;
                r = r->next;
            } else { break; }
        }
        return half == 0;
    }

    bool isPalindrome_1(ListNode *head) {
        if (head == nullptr) {
            return true;
        }
        deque<int> s;
        while (head) {
            s.push_back(head->val);
            head = head->next;
        }
        while (s.front() == s.back() && s.size() > 1) {
            s.pop_back();
            s.pop_front();
        }
        return s.size() <= 1;
    }

    bool isPalindrome_2(ListNode *head) {
        if (!head || !head->next) return true;
        ListNode *slow = head, *fast = head;
        // 将slow指针移动到链表中间位置
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        // 反转后半部分
        ListNode *curNode = slow, *nextNode = slow->next;
        while (nextNode) {
            ListNode *tmp = nextNode->next;
            nextNode->next = curNode;
            curNode = nextNode;
            nextNode = tmp;
        }
        slow->next = nullptr;
        // 开始比较是否相等
        while (head && curNode) {
            if (head->val != curNode->val)
                return false;
            head = head->next;
            curNode = curNode->next;
        }
        return true;
    }

    vector<ListNode *> splitListToParts(ListNode *root, int k) {
        vector<ListNode *> result;
        int len = 0;
        struct ListNode* p = root;
        while (p != nullptr) {  //记录长度
            len++;
            p = p->next;
        }
        for (int i = 0; k; i++, k--) {
            result.push_back(root);
            int size;
            if (len % k == 0) {
                 size = len / k;           //计算每组的大小
            } else {
                 size = len / k + 1;
            }
            len -= size;                         //更新剩余长度
            p = root;
            while ( --size && p != nullptr) {
                p = p->next;
            }
            struct ListNode *tmp = nullptr;         //截断链表
            if (p != nullptr) {
                tmp = p->next;
                p->next = nullptr;
            }
            root = tmp;
        }
        return result;
    }
// 142. Linked List Cycle II
    ListNode *detectCycle(ListNode *head) {
        ListNode *fast = head;
        ListNode *slow = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow) break;
        }
        if (fast == nullptr) return nullptr;
        if (fast->next == nullptr) return nullptr;
        fast = head;
        while (fast != slow) {
            fast = fast->next;
            slow = slow->next;
        }
        return fast;
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
/*    a2.next = &c1;
    c1.next = &c2;
    c2.next = &c3;*/

    b1.next = &b2;
    b2.next = &b3;
//    b3.next = &c1;
    Solution a;
    a.splitListToParts(&a1, 4);
}