// 衣服挂游戏
#include <iostream>
#include <vector>
using namespace std;

class TreeNode {
public:
  TreeNode(int _val) {
    left = right = myfather = nullptr;
    val = _val;
  }
  TreeNode *left;
  TreeNode *right;
  TreeNode *myfather;
  int val; // 存数字个数
};

TreeNode *whatfather(TreeNode *root) {
  if (root->myfather == nullptr)
    return root;

  root->myfather = whatfather(root->myfather);

  return root->myfather;
}

int main(void) {
  int opgroups = 0;
  scanf("%d", &opgroups);
  for (int p1 = 1; p1 <= opgroups; p1++) {
    int n = 0; // 多少列
    int m = 0; // 多少个挂的操作
    scanf("%d%d", &n, &m);
    vector<TreeNode *> vec(n + 1, nullptr); // 下标从1开始

    // 初始化
    for (int i = 1; i <= n; i++) {
      vec[i] = new TreeNode(i);
    }

    // 下面处理m个挂的操作
    for (int p2 = 1; p2 <= m; p2++) {
      int x = 0, y = 0;
      scanf("%d%d", &x, &y);

      // 把x列挂到y后面
      if (whatfather(vec[x]) == whatfather(vec[y])) {
      } else {
        auto xfather=whatfather(vec[x]);
        xfather->myfather=vec[y];
      }
    }

    for (int i = 1; i <= n; i++) {
      auto ifather=whatfather(vec[i]);
      printf("%d ", ifather->val);
    }
    printf("\n");
  }
  return 0;
}
