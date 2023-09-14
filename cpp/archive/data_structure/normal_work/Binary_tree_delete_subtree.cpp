// 二叉树删除子树
#include <iostream>
using namespace std;

class TreeNode {
public:
  TreeNode(int _val) {
    myfather = left = right = nullptr;
    val = _val;
  }
  TreeNode *left;
  TreeNode *right;
  int val;
  TreeNode *myfather;
};

TreeNode *Prebuildtree() {
  int d;
  scanf("%d", &d);

  if (d == 0)
    return nullptr;

  auto root = new TreeNode(d);

  root->left = Prebuildtree();
  root->right = Prebuildtree();

  if (root->left != nullptr)
    root->left->myfather = root;
  if (root->right != nullptr)
    root->right->myfather = root;

  return root;
}

TreeNode *Findfather(TreeNode *root, int val) {
  if (root == nullptr)
    return nullptr;

  if (root->val == val)
    return root;

  auto leftresult = Findfather(root->left, val);

  if (leftresult != nullptr)
    return leftresult;

  auto rightresult = Findfather(root->right, val);

  if (rightresult != nullptr)
    return rightresult;

  return nullptr;
}

void Printpreroot(TreeNode *root) {
  // 中根打印序列
  if (root == nullptr)
    return;
  Printpreroot(root->left);
  printf("%d ", root->val);
  Printpreroot(root->right);
}

int main(void) {
  // 带父节点二叉树
  auto root = Prebuildtree();

  int times;
  scanf("%d", &times);

  for (int i = 1; i <= times; i++) {
    int key;
    scanf("%d", &key);
    auto tmp = Findfather(root, key);
    if (tmp == nullptr)
      printf("0\n");
    else {
      auto tmpfather = tmp->myfather;
      if (tmp == tmpfather->left)
        tmpfather->left = nullptr;
      if (tmp == tmpfather->right)
        tmpfather->right = nullptr;
      tmp->myfather = nullptr;
      Printpreroot(root);
      printf("\n");
    }
  }
  return 0;
}
