#include <fmt/core.h>

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
    size_t return_hash_vector(const vector<int>& x) {
        // 返回一个vector的hash
        hash<int> hasher;
        size_t result = 0;
        for (const auto& i : x) {
            result ^= hasher(i) + 0x9e3779b9 + (result << 6) + (result >> 2);
        }
        return result;
    }

    int equalPairs(vector<vector<int>>& grid) {
        int allcount = 0;
        unordered_multiset<size_t> map1{};
        // 先扫描所有的行
        for (int i = 0; i < grid.size(); i++) {
            // hash值为x的在i列
            map1.insert(return_hash_vector(grid[i]));
        }

        // 分别计算每一个列的hash
        hash<int> hasher;
        for (int i = 0; i < grid.size(); i++) {
            // 因为是方阵所以列行数量一样
            size_t result = 0;
            // j是行号
            for (int j = 0; j < grid.size(); j++) {
                result ^= hasher(grid[j][i]) + 0x9e3779b9 + (result << 6) +
                          (result >> 2);
            }
            allcount += map1.count(result);
        }
        return allcount;
    }
};

int main(int argc, char* argv[]) {
    Solution a;
}
