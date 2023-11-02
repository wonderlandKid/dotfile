#include <fmt/core.h>
#include <fmt/ranges.h>

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;
class Solution {
   public:
    bool isSubsequence(string s, string t) {
        if (s.empty()) return true;
        int p1 = 0;
        int p2 = 0;
        // 判断s是不是t的子串
        while (p1 < s.length() && p2 < t.length()) {
            if (s[p1] == t[p2]) {
                p1++;
                p2++;
            } else {
                p2++;
            }
        }

        if (p1 >= s.length()) return true;
        return false;
    }
};

int main() {
    Solution a;
    return 0;
}
