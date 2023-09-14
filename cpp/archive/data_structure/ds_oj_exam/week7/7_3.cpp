// 最大边
// 给定一个包含n个顶点的无向正权连通图，顶点编号为1到n。请编写程序计算其最小支撑树中任意两个顶点间路径中，权值最大的边的权值。
#define INT_MAX 0x3f3f3f3f
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

class Treenode {
 public:
  Treenode(int _val) : val(_val), myfather(nullptr) {}
  int val;  // point name
  Treenode* myfather;
};

class Edge {
 public:
  Edge(int _waybegin, int _wayend, int _weight) {
    waybegin = _waybegin;
    wayend = _wayend;
    weight = _weight;
    next = nullptr;
  }
  int waybegin;
  int wayend;
  int weight;
  Edge* next;
};

Treenode* whosmyfather(Treenode* root) {
  if (root->myfather == nullptr) return root;
  root->myfather = whosmyfather(root->myfather);
  return root->myfather;
}

int DFS(vector<Edge*>& newindex, int n, int begin, int target,
        vector<int>& visited, vector<Edge>& result);

int main() {
  freopen("in.txt", "r", stdin);
  int n, m;  // n point m edges
  scanf("%d%d", &n, &m);
  vector<Treenode*> index(n + 10, nullptr);
  for (int i = 1; i <= n; i++) index[i] = new Treenode(i);

  vector<Edge> edge;
  edge.reserve(m + 10);
  for (int i = 1; i <= m; i++) {
    int begin, end, weight;
    scanf("%d%d%d", &begin, &end, &weight);
    edge.push_back(Edge(begin, end, weight));
  }

  auto compar = [](const Edge& a, const Edge& b) -> bool {
    if (a.weight <= b.weight) return true;
    return false;
  };

  sort(edge.begin(), edge.end(), compar);

  // printf("排序之后\n\n");
  // for (auto i : edge) {
  //   printf("%d->%d:%d\n", i.waybegin, i.wayend, i.weight);
  // }

  // printf("\n\n");
  vector<Edge> MST;
  MST.reserve(n + 10);

  auto solveMST = [&]() {
    int p1 = 0;  // edge从0开始
    for (int i = 1; i <= n - 1; i++) {
      while (1) {
        auto tmp = edge[p1];
        auto father1 = whosmyfather(index[tmp.waybegin]);
        auto father2 = whosmyfather(index[tmp.wayend]);
        if (father1 != father2) {
          // 此时两者不在同一个连通分量里面
          father2->myfather = father1;
          MST.push_back(tmp);
          p1++;
          break;
        }
        p1++;
      }
    }
  };

  solveMST();
  // 验证最小生成树
  // printf("验证最小生成树\n\n");
  // for (auto i : MST) {
  //   printf("%d->%d:%d \n", i.waybegin, i.wayend, i.weight);
  // }

  index.clear();
  index.shrink_to_fit();
  edge.clear();
  edge.shrink_to_fit();

  // vector<vector<int>> distarray(n + 10, vector<int>(n + 10, INT_MAX));
  vector<Edge*> newindex(n + 10, nullptr);
  // 超内存邻接表呢
  for (auto i : MST) {
    if (newindex[i.waybegin] == nullptr) {
      newindex[i.waybegin] = new Edge(i.waybegin, i.wayend, i.weight);
    } else {
      auto tmp = newindex[i.waybegin];
      newindex[i.waybegin] = new Edge(i.waybegin, i.wayend, i.weight);
      newindex[i.waybegin]->next = tmp;
    }
    if (newindex[i.wayend] == nullptr) {
      newindex[i.wayend] = new Edge(i.wayend, i.waybegin, i.weight);
    } else {
      auto tmp = newindex[i.wayend];
      newindex[i.wayend] = new Edge(i.wayend, i.waybegin, i.weight);
      newindex[i.wayend]->next = tmp;
    }
  }
  // 邻接表建立完毕

  MST.clear();
  MST.shrink_to_fit();

  int T;
  scanf("%d", &T);
  for (int i = 1; i <= T; i++) {
    int waybegin, wayend;
    scanf("%d%d", &waybegin, &wayend);
    // DFS硬过算了
    vector<Edge> result;
    result.reserve(n);
    vector<int> visited(n + 10, 0);
    DFS(newindex, n, waybegin, wayend, visited, result);

    int finalresult = 0;
    for (auto i : result) {
      if (i.weight > finalresult) finalresult = i.weight;
    }

    printf("%d\n", finalresult);
  }
  return 0;
}

int DFS(vector<Edge*>& newindex, int n, int begin, int target,
        vector<int>& visited, vector<Edge>& result) {
  // 从begin开始找target 成功返回1 结果存在result里面
  if (begin == target) return 1;
  visited[begin] = 1;
  int flag = 0;
  for (auto i = newindex[begin]; i != nullptr; i = i->next) {
    if (visited[i->wayend] == 0) {
      result.push_back(*i);
      flag = DFS(newindex, n, i->wayend, target, visited, result);
      if (flag == 0) {
        // 经过i边之后还是没有找到
        result.pop_back();
      } else {
        break;
      }
    }
  }
  if (flag == 0) return 0;
  return 1;
}

// int DFS(vector<vector<int>> distarray, int n, int begin, int target,
//         vector<int>& visited, vector<int>& result) {
//   // 从begin开始找target 如果成功找到了就返回1 结果存在result里面
//   visited[begin] = 1;
//   if (distarray[begin][target] < INT_MAX) {
//     result.push_back(target);
//     return 1;
//   }
//   int flag = 0;
//   for (int i = 1; i <= n; i++) {
//     if (visited[i] == 0 && distarray[begin][i] < INT_MAX) {
//       result.push_back(i);
//       flag = DFS(distarray, n, i, target, visited, result);
//       if (flag == 0) {
//         // i没有通向target
//         result.pop_back();
//       } else
//         break;
//     }
//   }
//   if (flag == 0)
//     return 0;
//   else
//     return 1;
// }

/*  vector<vector<int>> distarray(n + 10, vector<int>(n + 10, INT_MAX));
  for (int i = 1; i <= n; i++) distarray[i][i] = INT_MAX;
  for (auto i : MST) {
    distarray[i.waybegin][i.wayend] = i.weight;
    distarray[i.wayend][i.waybegin] = i.weight;
  }
int DFS(vector<vector<int>> distarray, int a, int b, vector<int> visited,
        vector<Edge>& result, int n);
int DFS(vector<vector<int>> distarray, int a, int b, vector<int> visited,
        vector<Edge>& result, int n) {
  // 起点a深度优先搜索 考察是否到达终点b 一旦到达终点b 就退出
  for (int i = 1; i <= n; i++) {
    if (distarray[a][i] < INT_MAX && visited[i] == 0) {

    }
  }
}


*/
