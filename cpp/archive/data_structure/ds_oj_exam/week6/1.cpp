#include <climits>
#include <iostream>
#include <queue>
#include <set>
using namespace std;

class Edge {
 public:
  Edge(int _begin, int _end, int _weight) {
    begin = _begin;
    end = _end;
    weight = _weight;
  }
  int end;
  int begin;
  int weight;
  Edge* next;
};

class Vertex {
 public:
  Vertex() : vername(-1), adjacent(nullptr) {}
  Vertex(int _vername) {
    adjacent = nullptr;
    vername = _vername;
  }
  int vername;
  Edge* adjacent;
};
void Printanswer(Vertex index[15010], int x, vector<int> path) {
  if (x == 0) return;
  Printanswer(index, path[x], path);
  printf("->%d", x);
}

int main(void) {
  int n, e;
  scanf("%d%d", &n, &e);
  Vertex index[15010];
  vector<int> dist(15010, INT_MAX);
  vector<int> path(15010, -1);
  vector<int> steps(15010, INT_MAX);

  steps[0] = 0;
  dist[0] = 0;
  for (int i = 1; i <= 15010; i++) index[i - 1] = Vertex(i - 1);
  for (int i = 1; i <= e; i++) {
    int waybegin, wayend, wayweight;
    scanf("%d%d%d", &waybegin, &wayend, &wayweight);
    auto tmp = new Edge(waybegin, wayend, wayweight);
    if (index[waybegin].adjacent == nullptr)
      index[waybegin].adjacent = tmp;
    else {
      tmp->next = index[waybegin].adjacent;
      index[waybegin].adjacent = tmp;
    }
  }

  auto printindex = [index, n]() -> void {
    for (int i = 0; i <= n - 1; i++) {
      for (auto p1 = index[i].adjacent; p1 != nullptr; p1 = p1->next) {
        printf("终点%d权值%d ", p1->end, p1->weight);
      }
      printf("\n");
    }
  };

  // printindex();

  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      que;

  que.push({0, 0});  //{dist, varname}
  // Dijkstra 堆优化
  for (int i = 1; i <= n; i++) {
    if (que.empty() == 1) break;  // 如果单调队列里面没有了 直接退出

    // 这里的单调队列只是为了根据距离的大小排vername, 所以重点是vername.
    auto tmp = que.top();
    que.pop();
    auto point = tmp.second;

    // point_edge是所有以point出发的边
    for (auto point_edge = index[point].adjacent; point_edge != nullptr;
         point_edge = point_edge->next) {
      if (dist[point_edge->end] > dist[point] + point_edge->weight) {
        dist[point_edge->end] = dist[point] + point_edge->weight;
        path[point_edge->end] = point;
        steps[point_edge->end] = steps[point] + 1;
        que.push({dist[point_edge->end], point_edge->end});
      } else if (dist[point_edge->end] == dist[point] + point_edge->weight) {
        if (steps[point_edge->end] > steps[point] + 1) {
          path[point_edge->end] = point;
          que.push({dist[point_edge->end], point_edge->end});
        } else
          ;
      }
    }
  }

  for (int i = 1; i <= n - 1; i++) {
    if (dist[i] == INT_MAX) continue;
    printf("0");
    Printanswer(index, i, path);
    printf("\n");
  }

  return 0;
}
