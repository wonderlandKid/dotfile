// 编写算法求给定二叉树中一条最长的路径，并输出此路径上各结点的值。
class Node {
public:
  Node() {
    left = nullptr;
    right = nullptr;
    val = 0;
  }
  Node(int _val) {
    left = nullptr;
    right = nullptr;
    val = _val;
  }

  Node *left;
  Node *right;
  int val;
};

#include <iostream>
#include <vector>

int depth(Node *root) {
  // 返回这个二叉树的深度
  if (root == nullptr)
    return -1;

  int tmp1 = depth(root->left);
  int tmp2 = depth(root->right);

  if (tmp1 >= tmp2)
    return tmp1 + 1;
  else
    return tmp2 + 1;
}

void print_longest_way(Node *root) {
  // 假如两条路径相等则打印靠左路径
  if (root == nullptr)
    return;

  printf("%d ", root->val);

  if (depth(root->left) >= depth(root->right))
    print_longest_way(root->left);
  else
    print_longest_way(root->right);
}

Node *buildtree() {
  int tmp = 0;
  // 输入-1表示空指针
  scanf("%d", &tmp);
  if (tmp != -1) {
    auto root = new Node(tmp);
    root->left = buildtree();
    root->right = buildtree();
    return root;
  } else
    return nullptr;
}

int main(void) {
  auto root=buildtree();
  print_longest_way(root);
  return 0;
}