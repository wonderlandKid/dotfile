#include <fmt/core.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
class Solution {
   public:
    string reverseWords(string s) {
        stringstream buff{};
        buff << s;
        string returnvalue{};
        string tmp{};
        vector<string> stk{};
        while (buff >> tmp) stk.push_back(tmp);
        while (!stk.empty()) {
            tmp = stk.back();
            returnvalue += tmp;
            returnvalue.push_back(' ');
            stk.pop_back();
        }
        // delete a backspace
        returnvalue.pop_back();
        return returnvalue;
    }
};

int main() {
    Solution a;
    fmt::print("{}\n", a.reverseWords("Hello    World"));
}
