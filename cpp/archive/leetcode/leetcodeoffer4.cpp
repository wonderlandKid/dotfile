#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
 public:
  int singleNumber(vector<int>& nums) {
    unordered_map<int, int> udmap;
    for (int i : nums) {
      if (udmap.find(i) == udmap.end())
        udmap.insert({i, 1});
      else {
        udmap[i]++;
      }
    }
    for (auto i : udmap) {
      if (i.second == 1) {
        return i.first;
      }
    }
    return -1;
  }
};
