#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
//[i, j]表示a的前i个字母和b的前j个字母之间的编辑距离

class Solution {
 public:
  vector<vector<int>> buffer{};
  int get_distance_recursive(string& a, int i, string& b, int j) {
    // 其中这里的a一定是短于b的
    // 返回a字符串的0~i-1(前i位)和b字符串的0~j-1(前j位)之间的编辑距离
    // cout << a.substr(0, i) << endl;
    // cout << b.substr(0, j) << endl;
    // auto flaga = a.substr(0, i);
    // auto flagb = b.substr(0, j);
    // cout << i << endl << j << endl;
    if (buffer[i][j] != -1) {
      return buffer[i][j];
    }
    if (i == 0) {
      buffer[i][j] = j;
      return j;
    }
    if (j == 0) {
      buffer[i][j] = i;
      return i;
    }

    // 现在两个都不为0
    // 如果最后一位相等 那么只需要求buffer[i-1][j-1];
    if (a[i - 1] == b[j - 1]) {
      int val1, val2, val3;
      val1 = val2 = val3 = 0;
      if (buffer[i][j - 1] == -1) {
        get_distance_recursive(a, i, b, j - 1);
      }
      val1 = buffer[i][j - 1];

      if (buffer[i - 1][j] == -1) {
        get_distance_recursive(a, i - 1, b, j);
      }
      val2 = buffer[i - 1][j];

      if (buffer[i - 1][j - 1] == -1) {
        get_distance_recursive(a, i - 1, b, j - 1);
      }
      val3 = buffer[i - 1][j - 1];

      buffer[i][j] = min(min(val1, val2), val3 - 1) + 1;
      return buffer[i][j];
    }

    int val1, val2, val3;
    val1 = val2 = val3 = 0;
    if (buffer[i][j - 1] == -1) {
      get_distance_recursive(a, i, b, j - 1);
    }
    val1 = buffer[i][j - 1];

    if (buffer[i - 1][j] == -1) {
      get_distance_recursive(a, i - 1, b, j);
    }
    val2 = buffer[i - 1][j];

    if (buffer[i - 1][j - 1] == -1) {
      get_distance_recursive(a, i - 1, b, j - 1);
    }
    val3 = buffer[i - 1][j - 1];

    buffer[i][j] = min(min(val1, val2), val3) + 1;
    return buffer[i][j];
  }

  int get_distance_loop(string& word1, int i, string& word2, int j) {
    // 求word1的前i项和word2的前j项的编辑距离
    // buffer需要的空间是0~i和0~j
    for (int tmp = 0; tmp <= i; tmp++) buffer[tmp][0] = tmp;
    for (int tmp = 0; tmp <= j; tmp++) buffer[0][tmp] = tmp;
    for (int p1 = 1; p1 <= i; p1++) {
      for (int p2 = 1; p2 <= j; p2++) {
        // 现在计算buffer[p1][p2]
        int left = buffer[p1][p2 - 1];
        int down = buffer[p1 - 1][p2];
        int left_down = buffer[p1 - 1][p2 - 1];
        if (word1[p1 - 1] == word2[p2 - 1]) {
          buffer[p1][p2] = min(min(left + 1, down + 1), left_down);
        } else {
          buffer[p1][p2] = min(min(left + 1, down + 1), left_down + 1);
        }
      }
    }
    return buffer[i][j];
  }
  int minDistance(string word1, string word2) {
    if (word1.size() * word2.size() == 0) return word1.size() + word2.size();
    // a为行 b为列
    if (word1.size() < word2.size()) {
      buffer = vector<vector<int>>(word1.size() + 3,
                                   vector<int>(word2.size() + 3, -1));
      return get_distance_loop(word1, word1.size(), word2, word2.size());
    } else {
      buffer = vector<vector<int>>(word2.size() + 3,
                                   vector<int>(word1.size() + 3, -1));
      return get_distance_loop(word2, word2.size(), word1, word1.size());
    }
  }
};
int main() {
  Solution a;
  cout << "开始" << endl;
  cout << a.minDistance("horse", "ros") << endl;
  return 0;
}
