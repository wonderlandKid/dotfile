#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int pivotIndex(vector<int>& nums) {
        // sum from left to right
        int whole_sum = 0;
        int left_sum = 0;
        for_each(nums.begin(), nums.end(),
                 [&whole_sum](auto& a) { whole_sum += a; });
        for (int i = 0; i < nums.size(); i++) {
            left_sum += nums[i];
            if (left_sum - nums[i] == whole_sum - left_sum) return i;
        }
        return -1;
    }
};

int main(int argc, char* argv[]) { return 0; }
