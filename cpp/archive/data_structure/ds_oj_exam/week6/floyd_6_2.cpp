#include <cstdio>
#include <vector>
#define INF 0x3f3f3f3f
using namespace std;

int main() {
  //freopen("in.txt", "r", stdin);

  int n, e;
  scanf("%d%d", &n, &e);

  // n+2 * n+2 全为INF 除了自己到自己是0
  vector<vector<int>> array(n + 2, vector<int>(n + 2, INF));
  for (int i = 1; i <= n; i++) array[i][i] = 0;

  // i->j最短路径条数 初始化 全0
  vector<vector<long long int>> waytimes(n + 2, vector<long long int>(n + 2, 0));

  for (int i = 1; i <= e; i++) {
    int waybegin, wayend, weight;
    scanf("%d%d%d", &waybegin, &wayend, &weight);

    array[waybegin][wayend] = weight;
    array[wayend][waybegin] = weight;
    waytimes[waybegin][wayend] = 1;
    waytimes[wayend][waybegin] = 1;
  }

  auto dists = array;  // 距离的矩阵最开始和邻接矩阵一样

  // floyd
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      if (i == k) continue;
      for (int j = 1; j <= n; j++) {
        if (j == k) continue;
        if (j == i) continue;
        if (dists[i][k] + dists[k][j] < dists[i][j]) {
          dists[i][j] = dists[i][k] + dists[k][j];
          /*这两个地方*/
          waytimes[i][j] = waytimes[i][k] * waytimes[k][j];
        } else if (dists[i][k] + dists[k][j] == dists[i][j]) {
          /*我不会*/
          waytimes[i][j] += waytimes[i][k] * waytimes[k][j];
        }
      }
    }
  }

  // 检查dists最后的数组
  // printf("\n\n这是dists数组的结果:\n\n");
  // for (int i = 1; i <= n; i++) {
  //   for (int j = 1; j <= n; j++) {
  //     printf("%d ", dists[i][j]);
  //   }
  //   printf("\n");
  // }

  // // 检查waytimes最后的数组
  // printf("\n\n这是waytimes数组的结果:\n\n");
  // for (int i = 1; i <= n; i++) {
  //   for (int j = 1; j <= n; j++) {
  //     printf("%d ", waytimes[i][j]);
  //   }
  //   printf("\n");
  // }

  for (int k = 1; k <= n; k++) {
    double result = 0;
    for (int i = 1; i <= n; i++) {
      if (i == k) continue;
      for (int j = 1; j <= n; j++) {
        if (j == k) continue;
        
        //说明i到j没有路 这个时候跳过这一轮
        if (waytimes[i][j] == 0) continue;

        //说明经过k的ij最短路没有 这个时候跳过(或者说result+=0)
        if (dists[i][k] == INF || dists[k][j] == INF) continue;
        
        if (dists[i][k] + dists[k][j] == dists[i][j]) {
          long long int Nijk = waytimes[i][k] * waytimes[k][j];
          double tmp = (double)dists[i][j] * (double)Nijk / waytimes[i][j];
          result += tmp;
        } else if (dists[i][k] + dists[k][j] > dists[i][j]) {
          result += 0;
        } else
          ;
      }
    }
    printf("%.3lf\n", result);
  }

  return 0;
}
