//二叉树查找结点及父结点
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

// 在root二叉树里面找到一个值为val的结点并返回其父亲结点的值 找不到返回0
int Findfather(TreeNode *root, int val) {
  if (root == nullptr)
    return 0;

  if (root->val == val && root->myfather != nullptr)
    return root->myfather->val;

  if (root->val == val && root->myfather == nullptr)
    return 0;

  int leftresult = Findfather(root->left, val);

  if(leftresult!=0) return leftresult;

  int rightresult = Findfather(root->right, val);

  if(rightresult!=0) return rightresult;

  return 0;

}

int main(void) {
  auto root = Prebuildtree();
  int times;
  scanf("%d", &times);

  for (int i = 1; i <= times; i++) {
    int key;
    scanf("%d", &key);
    printf("%d\n", Findfather(root, key));
  }
  return 0;
}