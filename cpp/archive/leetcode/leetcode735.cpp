#include <fmt/core.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <array>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "backward.hpp"
using namespace std;
class Solution {
   public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> return_result{};
        return_result.reserve(asteroids.size());
        for (int i = 0; i < asteroids.size(); i++) {
            // 相信短路或
            if (return_result.empty() || asteroids[i] > 0) {
                return_result.push_back(asteroids[i]);
            } else {
                // 现在是不同方向和vector顶端
                if (return_result.back() < 0) {
                    return_result.push_back(asteroids[i]);
                    continue;
                }
                int tmp{0};
                while ((return_result.size() > 0) && return_result.back() > 0 &&
                       (abs(tmp = return_result.back()) < abs(asteroids[i]))) {
                    return_result.pop_back();
                }

                // equal or g
                if (return_result.empty() || return_result.back() < 0) {
                    return_result.push_back(asteroids[i]);
                } else if (abs(asteroids[i]) == abs(return_result.back())) {
                    return_result.pop_back();
                } else {
                    continue;
                }
            }
        }
        return return_result;
    };
};

int main(int argc, char* argv[]) {
    Solution a;
    vector<int> test1{-2, -2, 1, -2};
    fmt::print("{}\n", a.asteroidCollision(test1));
    return 0;
}
