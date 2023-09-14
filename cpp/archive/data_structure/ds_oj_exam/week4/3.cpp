#include <climits>
#include <iostream>
using namespace std;

class TreeNode {
public:
  TreeNode() {
    myfather = left = right = nullptr;
    val = 0;
    sum = 0;
  }
  TreeNode(int _val) {
    myfather = left = right = nullptr;
    val = _val;
    sum = 0;
  }

  TreeNode *left;
  TreeNode *right;
  TreeNode *myfather;
  int val;
  int sum;
};

class ReSult {
public:
  ReSult() { smaller = bigger = absgap = 0; }
  int smaller;
  int bigger;
  int absgap;
};

TreeNode *Build_tree() {
  // 先根确定二叉树
  int val;
  scanf("%d", &val);
  if (val == 0)
    return nullptr;

  auto root = new TreeNode(val);

  root->left = Build_tree();
  if (root->left != nullptr)
    root->left->myfather = root;
  root->right = Build_tree();
  if (root->right != nullptr)
    root->right->myfather = root;

  return root;
}

void Build_sum(TreeNode *root) {
  if (root->left != nullptr)
    Build_sum(root->left);
  if (root->right != nullptr)
    Build_sum(root->right);

  if (root->left != nullptr)
    root->sum += root->left->sum + root->left->val;
  if (root->right != nullptr)
    root->sum += root->right->sum + root->right->val;
  // if (root->left != nullptr)
  //   Build_sum(root->left);
  // if (root->left != nullptr)
  //   Build_sum(root->right);
  // if (root->left == nullptr && root->right == nullptr) {
  //   root->leftsum = 0;
  //   root->rightsum = 0;
  // } else if (root->left == nullptr && root->right != nullptr) {
  //   root->leftsum = 0;
  //   root->rightsum = root->right->val + root->right->leftsum + root->leftsum;
  // } else if (root->left != nullptr && root->right == nullptr) {
  //   root->leftsum =
  //       root->left->val + root->left->leftsum + root->left->rightsum;
  //   root->rightsum = 0;
  // } else {
  //   root->leftsum =
  //       root->left->val + root->left->leftsum + root->left->rightsum;
  //   root->rightsum = root->right->val + root->right->leftsum + root->leftsum;
  // }
  // root->sum = root->leftsum + root->rightsum;
}

void Solve_problem(TreeNode *root, ReSult &a, int all_sum) {
  // root是当前处理的结点
  if (root->left != nullptr) {
    Solve_problem(root->left, a, all_sum);
  }

  auto tmp = root->myfather;
  if (tmp == nullptr)
    ;
  else {
    auto x1 = root->val + root->sum;
    auto x2 = all_sum - x1;
    auto absx1 = abs(x1);
    auto absx2 = abs(x2);
    auto gap = abs(absx1 - absx2);
    if (gap <= a.absgap) {
      a.absgap = gap;
      if (x1 <= x2) {
        a.smaller = x1;
        a.bigger = x2;
      } else {
        a.smaller = x2;
        a.bigger = x1;
      }
    }
  }

  if (root->right != nullptr) {
    Solve_problem(root->right, a, all_sum);
  }

  return;
}

void Printtree(TreeNode *root) {
  if (root == nullptr)
    return;

  printf("%d ", root->val);
  Printtree(root->left);
  Printtree(root->right);
}

int main(void) {
  auto root = Build_tree();
  // Printtree(root);
  // printf("\n");
  Build_sum(root);

  // 先根遍历找合适的边

  ReSult a;
  a.absgap = INT_MAX;
  int all_sum = root->val + root->sum;
  Solve_problem(root, a, all_sum);
  printf("%d %d %d\n", a.absgap, a.smaller, a.bigger);
  return 0;
}
