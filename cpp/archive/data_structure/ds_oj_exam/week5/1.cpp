#include <cstdlib>
#include <iostream>
using namespace std;

class List {
public:
  List(void) {
    val = weight = 0;
    before = after = nullptr;
  }
  List(int _val, int _weight) {
    val = _val;
    weight = _weight;
    before = after = nullptr;
  }
  int val;    // 存的终点边
  int weight; // 权值
  List *before;
  List *after;
};

int main(void) {
  // freopen("in.txt", "r", stdin);
  int n, e;
  scanf("%d%d", &n, &e); // 顶点数和边数
  List *index[20010]{};    // 默认指向空指针

  // 下面e次迭代输入边数
  for (int i = 1; i <= e; i++) {
    int start, end, weight;
    scanf("%d%d%d", &start, &end, &weight);
    if (index[start] == nullptr) {
      // 第一个元素
      index[start] = new List(end, weight);
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
            auto tmp = new List(end, weight);
            tmp->after = p1;
            p1->before = tmp;
            index[start] = tmp;
            break;
          } else {
            auto p1before = p1->before;
            auto tmp = new List(end, weight);
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
        List *tmp = new List(end, weight);
        p1end->after = tmp;
        tmp->before = p1end;
      }
    }
  }

  // 打印环节
  for (int i = 0; i <= n - 1; i++) {
    if (index[i] == nullptr)
      ;
    else {
      printf("%d:", i);
      for (auto begin = index[i]; begin != nullptr; begin = begin->after) {
        printf("(%d,%d,%d)", i, begin->val, begin->weight);
      }
      printf("\n");
    }
  }
  return 0;
}

/*
0:(0,1,5)(0,3,7)(0,6,6)
1:(1,2,4)
2:(2,5,1)
3:(3,5,3)
6:(6,5,4)
*/
