#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct mypair {
  int x;
  int y;
  int time = 0;
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

int main() {
  freopen("in.txt", "r", stdin);
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

  // twoDarray目标容器 尝试鑫鑫子的贪心方法
  // 全为0表示一开始都没走过
  vector<vector<int>> flag(twoDarray.size(), vector<int>(twoDarray.size(), 0));
  int return_result = 0;
  auto cmp = [](const mypair& a, const mypair& b) -> bool {
    return a.time > b.time;
  };
  priority_queue<mypair, vector<mypair>, decltype(cmp)> que(cmp);
  flag[0][0] = 1;
  // x y time
  que.push({0, 0, 0});
  int N = twoDarray.size();
  while (1) {
    mypair current = que.top();
    if (current.time > return_result) return_result = current.time;
    //cout<<current.x<<' '<<current.y<<endl;
    que.pop();
    if (current.x + 1 <= N - 1 && flag[current.x + 1][current.y] == 0) {
      if (current.x + 1 == N - 1 && current.y == N - 1) break;
      que.push({current.x + 1, current.y, twoDarray[current.x + 1][current.y]});
      flag[current.x + 1][current.y] = 1;
    }
    if (current.y + 1 <= N - 1 && flag[current.x][current.y + 1] == 0) {
      if (current.x == N - 1 && current.y + 1 == N - 1) break;
      que.push({current.x, current.y + 1, twoDarray[current.x][current.y + 1]});
      flag[current.x][current.y + 1] = 1;
    }
    if (current.y - 1 >= 0 && flag[current.x][current.y - 1] == 0) {
      if (current.x == N - 1 && current.y - 1 == N - 1) break;
      que.push({current.x, current.y - 1, twoDarray[current.x][current.y - 1]});
      flag[current.x][current.y - 1] = 1;
    }
    if (current.x - 1 >= 0 && flag[current.x - 1][current.y] == 0) {
      if (current.x - 1 == N - 1 && current.y == N - 1) break;
      que.push({current.x - 1, current.y, twoDarray[current.x - 1][current.y]});
      flag[current.x - 1][current.y] = 1;
    }
  }
  if (twoDarray[N - 1][N - 1] > return_result)
    cout << twoDarray[N - 1][N - 1];
  else
    cout << return_result;
  return 0;
}
