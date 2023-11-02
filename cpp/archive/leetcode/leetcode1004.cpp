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
    int longestOnes(vector<int>& nums, int k) {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        auto left = nums.begin();
        auto right = nums.begin();
        int max_val = 0;
        while (right < nums.end()) {
            if (*right == 0) {
                k--;
            }
            while (k < 0) {
                // 这里left不管怎么加一定会小于right 不会越界
                if (*left == 0) {
                    k++;
                }
                left++;
            }

            max_val = max(int(right - left + 1), max_val);
            right++;
        }
        return max_val;
    }
};
int main() {
    Solution a;
    vector<int> test1{1, 12, -5, -6, 50, 3};
    vector<int> test2{5};
    return 0;
}
