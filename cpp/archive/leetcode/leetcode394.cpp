#include <fmt/core.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <array>
#include <charconv>
#include <map>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "backward.hpp"
using namespace std;
class Solution {
   public:
    int return_str_int(string_view str, const int index) {
        int begin = index;
        while (isdigit(str[begin])) {
            ++begin;
        }
        int returnval{};
        from_chars(str.data() + index, str.data() + begin, returnval);
        return returnval;
    }

    string decodeString(std::string s) {
        string return_val;
        return_val.reserve(s.length());
        for (auto i = s.begin(); i < s.end();) {
            if (!isdigit(*i)) {
                return_val.push_back(*i);
                i++;
                continue;
            }

            // 现在是digit
            // 先获取dight 然后递归调用
            int index = i - s.begin();
            int strtimes = return_str_int(s, index);
            while (s[index] != '[') index++;
            int begin = index + 1;
            // 现在求和这个begin相对应的右括号
            int count = 0;
            while (true) {
                if (s[index] == '[')
                    count++;
                else if (s[index] == ']') {
                    count--;
                    if (count == 0) break;
                }
                index++;
            }
            int end = index;
            for (int k = 1; k <= strtimes; k++) {
                return_val += decodeString(s.substr(begin, end - begin));
            }

            i = s.begin() + index + 1;
        }
        return return_val;
    }
};

int main(int argc, char* argv[]) {
    string test{"3[a2[c]]"};
    Solution a;
    cout << a.decodeString(test);
    return 0;
}
