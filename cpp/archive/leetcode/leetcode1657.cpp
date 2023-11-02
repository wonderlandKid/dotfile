#include <algorithm>
#include <array>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
class Solution {
   public:
    bool closeStrings(string word1, string word2) {
        array<int, 26> word1_map{};
        array<int, 26> word2_map{};

        for (const auto& i : word1) {
            word1_map[i - 'a']++;
        }
        for (const auto& i : word2) {
            word2_map[i - 'a']++;
        }

        // 现在先来比较两个的字符种类是否相等
        for (int i = 0; i < word1_map.size(); i++) {
            if (((word1_map[i] > 0) ^ (word2_map[i] > 0)) != 0) return false;
        }

        sort(word1_map.begin(), word1_map.end());
        sort(word2_map.begin(), word2_map.end());

        for (int i = 0; i < word1_map.size(); i++) {
            if (word1_map[i] != word2_map[i]) return false;
        }
        return true;
    }
};
