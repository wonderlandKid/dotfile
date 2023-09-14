#include <bits/stdc++.h>

#include <algorithm>
#include <cstdio>
using namespace std;
/**/
// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};
struct mypair {
  int i;    // 几号元素
  int val;  // 值
};
class Solution {
 public:
  vector<int> nextLargerNodes(ListNode *head) {
    vector<mypair> stk;
    vector<int> result;
    result.reserve(100);
    int i = 0;
    while (head != nullptr) {
      if (stk.empty()) {
        stk.push_back({i, head->val});
        i++;
        head = head->next;
        continue;
      }
      if (stk.back().val >= head->val) {
        stk.push_back({i, head->val});
      } else {
        // 弹栈弹到不大于的
        //  for (auto i : stk) {
        //    result.push_back(head->val);
        //  }
        //  stk.clear();
        //  stk.push_back({i, head->val});
        // printf("现在遇到一个比stk大的, 是%d号元素, 值是%d\n", i, head->val);
        int j = 0;
        while (1) {
          if (stk[j].val < head->val) break;
          j++;
        }
        // 现在j到end()之间是需要弹出的
        // printf("j找到的是%d, 意味着j到尾部需要弹出\n", j);
        result.resize(stk.back().i + 1, 0);
        // cout << "resize之后的result:" << endl;
        // for (auto i : result) printf("%d ", i);
        // cout << endl;
        for (int k=j; k <= stk.size() - 1; k++) {
          result[stk[k].i] = head->val;
        }
        stk.erase(stk.begin() + j, stk.end());
        // cout << "擦除后的栈:" << endl;
        // for (auto i : stk) {
          // printf("%d号%d ", i.i, i.val);
        // }
        // cout << endl << endl;
        stk.push_back({i, head->val});
      }

      i++;
      head = head->next;
    }

    // 对于循环结束还在栈中的元素
    int maxnumber = 0;
    for (auto i : stk) {
      if (i.i > maxnumber) maxnumber = i.i;
    }
    stk.clear();
    stk.shrink_to_fit();
    result.resize(maxnumber + 1, 0);
    return result;
  }
};

int main() {
  ListNode *a = new ListNode(5);
  ListNode *b = new ListNode(2);
  ListNode *c = new ListNode(5);
  // ListNode *d = new ListNode(3);
  // ListNode *e = new ListNode(5);
  a->next = b;
  b->next = c;
  c->next = nullptr;
  // d->next = e;
  // e->next = nullptr;
  Solution test;
  auto testresult = test.nextLargerNodes(a);
  for(auto &i:testresult) printf("%d ", i);
  return 0;
}
