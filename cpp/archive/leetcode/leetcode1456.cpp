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
    int is_aeiou(const char& ch) {
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
    }
    int maxVowels(string s, int k) {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        auto right = s.begin() + k - 1;
        int max_count = 0;
        int cur_count = 0;
        for (auto i = s.begin(); i <= right; i++) {
            if (is_aeiou(*i)) cur_count++;
        }
        max_count = max(max_count, cur_count);
        for (right += 1; right < s.end(); right++) {
            cur_count += is_aeiou(*right);
            cur_count -= is_aeiou(*(right - k));
            max_count = max(max_count, cur_count);
        }
        return max_count;
    }
};
int main() {
    Solution a;
    vector<int> test1{1, 12, -5, -6, 50, 3};
    vector<int> test2{5};
    return 0;
}
