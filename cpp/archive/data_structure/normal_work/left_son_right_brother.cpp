// 对以左儿子—右兄弟链接表示的树，编写算法计算树的深度。
#include "node.h"
#include <iostream>
using namespace std;
int depth2(Node *root) {
  if (root == nullptr)
    return -1;

  int tmp1 = depth2(root->left) + 1;
  int tmp2 = depth2(root->right);

  if (tmp1 >= tmp2)
    return tmp1;
  else
    return tmp2;
}

int main(void) {
  auto p1 = new Node(1);
  auto p2 = new Node(2);
  auto p3 = new Node(3);
  auto p4 = new Node(4);
  auto p5 = new Node(5);
  auto p6 = new Node(6);
  auto p7 = new Node(7);
  auto p8 = new Node(8);
  auto p9 = new Node(9);

  p1->left = p2;
  p2->left = p5;
  p2->right = p3;
  p3->right = p4;
  p4->left = p7;
  p5->right = p6;
  p7->left = p8;
  p8->right = p9;
  printf("%d\n", depth2(p1));
  return 0;
}