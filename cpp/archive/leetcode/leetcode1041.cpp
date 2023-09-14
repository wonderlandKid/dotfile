#include <bits/stdc++.h>
using namespace std;
class Solution {
 public:
  bool isRobotBounded(string instructions) {
    int north_south = 0;  // 向北为正
    int east_west = 0;    // 向东为正
    int target = 0;       // 北0 东1 南2 西3
    for (auto i : instructions) {
      if (i == 'G') {
        gogogo(target, north_south, east_west);
      } else if (i == 'L') {
        target--;
        if (target < 0) target += 4;
      } else if (i == 'R') {
        target++;
        if (target > 3) target -= 4;
      }
    }
    if (north_south == 0 && east_west == 0) return true;
    if (target != 0) return true;
    return false;
  }
  static void gogogo(int i, int& north_south, int& east_west) {
    if (i == 0)
      north_south++;
    else if (i == 1)
      east_west++;
    else if (i == 2)
      north_south--;
    else if (i == 3)
      east_west--;
    else
      printf("ERROR!");
  }
};

int main(){
  Solution a;
  string test = "GG";
  if(a.isRobotBounded(test)) printf("true");
}
