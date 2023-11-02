#include <fmt/core.h>
#include <fmt/ranges.h>

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

class Solution {
   public:
    void add_string(vector<char>& chars, int& slowest, string& str,
                    char oldchar) {
        chars[slowest] = oldchar;
        slowest++;
        for (const auto& i : str) {
            chars[slowest] = i;
            slowest++;
        }
        return;
    }

    int compress(vector<char>& chars) {
        int slowp = 0;
        int fastp = 0;
        int slowest = 0;
        for (; fastp < chars.size();) {
            int count = 0;
            char oldchar = 0;
            while (fastp < chars.size() && chars[fastp] == chars[slowp]) {
                fastp += 1;
                count += 1;
            }
            oldchar = chars[slowp];
            string countstr(to_string(count));
            if (count != 1)
                add_string(chars, slowest, countstr, oldchar);
            else {
                chars[slowest] = oldchar;
                slowest++;
            };
            slowp = fastp;
        }
        return slowest;
    }
};

int main() {
    Solution a;
    vector<char> test{'a', 'a', 'a', 'b', 'b', 'a', 'a'};
    vector<char> test1{'a'};
    fmt::print("{}\n", a.compress(test));
    return 0;
}
