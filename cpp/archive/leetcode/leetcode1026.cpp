#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

class Solution {
 public:
  int dfs(TreeNode* root, int mi, int ma) {
    if (root == nullptr) {
      return 0;
    }
    int diff = max(abs(root->val - mi), abs(root->val - ma));
    mi = min(mi, root->val);
    ma = max(ma, root->val);
    diff = max(diff, dfs(root->left, mi, ma));
    diff = max(diff, dfs(root->right, mi, ma));
    return diff;
  }

  int maxAncestorDiff(TreeNode* root) {
    return dfs(root, root->val, root->val);
  }
};

int main() {
  auto root = new TreeNode(8);
  auto a = new TreeNode(3);
  auto b = new TreeNode(10);
  auto c = new TreeNode(1);
  auto d = new TreeNode(6);
  auto e = new TreeNode(14);
  auto f = new TreeNode(4);
  auto g = new TreeNode(7);
  auto h = new TreeNode(13);
  root->left = a;
  root->right = b;
  a->left = c;
  a->right = d;
  d->left = f;
  d->right = g;
  b->right = e;
  e->left = h;
  Solution test;
  cout << test.maxAncestorDiff(root);
  return 0;
}
