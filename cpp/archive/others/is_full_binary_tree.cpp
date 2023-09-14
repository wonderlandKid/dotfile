#include <cstdio>
#include <queue>
using namespace std;

class Node {
 public:
  Node(int _val) : val(_val) {}
  Node* left{nullptr};
  Node* right{nullptr};
  int val{0};
};

bool is_full_binary_tree(Node* root) {
  // 如果是false表示不是完全二叉树
  // 一种层次遍历思想的体现
  queue<Node*> que;
  que.push(root);
  int flag = 1;
  while (!que.empty()) {
    auto tmp = que.front();
    que.pop();
    if (tmp == nullptr) {
      flag = 1;
      continue;
    }

    if (flag == 1) return false;

    que.push(tmp->left);
    que.push(tmp->right);
  }
  return true;
}
