//
// Created by logan on 2020/9/16.
//
// 160. Intersection of Two Linked Lists (Easy)
// 206. Reverse Linked List (Easy)
// 21. Merge Two Sorted Lists (Easy)
// 83. Remove Duplicates from Sorted List (Easy)
// 19. Remove Nth Node From End of List (Medium)
// 24. Swap Nodes in Pairs (Medium)
// 445. Add Two Numbers II (Medium)
// 234. Palindrome Linked List (Easy)
// 725. Split Linked List in Parts(Medium)
// 328. Odd Even Linked List (Medium)
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

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
        auto cur = head;
        while (n != 0) {//拉开距离
            cur = cur->next;
            n--;
        }
        if (cur == nullptr) return pre->next;
        while (cur->next != nullptr) {
            cur = cur->next;
            pre = pre->next;
        }
        pre->next = pre->next->next;
        return head;
    }

// 24. Swap Nodes in Pairs (Medium)
    ListNode *swapPairs(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return head;
        auto ans = head->next;
        swapPairs_help(nullptr, head);
        return ans;
    }

    void swapPairs_help(ListNode *pre, ListNode *head) {
        if (head == nullptr) return;
        auto cur = head;
        auto aft = head->next;
        if (aft == nullptr) return;
        cur->next = aft->next;
        aft->next = cur;
        if (pre != nullptr) {//不是首节点
            pre->next = aft;
        }
        swapPairs_help(cur, cur->next);
    }

// 445. Add Two Numbers II (Medium)
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        stack<int> s1, s2;
        while (l1 != nullptr) {
            s1.push(l1->val);
            l1 = l1->next;
        }
        while (l2 != nullptr) {
            s2.push(l2->val);
            l2 = l2->next;
        }
        ListNode *ans = nullptr;
        int add = 0, ref1 = 0, ref2 = 0;
        while (!s1.empty() || !s2.empty() || add != 0) {
            if (!s1.empty()) {
                ref1 = s1.top();
                s1.pop();
            } else ref1 = 0;
            if (!s2.empty()) {
                ref2 = s2.top();
                s2.pop();
            } else ref2 = 0;
            //求和
            int node_value = ref1 + ref2 + add;
            add = node_value / 10;
            auto *temp = new ListNode(node_value % 10);
            //尾插
            temp->next = ans;
            ans = temp;
        }
        return ans;
    }

// 234. Palindrome Linked List (Easy)
    bool isPalindrome(ListNode *head) {
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

// 725. Split Linked List in Parts(Medium)
    vector<ListNode *> splitListToParts(ListNode *root, int k) {
        vector<ListNode *> ans(k);
        int size = 0;
        auto *l1 = root;
        while (l1 != nullptr) {
            size++;
            l1 = l1->next;
        }
        ListNode *vec_list = root;//每个vector的元素
        int aver_len = size / k;//平均长度
        int bonus = size % k;//有余数，长度+1
        while (k != 0) {
            auto *temp = vec_list;
            int final_len = aver_len + bonus;
            while (final_len >= 1) {
                temp = temp->next;
                final_len--;
            }
            //temp不为空，断链
            if (temp != nullptr) {
                auto *next = temp->next;
                temp->next = nullptr;
                ans.push_back(vec_list);
                vec_list = next;
            } else{

            }
            if (bonus != 0) bonus--;
            k--;
        }
        return ans;
    }

// 328. Odd Even Linked List (Medium)
    ListNode* oddEvenList(ListNode* head) {
        auto *odd = new ListNode(1);
        auto odd_head = odd;
        auto *even = new  ListNode(1);
        auto even_head = even;
        int flag = 1;
        while(head != nullptr){
            if(flag == 1){//奇数节点插入奇数链表
                odd->next = head;
                odd = head;
                head = head->next;
                odd->next = nullptr;
                flag = 0;
            }else {//偶数节点插入偶数链表
                even->next = head;
                even = head;
                head = head->next;
                even->next = nullptr;
                flag = 1;
            }
        }
        odd->next = even_head->next;
        return odd_head->next;
    }
};

int main() {
    Solution s;
    auto root = new ListNode(1);
    auto l1 = new ListNode(2);
    auto l2 = new ListNode(2);
    auto l3 = new ListNode(1);
    root->next = l1;
    l1->next = l2;
    l2->next = l3;
    s.isPalindrome(root);
}