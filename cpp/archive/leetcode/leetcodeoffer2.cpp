#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Solution {
 public:
  string testfunction(string a, string b) {
    // string& minstring = test2;
    // string& maxstring = test;
    auto [maxstring, minstring] = [&a, &b]() -> pair<string&, string&> {
      if (a.size() > b.size()) return {a, b};
      return {b, a};
    }();

    string return_string(maxstring.size() + 2, '0');
    // auto printall = [&] {
    //   cout << "此时各个string的情况 按照min max return_string的顺序:" << endl;
    //   cout << minstring << endl;
    //   cout << maxstring << endl;
    //   cout << return_string << endl << endl;
    // };

    int flag = 0;  // 标识进位
    for (auto i = minstring.rbegin(), j = maxstring.rbegin(),
              k = return_string.rbegin();
         i < minstring.rend(); i++, j++, k++) {
      //printall();
      if (*i == '1' && *j == '1' && flag == 1) {
        *k = '1';
        flag = 1;
      } else if ((*i == '1' && *j == '1' && flag == 0) ||
                 (*i == '1' && *j == '0' && flag == 1) ||
                 (*i == '0' && *j == '1' && flag == 1)) {
        *k = '0';
        flag = 1;
      } else if ((*i == '1' && *j == '0' && flag == 0) ||
                 (*i == '0' && *j == '1' && flag == 0) ||
                 (*i == '0' && *j == '0' && flag == 1)) {
        *k = '1';
        flag = 0;
      } else {
        *k = '0';
        flag = 0;
      }
    }

    // cout << "一轮循环过去后" << return_string << endl;

    for (auto j = maxstring.rbegin() + minstring.size(),
              k = return_string.rbegin() + minstring.size();
         j < maxstring.rend(); j++, k++) {
      if (flag == 1 && *j == '1') {
        *k = '0';
        flag = 1;
      } else if ((flag == 1 && *j == '0') || (flag == 0 && *j == '1')) {
        *k = '1';
        flag = 0;
      } else {
        *k = '0';
        flag = 0;
      }
    }

    // cout << "二轮循环过去后" << return_string << endl;

    auto k = return_string.rbegin() + maxstring.size();
    if (flag == 1) *k = '1';

    // cout << "处理最后的进位" << return_string << endl;

    // 删除前导0
    auto i = return_string.begin();
    for (; i < return_string.end(); i++) {
      if (*i == '1') break;
    }

    return_string = string(i, return_string.end());

    if (return_string.size() == 0) return string(maxstring.size(), '0');
    return return_string;
  }
};

int main() {}
