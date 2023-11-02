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
    bool try_step_two(ListNode*& cur) {
        if (cur->next == nullptr || cur->next->next == nullptr) return false;
        cur = cur->next->next;
        return true;
    }

    void move_node(ListNode* psrc, ListNode* pdes) {
        // move node behind PDES after the PSRC
        ListNode* npdes = pdes->next;
        if(npdes == nullptr) return ;
        ListNode* nnpdes = npdes->next;
        ListNode* npsrc = psrc->next;
        psrc->next = npdes;
        npdes->next = npsrc;
        pdes->next = nnpdes;
        return;
    }

    ListNode* oddEvenList(ListNode* head) {
        if (head->next == nullptr) return head;
        auto pctor = head;
        auto pmove = head->next;

        while (true) {
            auto copypmove = pmove;
            if (try_step_two(pmove)) {
                move_node(pctor, copypmove);
                pctor = pctor->next;
            } else {
                move_node(pctor, pmove);
                break;
            }
        }
        return head;
    }
};

int main(int argc, char* argv[]) {
    ListNode* head = new ListNode(
        1,
        new ListNode(
            2,
            new ListNode(
                3, new ListNode(
                       4, new ListNode(
                              5, new ListNode(
                                     6, new ListNode(7, new ListNode(8))))))));
    Solution a;
    auto i = a.oddEvenList(head);
    return 0;
}
