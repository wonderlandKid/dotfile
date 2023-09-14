#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
int main() {
  // 查到的满足进阶条件的算法
  vector<int> array;
  array.reserve(5000);
  while (1) {
    char tmp;
    int i;
    scanf("%c", &tmp);
    if (tmp == ']') break;
    scanf("%d", &i);
    array.push_back(i);
  }
  int current = 0;
  int vote = 0;
  for (int i : array) {
    if (vote == 0) {
      current = i;
      vote = 1;
      continue;
    }
    if (i == current)
      vote++;
    else {
      vote--;
    }
  }

  if (current == 0) {
    cout << "NA";
    return 0;
  }
  // 否则current是一个众数
  int count = 0;
  for (int i : array) {
    if (i == current) count++;
  }
  if (count > array.size() / 2)
    cout << current;
  else
    cout << "NA";
  return 0;
}
