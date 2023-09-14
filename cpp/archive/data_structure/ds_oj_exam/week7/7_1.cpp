#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Edge {
 public:
  Edge(int _end, int _weight) : end(_end), weight(_weight), next(nullptr){};
  int end;
  int weight;
  Edge* next;
};

int main(void) {
  int n, e;
  while (scanf("%d%d", &n, &e) != EOF) {
    // 定点编号1~n
    vector<Edge*> index(210, nullptr);
    vector<int> count(210, 0);
    vector<int> stk;  // 每有一个入度为0的点就压栈
    stk.reserve(210);
    vector<int> toporesult;  // 拓扑排序的结果 注意这个是从下标0开始的
    toporesult.reserve(210);

    // ve[i]的意义是i号点的对应值 不是topo序列里面的第i个 就是原来的
    vector<int> ve(210, 0), vl(210, 0);

    // 开始输入邻接表形式的图
    for (int i = 1; i <= e; i++) {
      int waybegin, wayend, wayweight;
      scanf("%d%d%d", &waybegin, &wayend, &wayweight);
      count[wayend]++;  // 入度+1
      auto newnode = new Edge(wayend, wayweight);
      if (index[waybegin] == nullptr)
        index[waybegin] = newnode;
      else {
        // 还是稍微排个序 终点小的排在前面 便于最后处理
        auto tmp = index[waybegin];
        if (index[waybegin]->end > newnode->end) {
          index[waybegin] = newnode;
          newnode->next = tmp;
          continue;
        }
        auto tmp2 = tmp->next;
        while (tmp2 != nullptr) {
          if (tmp2->end > newnode->end) break;

          tmp = tmp2;
          tmp2 = tmp2->next;
        }
        tmp->next = newnode;
        newnode->next = tmp2;
      }
    }

    for (int i = 1; i <= n; i++) {
      if (count[i] == 0) stk.push_back(i);
    }

    auto printtoporesult = [&]() -> void {
      printf("\n下面是打印toporesult:\n");
      for (int i : toporesult) printf("%d ", i);
      printf("\n");
    };

    auto Topoorder = [&]() -> bool {
      for (int i = 1; i <= n; i++) {
        if (stk.empty()) return false;
        auto target = stk.back();
        stk.pop_back();  // stk是暂存
        toporesult.push_back(target);
        // printtoporesult();
        for (auto p1 = index[target]; p1 != nullptr; p1 = p1->next) {
          count[p1->end]--;
          if (count[p1->end] == 0) stk.push_back(p1->end);
        }
      }
      return true;
    };

    if (Topoorder() == false) {
      printf("unworkable project\n");
      continue;
    }

    // 现在计算每个顶点的最早发生时间
    for (int i : toporesult) {
      for (auto p1 = index[i]; p1 != nullptr; p1 = p1->next) {
        int k = p1->end;
        if (ve[i] + p1->weight > ve[k]) ve[k] = ve[i] + p1->weight;
      }
    }

    // 现在计算顶点的最迟发生时间
    vl.assign(210, ve[toporesult.back()]);

    // for (int i = n; i != 0; i--) {
    //   for (auto p1 = index[toporesult[i - 1]]; p1 != nullptr; p1 = p1->next)
    //   {
    //     int k = p1->end;
    //     if (vl[k] - p1->weight < vl[toporesult[i - 1]])
    //       vl[toporesult[i - 1]] = vl[k] - p1->weight;
    //   }
    // }
    //  计算定点的最迟发生时间(way2)
    for (auto p1 = toporesult.rbegin(); p1 != toporesult.rend(); p1++) {
      for (auto p2 = index[*p1]; p2 != nullptr; p2 = p2->next) {
        int k = p2->end;
        if (vl[k] - p2->weight < vl[*p1]) vl[*p1] = vl[k] - p2->weight;
      }
    }

    // printf("\n打印数组ve的值\n");
    // for (int i = 1; i <= n; i++) printf("%d ", ve[i]);
    // printf("\n");
    // printf("\n打印数组vl的值:\n");
    // for (int i = 1; i <= n; i++) printf("%d ", vl[i]);
    // printf("\n");

    // 打印最短时间

    vector<int> cucialpoint;
    cucialpoint.reserve(210);
    for (int i = 1; i <= n; i++) {
      if (ve[i] == vl[i]) cucialpoint.push_back(i);
    }

    printf("%d\n", ve[toporesult.back()]);

    // 打印关键路径
    // priority_queue<int, vector<int>, greater_equal<int>> que;
    // for (int i : cucialpoint) {
    //  for (auto p1 = index[i]; p1 != nullptr; p1 = p1->next) {
    //    // 找在不在topo序列里面
    //    if (find(cucialpoint.begin(), cucialpoint.end(), p1->end) ==
    //        cucialpoint.end())
    //      ;
    //    else {
    //      que.push(p1->end);
    //    }
    //  }
    //  while (!que.empty()) {
    //    auto tmp = que.top();
    //    que.pop();
    //    printf("%d->%d\n", i, tmp);
    //  }
    //}

    // 打印关键路径(way2)
    for (auto i : cucialpoint) {
      for (auto p1 = index[i]; p1 != nullptr; p1 = p1->next) {
        int k = p1->end;
        if (ve[i] == vl[k] - p1->weight) printf("%d->%d\n", i, k);
      }
    }
  }

  return 0;
}
