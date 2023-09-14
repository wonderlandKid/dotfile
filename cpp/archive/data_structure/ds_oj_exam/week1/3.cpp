#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
using namespace std;

int main(void) {
  int array[100000] = {0};
  int target[100000] = {0};
  int result[26] = {0}; // 26个字母对应的数字 要是-1就表示没出现过
  for (int i = 0; i <= 25; i++)
    result[i] = -1;
  int arraysize = 0;
  int sum = 0;

  int tmp;
  for (int i = 0; i <= 100007; i++) {
    tmp = getchar();
    if (tmp == '\n')
      tmp = -1;
    if (tmp == -1)
      break;
    ++arraysize;
    array[i] = tmp;
  }
  for (int i = arraysize - 1; i >= 0; --i) {
    if (result[array[i] - 'a'] == -1) {
      target[i] = 'a' + sum;
      result[array[i] - 'a'] = sum;
      sum++;
    } else {
      target[i] = 'a' + result[array[i] - 'a'];
    }
  }

  for (int i = 0; i <= arraysize - 1; i++)
    printf("%c", target[i]);
  return 0;
}