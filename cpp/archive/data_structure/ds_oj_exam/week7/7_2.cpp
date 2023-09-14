// 联盟数目 n次dijkstra
#define INT_MAX 0x3f3f3f3f
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Edge {
 public:
  Edge(int _end) : end(_end), weight(1), next(nullptr) {}
  int end;
  int weight;
  Edge* next;
};

// class Treenode {
//  public:
//   Treenode(int _val) : val(_val) { left = right = myfather = nullptr; }
//   int val;  // 结点编号
//   Treenode* left;
//   Treenode* right;
//   Treenode* myfather;
// };
//
// Treenode* whosmyfather(Treenode* root) {
//   if (root == nullptr) return root;
//   root->myfather = whosmyfather(root->myfather);
//   return root->myfather;
// }
//
int main() {
  //freopen("in.txt", "r", stdin);
  int T;
  scanf("%d", &T);
  for (int alltimes = 1; alltimes <= T; alltimes++) {
    int n;  // 公司数目 从1开始
    scanf("%d", &n);
    vector<Edge*> index(n + 10, nullptr);
 
    vector<vector<int>> dist(n + 10, vector<int>(n + 10, INT_MAX));
    for (int i = 1; i <= n; i++) dist[i][i] = 0;

    for (int i = 1; i <= n; i++) {
      int wayend;
      while (1) {
        scanf("%d", &wayend);
        if (wayend == 0) break;
        auto newnode = new Edge(wayend);
        if (index[i] == nullptr)
          index[i] = newnode;
        else {
          auto tmp = index[i];
          index[i] = newnode;
          index[i]->next = tmp;
        }
      }
    }

    auto checkgraph = [&]() {
      for (int i = 1; i <= n; i++) {
        printf("\n现在起点是%d:\n", i);
        for (auto p1 = index[i]; p1 != nullptr; p1 = p1->next)
          printf(" %d ", p1->end);
      }
    };

    // checkgraph();
    auto dijkstra = [&](int point) {
      // 处理第point号点的dijkstra
      priority_queue<pair<int, int>, vector<pair<int, int>>,
                     greater<pair<int, int>>>
          que;
      que.push({0, point});  // first存dist second存end
      for (int i = 1; i <= n; i++) {
        if (que.empty()) break;
        auto target = que.top().second;
        que.pop();
        for (auto p1 = index[target]; p1 != nullptr; p1 = p1->next) {
          int wayend = p1->end;
          // printf("下面左侧的值是%d,右侧的值是%d\n", dist[point][wayend],
          //        dist[point][target] + p1->weight);
          if (dist[point][wayend] > dist[point][target] + p1->weight) {
            dist[point][wayend] = dist[point][target] + p1->weight;
            que.push({dist[point][wayend], wayend});
          }
        }
      }
    };

    for (int i = 1; i <= n; i++) dijkstra(i);

    auto printdist = [=]() {
      for (int i = 1; i <= n; i++) {
        printf("\n");
        for (int j = 1; j <= n; j++) {
          if (dist[i][j] == INT_MAX)
            printf("MAX ");
          else
            printf("%d ", dist[i][j]);
        }
        printf("\n");
      }
      printf("\n");
      printf("\n");
    };

    //printdist();
    //   初始化
    vector<vector<int>> myset(n + 10, vector<int>());
    for (int i = 1; i <= n; i++) {
      myset[i].reserve(n + 10);
      myset[i].push_back(i);
    }
    int result = n;
    for (int i = 1; i <= n; i++) {
      // 找所有和第i个元素同集合的元素
      if (myset[i].empty()) continue;

      for (int j = i + 1; j <= n; j++) {
        if (myset[j].empty()) continue;
        int flag1 = 0;  // i里面有路出来
        int flag2 = 0;  // j有路进去
        for (int l : myset[i]) {
          if (flag1 == 1)
            ;
          else {
            if (dist[l][j] < INT_MAX) flag1 = 1;
          }

          if (flag2 == 1)
            ;
          else {
            if (dist[j][l] < INT_MAX) flag2 = 1;
          }

          if (flag1 == 1 && flag2 == 1) break;
        }

        if (flag1 == 0 || flag2 == 0)
          ;
        else {
          myset[i].push_back(j);
          myset[j].clear();
          myset[j].shrink_to_fit();
          result--;
        }
      }
    }
    printf("%d\n", result);
  }
  return 0;
}
