#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
using namespace std;

class Node {
public:
  Node() {
    left = nullptr;
    right = nullptr;
  }
  Node(int _val) : val(_val), left(nullptr), right(nullptr) {}
  Node *left;
  Node *right;
  int val;
};

class Blist {
public:
  Blist() {
    begin = end = nullptr;
    for (int i = 0; i <= 100009; ++i)
      index[i] = nullptr;
    size = 0;
  }
  Node *begin;
  Node *end; // 只在插入的时候有用 进入交换阶段就不维护了
  Node *index[100010]; // 下标从0开始
  int size;
  void push(int x) {
    auto tmp = new Node(x);
    size++;
    if (end == nullptr) {
      index[size] = tmp;
      begin = end = tmp;
    } else {
      index[size] = tmp;
      end->right = tmp;
      tmp->left = end;
      end = end->right;
    }
  }
};

int main(void) {
  int n = 0, m = 0; // n苹果个数 m指令个数
  scanf("%d%d", &n, &m);
  Blist solution;
  for (int p1 = 1; p1 <= n; p1++) {
    int tmp = 0;
    solution.push(p1);
  }

  // 还是整个哨兵节点
  auto beforebegin = new Node;
  beforebegin->right = solution.begin;
  solution.begin->left = beforebegin;

  auto afterend = new Node;
  afterend->left = solution.end;
  solution.end->right = afterend;

  int flag = 0;
  for (int p1 = 1; p1 <= m; p1++) {
    scanf("%c", &flag);
    if (flag == '\n')
      scanf("%c", &flag);
    if (flag == 'L') {
      int i, j;
      scanf("%d%d", &i, &j); // i移到j左侧
      auto pi = solution.index[i];
      auto pj = solution.index[j];
      auto pileft = pi->left;
      auto piright = pi->right;
      auto pjleft = pj->left;
      auto pjright = pj->right;
      if (pj->left == pi)
        ;
      else {
        pi->right = pj;
        pj->left = pi;
        pi->left = pjleft;
        pjleft->right = pi;
        piright->left = pileft;
        pileft->right = piright;
      }

    } else if (flag == 'R') {
      int i, j;
      scanf("%d%d", &i, &j); // i移到j右侧
      auto pi = solution.index[i];
      auto pj = solution.index[j];
      auto pileft = pi->left;
      auto piright = pi->right;
      auto pjleft = pj->left;
      auto pjright = pj->right;
      if (pj->right == pi)
        ;
      else {
        pj->right = pi;
        pi->left = pj;
        pi->right = pjright;
        pjright->left = pi;
        piright->left = pileft;
        pileft->right = piright;
      }
    } else
      ;
  }
  auto temp = beforebegin->right;
  while (temp != afterend) {
    printf("%d ", temp->val);
    temp = temp->right;
  }
  return 0;
}