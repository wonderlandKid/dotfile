// 图深度优先遍历
#include <iostream>

using namespace std;
class List {
public:
  List(void) {
    val = 0;
    before = after = nullptr;
  }
  List(int _val) {
    val = _val;
    before = after = nullptr;
  }
  int val; // 存的终点边
  List *before;
  List *after;
};

// 从数组第start开始 打印之后的DFS序列
void DFS(int start, List *index[], int readed[], int e) {
  if (readed[start] == 1)
    ;
  else {
    readed[start] = 1;
    printf("%d ", start);
    for (auto tmp = index[start]; tmp != nullptr; tmp = tmp->after) {
      DFS(tmp->val, index, readed, e);
    }
  }
  return;
}

int main(void) {
  int n, e;
  scanf("%d%d", &n, &e); // 顶点数和边数
  List *index[20010]{};  // 默认指向空指针
  int readed[20010] = {0};
  // 下面e次迭代输入边数
  for (int i = 1; i <= e; i++) {
    int start, end;
    scanf("%d%d", &start, &end);
    if (index[start] == nullptr) {
      // 第一个元素
      index[start] = new List(end);
    } else {
      // 有元素 找到位置插入
      int flag = 0; // 为1表示已经进行过操作
      auto p1 = index[start];
      auto p1end = p1; // 为了循环外面尾端插入留一个尾部指针
      for (; p1 != nullptr; p1 = p1->after) {
        if (p1->after == nullptr)
          p1end = p1;
        if (p1->val > end) {
          // 插入到p1的前面
          flag = 1;
          if (p1->before == nullptr) {
            // p1是首节点
            auto tmp = new List(end);
            tmp->after = p1;
            p1->before = tmp;
            index[start] = tmp;
            break;
          } else {
            auto p1before = p1->before;
            auto tmp = new List(end);
            p1before->after = tmp;
            tmp->before = p1before;
            tmp->after = p1;
            p1->before = tmp;
          }
          break;
        }
      }
      // 此处退出for循环
      if (flag == 0) {
        List *tmp = new List(end);
        p1end->after = tmp;
        tmp->before = p1end;
      }
    }
  }

  for(int i=0; i<=n-1; i++){
    DFS(i, index, readed, e);
  }
  return 0;
}