#include <bits/stdc++.h>
#include <fmt/core.h>
#include <fmt/ranges.h>
using namespace std;
class Solution {
   public:
    vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
        // create two hashmaps
        unordered_set<int> n1;
        unordered_set<int> n2;
        for (const auto& i : nums1) {
            n1.insert(i);
        }

        for (const auto& i : nums2) {
            n2.insert(i);
        }

        vector<vector<int>> retrunval{{}, {}};
        for (const auto& i : n1) {
            if (n2.find(i) == n2.end()) retrunval[0].push_back(i);
        }

        for (const auto& i : n2) {
            if (n1.find(i) == n1.end()) retrunval[1].push_back(i);
        }
        return retrunval;
    }
};

int main(int argc, char* argv[]) {
    Solution a;
    vector<int> vec1{1, 2, 3};
    vector<int> vec2{2, 4, 6};
    fmt::print("{}", a.findDifference(vec1, vec2));

    return 0;
}
