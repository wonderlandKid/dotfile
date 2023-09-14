// 猜数字
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;
int main(void) {
  string s; // 从0到s.size()-1
  int next[100000] = {0};
  while (cin >> s) {
    int p = 0, q = 0;
    const int slen = s.size();

    if (slen == 1)
      printf("1\n");
    else {
      string s_re = s;
      // 字符串倒置
      int i = 0;
      int j = slen - 1;
      for (; i <= slen - 1; i++, j--) {
        s_re[i] = s[j];
      }

      // 求s_re的next数组 从0求到s.size()
      i = j = 0;
      next[i] = -1;
      for (i = 0; i <= slen - 1; i++) {
        j = next[i];
        while (j >= 0 && s_re[i] != s_re[j])
          j = next[j];
        next[i + 1] = j + 1;
      }

      {
        int max = 0;
        for (int i = 0; i <= slen; i++) {
          if (next[i] > max)
            max = next[i];
        }
        p = max;
      }

      // 求q
      while (1) {
        if (next[slen] == 0 || next[slen] == 1) {
          q = slen;
          break;
        }
        int tmp = 0;
        tmp = next[slen];
        if (next[next[slen - tmp]] != -1) {
          q = slen;
          break;
        }
        int i = 0, j = 0;
        j = slen - next[slen] + 1;
        i = next[slen] - 1 - 1;
        while (1) {
          if (i == -1)
            break;
          if (s[i] == s[slen - 1] && s[j] == s[0])
            break;
          i--;
          j++;
        }
        if (i == -1) {
          q = slen;
          break;
        } else {
          q = slen - 2 * (i + 1);
          if (q < 0)
            q = 0;
          break;
        }
      }

      printf("%d\n", p + q);
    }
  }

  return 0;
}