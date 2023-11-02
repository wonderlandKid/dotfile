#include <bits/stdc++.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

#include <array>
#include <optional>

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
    optional<ListNode*> get_next(ListNode* const& cur) {
        if (cur==nullptr || cur->next == nullptr)
            return nullopt;
        else {
            return cur->next;
        }
    }

    optional<int> get_val(ListNode* const& cur) {
        if (cur == nullptr)
            return nullopt;
        else {
            return cur->val;
        }
    }

    ListNode* reverseList(ListNode* head) {
        auto p1 = head;
        ListNode* p2 = nullptr;
        try {
            p2 = get_next(p1).value();
        } catch (const std::exception& e) {
            return p1;
        }

        p1->next = nullptr;
        while (true) {
            ListNode* tmp = nullptr;
            if (get_next(p2).has_value()) {
                tmp = get_next(p2).value();
                p2->next = p1;
                p1 = p2;
                p2 = tmp;
            } else {
                // 下一个没有值了
                p2->next = p1;
                return p2;
            }
        }
        return nullptr;
    }
};

void print_linked_list(ListNode* root) {
    while (root != nullptr) {
        cout << root->val << endl;
        root = root->next;
    }
    return;
}

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
    auto b = a.reverseList(head);
    print_linked_list(b);
    return 0;
}
