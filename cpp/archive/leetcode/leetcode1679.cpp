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
    int maxOperations(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        // 从两侧向内
        auto beginiter = nums.begin();
        auto enditer = nums.end();
        enditer -= 1;
        int count = 0;
        while (beginiter < enditer) {
            if (*beginiter + *enditer < k) {
                beginiter++;
            } else if (*beginiter + *enditer > k) {
                enditer--;
            } else {
                // 这个时候相等
                count++;
                beginiter++;
                enditer--;
            }
        }
        return count;
    }
};
int main() {
    Solution a;
    vector<int> test1{1, 8, 6, 2, 5, 4, 8, 3, 7};
    vector<int> test2{1, 1};
    return 0;
}
