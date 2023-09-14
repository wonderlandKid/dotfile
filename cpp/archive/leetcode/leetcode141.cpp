// Definition for singly-linked list.
#include <cstdio>
#include <iostream>
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
   public:
    bool hasCycle(ListNode* head) {
        ListNode* p1 = head;
        if (p1 == nullptr) return false;
        auto p2 = p1->next;
        while (p1 != p2) {
            if (p1 == nullptr || p2 == nullptr) return false;
            p1 = p1->next;
            p2 = p2->next;
            if (p2 == nullptr) return false;
            p2 = p2->next;
        }
        return true;
    }
};

int main() {
    ListNode* a = new ListNode(3);
    ListNode* b = new ListNode(2);
    ListNode* c = new ListNode(0);
    ListNode* d = new ListNode(-4);

    a->next = b;
    b->next = c;
    c->next = d;
    d->next = b;
    Solution wow;
    printf("%d", wow.hasCycle(a));
}
