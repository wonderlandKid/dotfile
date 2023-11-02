#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <vector>
using namespace std;
class Solution {
   public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        auto max = 0;
        for_each(candies.begin(), candies.end(), [&max](auto& i) {
            if (i > max) max = i;
        });
        vector<bool> returnresult{};
        returnresult.reserve(candies.size());
        for_each(candies.begin(), candies.end(), [&](auto& i) {
            if (i + extraCandies >= max)
                returnresult.push_back(true);
            else
                returnresult.push_back(false);
        });
        return returnresult;
    }
};

int main() {
    Solution a;
    vector<int> vec{12, 1, 12};
    fmt::print("{}", a.kidsWithCandies(vec, 10));
    return 0;
}
