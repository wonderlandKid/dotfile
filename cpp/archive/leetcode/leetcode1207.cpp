#include <bits/stdc++.h>
#include <fmt/core.h>
#include <fmt/ranges.h>
using namespace std;
class Solution {
   public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int, int> arrmap{};
        for (const auto& i : arr) {
            auto tmp = arrmap.find(i);
            if (tmp == arrmap.end()) {
                arrmap.insert(make_pair(i, 1));
            } else {
                arrmap[i]++;
            }
        }

        unordered_set<int> onlyone{};
        for (const auto& i : arrmap) {
            if (onlyone.find(i.second) != onlyone.end()) {
                return false;
            }
            onlyone.insert(i.second);
        }
        return true;
    }
};

int main(int argc, char* argv[]) {
    Solution a;
    vector<int> vec1{1, 2, 3};
    vector<int> vec2{2, 4, 6};
    return 0;
}
