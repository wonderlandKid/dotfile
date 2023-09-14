#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int main(void) {
  static char array[10000000] = {0};
  static int next[10000000] = {0};
  int m; // 字符串长度
  long long int result = 0;
  scanf("%d", &m);
  getchar();
  for (int i = 0; i <= m - 1; i++)
    scanf("%c", &array[i]);

  // 还是先生成next数组吧家人们 多生成一位
  next[0] = -1;
  int i = 0, j = 0;
  for (i = 0; i <= m - 1; i++) {
    j = next[i];
    while (j >= 0 && array[i] != array[j])
      j = next[j];
    next[i + 1] = ++j;
  }

  // 按位依次考察
  // 每一轮算出来的最短前后缀可以直接存到next数组里面便于下次使用
  int tmp = 0; // 每一轮的秩
  for (i = 0; i <= m - 1; i++) {
    if (next[i + 1] == 0) {
      tmp = 0;
      next[i + 1] = 0;
    } else if (next[i + 1] == 1 || array[i] == array[0]) {
      tmp = i;
      next[i + 1] = 1;
    } else {
      if (next[next[i + 1]] != 0) {
        next[i + 1] = next[next[i + 1]];
        tmp = i + 1 - next[i + 1];
      } else {
        tmp = i + 1 - next[i + 1];
      }
    }
    // printf("这是考察第%d个字符, 此时计算出来的秩为%d\n", i, tmp);
    // for(int i=0; i<=6; i++) printf("%d", next[i]);
    // printf("\n");
    result += tmp;
  }

  printf("%lld\n", result);
  return 0;
}
