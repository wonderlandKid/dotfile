
// Definition for singly-linked list.
#include <cstdlib>
#include <iostream>
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    auto copyA = headA;
    auto copyB = headB;
    int countA = 0;
    int countB = 0;
    while (headA != NULL) {
      countA++;
      headA = headA->next;
    }
    while (headB != NULL) {
      countB++;
      headB = headB->next;
    }
    ListNode *longone = NULL;
    ListNode *shortone = NULL;
    if (countA >= countB) {
      longone = copyA;
      shortone = copyB;
    } else {
      longone = copyB;
      shortone = copyA;
    }
    for (int i = 1; i <= abs(countA - countB); i++) {
      longone = longone->next;
    }
    while(longone!=NULL && shortone!=NULL){
        if(longone == shortone) return longone;
        longone=longone->next;
        shortone=shortone->next;
    }

    return NULL;
  }
};
