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
    int maxArea(vector<int>& height) {
        auto beginiter = height.begin();
        auto enditer = height.end();
        enditer -= 1;

        // 现在开始求体积
        int max_area = 0;
        while (enditer - beginiter > 0) {
            max_area = max(int(enditer - beginiter) * min(*beginiter, *enditer),
                           max_area);
            if (*beginiter < *enditer) {
                beginiter += 1;
            } else {
                enditer -= 1;
            }
        }
        return max_area;
    }
};
int main() {
    Solution a;
    vector<int> test1{1, 8, 6, 2, 5, 4, 8, 3, 7};
    vector<int> test2{1, 1};
    fmt::print("{}\n", a.maxArea(test2));
    return 0;
}
