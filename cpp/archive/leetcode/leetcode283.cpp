#include <fmt/core.h>
#include <fmt/ranges.h>

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

class Solution {
   public:
    void moveZeroes(vector<int>& nums) {
        // 找0
        int p1 = 0;
        // 找非0
        int p2 = 0;
        while (p1 < nums.size() && p2 < nums.size()) {
            if (nums[p1] != 0) p1++;
            if (nums[p2] == 0) p2++;
            if (p1 >= nums.size() || p2 >= nums.size()) return;
            if (nums[p1] == 0 && nums[p2] != 0 && p1 < p2)
                swap(nums[p1], nums[p2]);
            if (nums[p1] == 0 && nums[p2] != 0 && p1 > p2) p2++;
        }
    }
};

int main() {
    Solution a;
    vector<int> test{1, 0};
    vector<int> test1{0};
    vector<int> test2{0, 1, 0, 3, 12};
    vector<int> test3{1, 0, 1};
    a.moveZeroes(test1);
    fmt::print("{}\n", test1);
    return 0;
}
