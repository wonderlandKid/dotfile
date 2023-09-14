// map<key,value>
// map<value, position>
#include <bits/stdc++.h>
using namespace std;
class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    vector<int> return_result;
    unordered_map<int, int> hashmap;
    int numssize = nums.size();
    for (int i = 0; i <= numssize - 1; i++) {
      hashmap.insert({nums[i], i});
    }

    auto unvalidend = hashmap.end();
    for (int i = 0; i <= numssize - 1; i++) {
      int item = target - nums[i];
      auto result = hashmap.find(item);
      if (result != unvalidend && i != result->second) {
        return {result->second, i};
        break;
      }
    }
    return {};
  }
};
