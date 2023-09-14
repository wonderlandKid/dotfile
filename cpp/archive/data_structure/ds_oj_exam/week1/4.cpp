#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
using namespace std;

int main(void) {
  int n = 0, m = 0;
  long long int sum = 0; // n人数 m操作个数
  scanf("%d%d", &n, &m);
  int array[100010] = {0};
  long long int n_array[100010] = {0}; // 下标从0开始
  for (int i = 1; i <= n; i++) {
    scanf("%d", &array[i]);
    sum = sum + array[i];
    n_array[i] = sum;
  }

  int i = 0, j = 0;
  for (int p1 = 1; p1 < m; p1++) {
    scanf("%d%d", &i, &j);
    double tmp = n_array[j] - n_array[i - 1];
    double result = tmp / (j - i + 1);
    int a = result;
    printf("%d\n", a);
  }

  scanf("%d%d", &i, &j);
  double tmp = n_array[j] - n_array[i - 1];
  double result = tmp / (j - i + 1);
  int a = result;
  printf("%d", a);
  return 0;
}