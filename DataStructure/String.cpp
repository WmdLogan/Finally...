//
// Created by logan on 2020/7/22.
//
// 242. Valid Anagram (Easy)

#include <stack>
#include <deque>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
// 242. Valid Anagram (Easy)
    bool isAnagram(string s, string t) {
        unordered_map<char, int> m;
        int flag1 = 0, flag2 = 0;
        for (char c:s) {
            flag1++;
            m[c]++;
        }
        for (char c:t) {
            flag2++;
            if (m[c] != 0) {
                m[c]--;
            } else {
                return false;
            }
        }
        if (flag1 != flag2) return false;
        return true;
    }

};

typedef struct DNode {
    int data;
    struct DNode *pre;
    struct DNode *next;
} DNode, *DList;

void insertSort(DList &l) {
    if (l == nullptr || l->next == nullptr) return;
    DNode *cur = l->next;
    while (cur) {
        DNode *next = cur->next;
        DNode *tmpDNode = cur->pre;
        while (tmpDNode && tmpDNode->data > cur->data) {
            tmpDNode = tmpDNode->pre;
        }
        if (tmpDNode == nullptr) {
            cur->pre->next = cur->next;
            if (cur->next != nullptr) cur->next->pre = cur->pre;
            l->pre = cur;
            cur->next = l;
            cur->pre = nullptr;
            l = cur;

        } else if (tmpDNode->next != cur) {
            cur->pre->next = cur->next;
            if (cur->next != nullptr) cur->next->pre = cur->pre;
            else {
                cur->pre = tmpDNode;
                cur->next = tmpDNode->next;
                tmpDNode->next->pre = cur;
                tmpDNode->next = cur;
            }
        }
        cur = next;
    }
    return;
}
