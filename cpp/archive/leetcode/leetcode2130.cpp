#include <bits/stdc++.h>

#include <array>
#include <optional>

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
    optional<int> get_val(ListNode* const& cur) {
        if (cur == nullptr) return nullopt;
        return cur->val;
    }

    optional<ListNode*> get_next(ListNode* const& cur) {
        // 如果说一个结点的next为nullptr 也不应该能够得到next
        if (cur == nullptr || cur->next == nullptr) return nullopt;
        return cur->next;
    }

    int pairSum(ListNode* head) {
        // 先拿到整个链表的长度减一
        // head的范围是2到10^5
        int whole_list_length = -1;
        auto tmp = head;
        while (true) {
            whole_list_length++;
            auto tmp_next = get_next(tmp);
            if (tmp_next)
                tmp = tmp_next.value();
            else
                break;
        }

        cout << whole_list_length;

        vector<int> array((whole_list_length + 1) / 2, 0);

        tmp = head;
        for (int i = 0; i <= whole_list_length; i++) {
            auto val = tmp->val;
            if (i <= whole_list_length / 2)
                array[i] += val;
            else
                array[whole_list_length - i] += val;
            tmp = tmp->next;
        }

        int maxval = 0;
        for (auto const& i : array) {
            if (i > maxval) maxval = i;
        }
        return maxval;
    }
};
