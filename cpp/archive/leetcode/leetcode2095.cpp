#include <bits/stdc++.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

#include <array>

#include "backward.hpp"
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
   public:
    bool fast_go(ListNode*& cur) {
        if (cur->next == nullptr) return false;
        cur = cur->next;
        if (cur->next == nullptr) return true;
        cur = cur->next;
        return true;
    }
    ListNode* deleteMiddle(ListNode* head) {
        if (head->next == nullptr) return nullptr;
        auto fastptr = head;
        auto slowptr = head;
        auto slowptr_1 = head;
        while (fast_go(fastptr)) {
            slowptr_1 = slowptr;
            slowptr = slowptr->next;
        }

        // delete slowptr node
        slowptr_1->next = slowptr->next;
        delete slowptr;
        slowptr = nullptr;
        return head;
    }
};
