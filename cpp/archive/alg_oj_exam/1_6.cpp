
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct mypair {
  int x;
  int y;
};

int getnumber(string& str, int& i) {
  // 从第i个位置之后读入一个数字
  string intstring{};
  while (isdigit(str[i])) {
    intstring += str[i];
    i++;
  }
  return stoi(intstring);
}

int checktime(const vector<vector<int>>& a, int time) {
  // 查看time时间内能否到达(N-1,N-1) 使用深搜
  // x和y的取值范围是0~N-1
  int N = a.size();
  vector<vector<int>> flag(N, vector<int>(N, 0));
  flag[0][0] = 1;
  queue<mypair> que;
  que.push({0, 0});
  while (!que.empty()) {
    // for (auto i : twoDarray) {
    //   for (auto j : i) cout << j << ' ';
    //   cout << endl;
    // }
    mypair current = que.front();
    que.pop();
    // 懒得封装函数嗯凑四个方向 左上方排到后面
    // 先尝试不要两个方向
    if (current.x + 1 <= N - 1 && flag[current.x + 1][current.y] == 0) {
      if (a[current.x + 1][current.y] <= time) {
        // 进入此说明能够从这里通过
        if (current.x + 1 == N - 1 && current.y == N - 1)
          return 1;  // 即可以达到
        flag[current.x + 1][current.y] = 1;
        que.push({current.x + 1, current.y});
      }
    }
    if (current.y + 1 <= N - 1 && flag[current.x][current.y + 1] == 0) {
      if (a[current.x][current.y + 1] <= time) {
        // 进入此说明能够从这里通过
        if (current.x == N - 1 && current.y + 1 == N - 1)
          return 1;  // 即可以达到
        flag[current.x][current.y + 1] = 1;
        que.push({current.x, current.y + 1});
      }
    }
    if (current.y - 1 >= 0 && flag[current.x][current.y - 1] == 0) {
      if (a[current.x][current.y - 1] <= time) {
        // 进入此说明能够从这里通过
        if (current.x == N - 1 && current.y - 1 == N - 1)
          return 1;  // 即可以达到
        flag[current.x][current.y - 1] = 1;
        que.push({current.x, current.y - 1});
      }
    }
    if (current.x - 1 >= 0 && flag[current.x - 1][current.y] == 0) {
      if (a[current.x - 1][current.y] <= time) {
        // 进入此说明能够从这里通过
        if (current.x - 1 == N - 1 && current.y == N - 1)
          return 1;  // 即可以达到
        flag[current.x - 1][current.y] = 1;
        que.push({current.x - 1, current.y});
      }
    }
  }
  return 0;
}

int main() {
  string inputstr;
  cin >> inputstr;

  vector<vector<int>> twoDarray;
  int line = -1;

  int maxheight = 0;
  auto strlen = inputstr.length();
  for (int i = 1; i <= strlen - 1;) {
    char ch = inputstr[i];
    if (ch == '[') {
      i++;
      line++;
      twoDarray.push_back(vector<int>());
    } else if (ch == ',' || ch == ']') {
      i++;
    } else if (isdigit(ch)) {
      int num = getnumber(inputstr, i);
      if (num > maxheight) maxheight = num;
      twoDarray[line].push_back(num);
    }
  }
  // for (auto i : twoDarray) {
  //   for (auto j : i) cout << j << ' ';
  //   cout << endl;
  // }
  // 居然是试根吗?
  int printresult;
  int lesser = 0;
  while (1) {
    if (maxheight == lesser + 1) {
      if (lesser == 0 && maxheight == 1) {
        printresult = 0;
        break;
      }
      printresult = maxheight;
      break;
    }
    int mid = (maxheight + lesser) / 2;
    if (checktime(twoDarray, mid)) {
      maxheight = mid;
    } else {
      lesser = mid;
    }
  }
  cout << printresult;
  return 0;
}
