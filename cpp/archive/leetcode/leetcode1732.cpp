#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int largestAltitude(vector<int>& gain) {
        int cur_val = 0;
        int max_val = 0;
        for (const auto& i : gain) {
            cur_val += i;
            max_val = max(max_val, cur_val);
        }
        return max_val;
    }
};
