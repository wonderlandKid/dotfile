#include <cstdio>
#include <queue>
#include <cstdlib>
using namespace std;

class Node {
public:
  Node() {
    val = 0;
    left = nullptr;
    right = nullptr;
  }
  Node(int _val) {
    val = _val;
    left = nullptr;
    right = nullptr;
  }
  int val;
  Node *left;
  Node *right;
};

Node *BuildTree(void) {
  int x = 0;
  scanf("%d", &x);
  if (x == 0)
    return nullptr;

  auto root = new Node(x);

  root->left = BuildTree();
  root->right = BuildTree();

  return root;
}

int main(void) {
  //freopen("in.txt", "r", stdin);

  // 建树
  auto root = BuildTree();

  int whatline = 1; // 1反遍历 0正遍历
  int m, n;
  int flag = 0; // 为1时可以打印
  scanf("%d%d", &m, &n);

  int resultsize = 0; // result数组里面有多少个
  Node *result[10011] = {0};
  queue<Node *> que;
  queue<Node *> buffer;
  que.push(root);

  while (!(que.empty() && buffer.empty())) {
    while (!que.empty()) {
      auto tmp = que.front();
      que.pop();
      result[resultsize] = tmp;
      resultsize++;
      if (tmp->left != nullptr)
        buffer.push(tmp->left);
      if (tmp->right != nullptr)
        buffer.push(tmp->right);
    }

    if (whatline == 1) {
      // 反遍历
      for (int i = resultsize - 1; i >= 0; i--) {
        if (result[i]->val == m)
          flag = 1;
        if (flag)
          printf("%d ", result[i]->val);
        if (result[i]->val == n)
          exit(0);
      }
    } else {
      // 正遍历
      for (int i = 0; i <= resultsize - 1; i++) {
        if (result[i]->val == m)
          flag = 1;
        if (flag)
          printf("%d ", result[i]->val);
        if (result[i]->val == n)
          exit(0);
      }
    }
    resultsize = 0;
    que = buffer;
    while (!buffer.empty())
      buffer.pop();
    if(whatline==1)
      whatline=0;
    else whatline=1;
  }
  return 0;
}