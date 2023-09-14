// 非常妙啊 LeetCode评论的题解确实比官方的好理解
// 这启示我们遇到不会的代码题目先找找规律 多手写几项

#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> countBits(int n) {
    if (n == 0) return {0};
    if (n == 1) return {0, 1};
    if (n == 2) return {0, 1, 1};
    vector<int> result(n + 1, 0);
    result[1] = 1;
    result[2] = 1;
    for (int i = 3; i <= n; i++) {
      if (i % 2 == 1)
        result[i] = result[(i - 1) / 2] + 1;
      else
        result[i] = result[i / 2];
    }
    return result;
  }
};
