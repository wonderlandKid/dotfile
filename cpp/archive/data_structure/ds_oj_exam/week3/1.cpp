#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
  Node(int _val) {
    val = _val;
    left = nullptr;
    right = nullptr;
  }
  int val;
  Node *left;
  Node *right;
};

Node *buildtree(int leftmark, int rightmark, string &afterroot, string &midroot,
                string &afterrootmark, string &midrootmark) {
  // 给定中根序列的两个下标 返回一个树的root
  const int afterroot_len = afterroot.size();
  const int midroot_len = midroot.size();
  int tmp = -1;

  // 找给定区间的根节点
  for (int p1 = afterroot_len - 1; p1 >= 0; p1--) {
    if (afterrootmark[p1] == 1)
      continue;
    else {
      for (int p2 = leftmark; p2 <= rightmark; p2++) {
        if (afterroot[p1] == midroot[p2]) {
          afterrootmark[p1] = 1;
          midrootmark[p2] = 1;
          tmp = p2;
          break;
        }
      }
      if (tmp != -1)
        break;
    }
  }

  auto root = new Node(midroot[tmp]);

  // 建立左子树
  if (tmp == 0)
    root->left = nullptr;
  else if (midrootmark[tmp - 1] == 1)
    root->left = nullptr;
  else {
    int leftlimit = tmp - 1;
    while (1) {
      if (leftlimit == -1)
        break;
      if (midrootmark[leftlimit] == 1)
        break;
      leftlimit--;
    }
    root->left = buildtree(leftlimit + 1, tmp - 1, afterroot, midroot,
                           afterrootmark, midrootmark);
  }

  if (tmp == midroot_len - 1)
    root->right = nullptr;
  else if (midrootmark[tmp + 1] == 1)
    root->right = nullptr;
  else {
    int rightlimit = tmp + 1;
    while (1) {
      if (rightlimit == midroot_len)
        break;
      if (midrootmark[rightlimit] == 1)
        break;
      rightlimit++;
    }
    root->right = buildtree(tmp + 1, rightlimit - 1, afterroot, midroot,
                            afterrootmark, midrootmark);
  }
  // root->left = buildtree(tmp + 1, midroot_len - 1, afterroot, midroot,
  // afterrootmark, midrootmark);
  return root;
}

int tree_height(Node *root) {
  if (root == nullptr)
    return 0;

  int left_height = tree_height(root->left) + 1;
  int right_height = tree_height(root->right) + 1;

  if (left_height >= right_height)
    return left_height;
  else
    return right_height;
}

void is_legal(string &Myafterroot, Node *root) {
  // 左右根
  if (root != nullptr)
    is_legal(Myafterroot, root->left);

  if (root != nullptr)
    is_legal(Myafterroot, root->right);

  if (root == nullptr)
    return;

  else
    Myafterroot += root->val;

  return;
}

void print_preroot(Node *root) {
  printf("%c", root->val);

  if (root->left == nullptr)
    ;
  else
    print_preroot(root->left);

  if (root->right == nullptr)
    ;
  else
    print_preroot(root->right);

  return;
}

int main(void) {
  string tmp1;
  string tmp2;

  // 第一行后根 第二行中根
  while (cin >> tmp1 >> tmp2) {
    string afterroot = tmp1;
    string midroot = tmp2;
    string afterrootmark = string(30, 0);
    string midrootmark = string(30, 0);
    auto root = buildtree(0, tmp2.size() - 1, afterroot, midroot, afterrootmark,
                          midrootmark);

    // 判断合法环节 直接对比两个后根序列

    string Myafterroot;
    is_legal(Myafterroot, root);

    if (Myafterroot == afterroot) {
      // 合法
      printf("%d\n", tree_height(root) - 1);
      print_preroot(root);
      printf("\n");
    } else
      printf("INVALID\n");
  }
  return 0;
}
