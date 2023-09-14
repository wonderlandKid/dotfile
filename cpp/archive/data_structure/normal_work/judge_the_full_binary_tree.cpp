// 判断某个树是不是完全二叉树
#include "node.h"
#include <iostream>
#include <queue>
int is_full_binary_tree(Node *root) {
  // 返回0表示不是完全二叉树
  std::queue<Node *> que;
  que.push(root);
  int flag = 0;
  while (!que.empty()) {
    auto tmp = que.front();
    que.pop();
    if (tmp == nullptr) {
      flag = 1;
      continue; // 空指针没有子节点需要插入
    }

    if (flag == 1)
      return 0;
    que.push(tmp->left);
    que.push(tmp->right);
  }
  return 1;
}

int main(void) {
  auto A = new Node(1);
  auto B = new Node(2);
  auto C = new Node(3);
  auto D = new Node(4);
  auto E = new Node(5);
  auto F = new Node(6);
  auto G = new Node(7);
  auto H = new Node(8);
  auto I = new Node(9);
  auto J = new Node(10);
  auto K = new Node(11);
  auto L = new Node(12);

  A->left = B;
  A->right = C;
  B->right = D;
  C->left = E;
  C->right = F;
  printf("%d\n", is_full_binary_tree(A));

  return 0;
}