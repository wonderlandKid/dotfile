#include <fmt/core.h>
#include <fmt/ranges.h>

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;
class Solution {
   public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<tuple<int, int>> mutiplyresult(nums.size(), tuple{1, 1});
        int mutiply = 1;
        for (int i = 0; i < nums.size(); i++) {
            if (i == 0) continue;
            mutiply *= nums[i - 1];
            get<0>(mutiplyresult[i]) = mutiply;
        }

        mutiply = 1;
        for (int i = nums.size() - 1; i >= 0; i--) {
            if (i == nums.size() - 1) continue;
            mutiply *= nums[i + 1];
            get<1>(mutiplyresult[i]) = mutiply;
        }

        vector<int> returnresult;
        returnresult.reserve(nums.size());

        for (int i = 0; i < nums.size(); i++) {
            auto [leftmutiply, rightmutiply] = mutiplyresult[i];
            returnresult.push_back(leftmutiply * rightmutiply);
        }
        return returnresult;
    }
};
int main() {
    Solution a;
    vector<int> test{1, 2, 3, 4};
    fmt::print("{}", a.productExceptSelf(test));
}
