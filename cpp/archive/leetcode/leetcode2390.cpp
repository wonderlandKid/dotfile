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
    string removeStars(string s) {
        string returnstr{};
        returnstr.reserve(s.length());
        int deletecount{0};
        for (auto i = s.rbegin(); i < s.rend(); i++) {
            if (*i == '*')
                deletecount++;
            else {
                if (deletecount > 0) {
                    deletecount--;
                } else {
                    returnstr.push_back(*i);
                }
            }
        }
        reverse(returnstr.begin(), returnstr.end());
        return returnstr;
    }
};

int main(int argc, char* argv[]) { Solution a; }
