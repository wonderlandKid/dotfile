// 已知一棵树的层次遍历序列及相应的每个结点的次数序列，请写出构造此树的左儿子—右兄弟链接表示的算法。

#include "node.h"
#include <iostream>

// 这个类把每个结点的指针都存下来

class index {
public:
  index(int _down, Node *_root) {
    root = _root;
    downmark = _down;
  }

  index() {
    root = nullptr;
    downmark = 0;
  }
  Node *root;
  int downmark;
};

#include <vector>
Node *build_sonandbroTree(int data[], int nodedegree[], int nodenumber) {
  // 数据存到data里面 nodedegree是存度的数组 nodenumber是结点个数

  int marknode[10000]; // 假设结点个数小于10000 视nodenumber大小调
  std::vector<index> array;
  for (int i = 0; i <= nodenumber - 1; i++) {
    array.push_back(index(i, new Node(data[i])));
    // 把所有数值全都放入结点 然后把结点和下标一起放入array
  }
  for (int i = 0; i <= nodenumber - 1; i++) {
    marknode[i] = 1;

    const int i_degree = nodedegree[i]; // 第i个结点的度
    int count = 0;                      // 找到 度 个未进树的结点
    int p1 = i + 1;                     // 下标
    Node *tmp = nullptr;                // 当前操作的结点
    while (1) {
      if (marknode[p1] == 1)
        continue;
      if (count == i_degree)
        break;
      if (marknode[p1] == 0) {
        count++;
        marknode[p1] = 1;
        if (count == 1) {
          tmp = array[i].root;
          tmp->left = array[p1].root;
          tmp = tmp->left;
        } else {
          tmp->right = array[p1].root;
          tmp = tmp->right;
        }
      }
    }
  }

  return array[0].root;
}
