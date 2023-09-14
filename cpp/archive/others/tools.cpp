#include <string>
#include "node.h"
using namespace std;

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

