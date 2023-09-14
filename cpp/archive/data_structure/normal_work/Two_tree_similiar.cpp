// 判断两棵二叉树是否相似
class Node {
public:
  Node() {
    left = nullptr;
    right = nullptr;
    val = 0;
  }
  Node *left;
  Node *right;
  int val;
};
#include <queue>
int Binary_tree_like(Node *root1, Node *root2) {
  std::queue<Node> que1, que2;
  que1.push(*root1);
  que2.push(*root2);
  while (que1.empty() != 1 && que2.empty() != 1) {
    auto tmp1 = que1.front();
    auto tmp2 = que2.front();
    que1.pop();
    que2.pop();
    int flag1 = 0;
    int flag2 = 0;
    if (tmp1.left != nullptr)
      flag1 = flag1 + 10;
    if (tmp1.right != nullptr)
      flag1 = flag1 + 1;

    if (tmp2.left != nullptr)
      flag2 = flag2 + 10;
    if (tmp2.right != nullptr)
      flag2 = flag2 + 1;

    // 如果这里的结构不一样 那么就返回0 表示不匹配
    if (flag1 != flag2)
      return 0;

    if (tmp1.left != nullptr)
      que1.push(*(tmp1.left));
    if (tmp1.right != nullptr)
      que1.push(*(tmp1.right));

    if (tmp2.left != nullptr)
      que2.push(*(tmp2.left));
    if (tmp2.right != nullptr)
      que2.push(*(tmp2.right));
  }
  return 1; // 此时两个树结构一样
}