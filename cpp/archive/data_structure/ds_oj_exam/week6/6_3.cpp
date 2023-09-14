// 去火车
#include <cstdio>
#define INT_MAX 4000000
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Edge {
 public:
  Edge(int _waybegin, int _wayend, int _weight)
      : waybegin(_waybegin), wayend(_wayend), weight(_weight), next(nullptr) {}
  int waybegin;
  int wayend;
  int weight;
  Edge* next;
};

class Result {
 public:
  Result() {
    flag = 0;
    min = INT_MAX;
    wherechange = 0;
  }
  int flag;  // 需不需要换乘轻轨
  int min;
  int wherechange;  // 哪里换乘轻轨
};

int main() {
  // freopen("in.txt", "r", stdin);
  int n, s, t;  // 1~n s(begin) t(end)
  while (scanf("%d%d%d", &n, &s, &t) != EOF) {
    vector<Edge*> index(n + 10, nullptr);
    int m;
    scanf("%d", &m);
    for (int i = 1; i < m + 1; i++) {
      int waybegin, wayend, weight;
      scanf("%d%d%d", &waybegin, &wayend, &weight);

      // 构建邻接表
      if (index[waybegin] == nullptr) {
        index[waybegin] = new Edge(waybegin, wayend, weight);
      } else {
        auto tmp = index[waybegin];
        index[waybegin] = new Edge(waybegin, wayend, weight);
        index[waybegin]->next = tmp;
      }

      if (index[wayend] == nullptr) {
        index[wayend] = new Edge(wayend, waybegin, weight);
      } else {
        auto tmp = index[wayend];
        index[wayend] = new Edge(wayend, waybegin, weight);
        index[wayend]->next = tmp;
      }
    }

    int k;
    scanf("%d", &k);
    vector<Edge> fastway;
    fastway.reserve(k + 10);
    for (int i = 1; i < k + 1; i++) {
      int waybegin, wayend, weight;
      scanf("%d%d%d", &waybegin, &wayend, &weight);
      fastway.push_back(Edge(waybegin, wayend, weight));
    }

    // dijkstra
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        que;
    //{dist, number}

    vector<int> dists(n + 10, INT_MAX);  // 起点dijkstra

    auto dijkstra = [&](int target) {
      que.push({0, target});
      dists[target] = 0;
      for (int i = 1; i <= n; i++) {
        if (que.empty()) break;
        auto node = que.top();
        que.pop();
        for (auto p1 = index[node.second]; p1 != nullptr; p1 = p1->next) {
          int k = p1->wayend;
          if (dists[k] > dists[node.second] + p1->weight) {
            dists[k] = dists[node.second] + p1->weight;
            que.push({dists[k], k});
          }
        }
      }
    };

    dijkstra(s);
    vector<int> dists_s(dists);

    dists.assign(n + 10, INT_MAX);

    dijkstra(t);

    // 现在dists里面存的是t的数据
    vector<int> dists_t(dists);
    dists.clear();
    dists.shrink_to_fit();
    // for (int i = 1; i <= n; i++) printf("%d ", dists_s[i]);
    // printf("\n\n");

    // for (int i = 1; i <= n; i++) printf("%d ", dists_t[i]);
    // printf("\n\n");

    // 遍历所有的边
    Result result;
    for (int i = 1; i <= n; i++) {
      for (auto p1 = index[i]; p1 != nullptr; p1 = p1->next) {
        int maybe1 = p1->weight + dists_s[p1->waybegin] + dists_t[p1->wayend];
        int maybe2 = p1->weight + dists_s[p1->wayend] + dists_t[p1->waybegin];
        if (maybe1 < result.min) result.min = maybe1;
        if (maybe2 < result.min) result.min = maybe2;
      }
    }

    // 下面遍历轻轨
    for (auto i : fastway) {
      int maybe1 = i.weight + dists_s[i.waybegin] + dists_t[i.wayend];
      int maybe2 = i.weight + dists_s[i.wayend] + dists_t[i.waybegin];

      if (maybe1 == result.min && result.flag == 1) {
        if (i.waybegin < result.wherechange) {
          result.wherechange = i.waybegin;
        }
      }

      if (maybe1 < result.min) {
        result.flag = 1;  // 表示换乘轻轨
        result.min = maybe1;
        result.wherechange = i.waybegin;
      }

      if (maybe2 == result.min && result.flag == 1) {
        if (i.wayend < result.wherechange) {
          result.wherechange = i.wayend;
        }
      }
      if (maybe2 < result.min) {
        result.flag = 1;  // 表示换乘轻轨
        result.min = maybe2;
        result.wherechange = i.wayend;
      }
    }

    if (result.flag)
      printf("%d\n%d\n", result.min, result.wherechange);

    else {
      printf("%d\nno metro\n", result.min);
    }
  }
  return 0;
}
