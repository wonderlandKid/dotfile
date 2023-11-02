#include <fmt/core.h>
#include <fmt/ranges.h>

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;
class Solution {
   public:
    bool increasingTriplet(vector<int>& nums) {
        vector<int> leftmin(nums.size(), INT_MAX);
        vector<int> rightmax(nums.size(), INT_MIN);
        int leftminval = nums[0];
        int rightmaxval = nums.back();
        for (int i = 0; i < nums.size(); i += 1) {
            if (nums[i] < leftminval) leftminval = nums[i];
            leftmin[i] = leftminval;
        }

        for (int i = nums.size() - 1; i >= 0; i -= 1) {
            if (nums[i] > rightmaxval) rightmaxval = nums[i];
            rightmax[i] = rightmaxval;
        }
        // fmt::print("这里是left数组和right数组的值\n");
        // fmt::print("{} {}\n", leftmin, rightmax);
        for (int i = 0; i < nums.size(); i += 1) {
            if (i == 0 || i == nums.size() - 1) continue;
            if (leftmin[i - 1] < nums[i] && nums[i] < rightmax[i + 1])
                return true;
        }
        return false;
    }
};
int main() {
    Solution a;
    vector<int> test{2, 1, 5, 0, 4, 6};
    fmt::print("{}", a.increasingTriplet(test));
}
