#include <fmt/core.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <tuple>
#include <vector>

using namespace std;
class Solution {
   public:
    double findMaxAverage(vector<int>& nums, int k) {
        int max_sum = numeric_limits<int>::min();
        int cur_sum = 0;
        auto left = nums.begin();
        auto right = left + k - 1;
        for (auto i = left; i <= right; i++) cur_sum += *i;
        for (auto i = right; i < nums.end(); i++) {
            max_sum = max(max_sum, cur_sum);
            cur_sum -= *left;
            left += 1;
            right += 1;
            if (right == nums.end()) break;
            cur_sum += *right;
        }
        return double(max_sum) / k;
    }
};
int main() {
    Solution a;
    vector<int> test1{1, 12, -5, -6, 50, 3};
    vector<int> test2{5};
    cout << a.findMaxAverage(test2, 1);
    return 0;
}
