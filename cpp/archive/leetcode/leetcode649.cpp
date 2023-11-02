#include <bits/stdc++.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

#include <array>

#include "backward.hpp"
using namespace std;
class Solution {
   public:
    string predictPartyVictory(string senate) {
        // 刚开始都有权利
        vector<int> have_power(senate.length(), 1);
        // 各自沉默多少人
        int R_silent = 0;
        int D_silent = 0;
        while (true) {
            // 如果没有沉默人 那么现在沉默多余的就是胜利者
            int can_silent = 0;
            for (int i = 0; i < senate.length(); i++) {
                if (senate[i] == 'R') {
                    if (D_silent > 0 && have_power[i] == 1) {
                        have_power[i] = 0;
                        can_silent = 1;
                        D_silent--;
                    } else {
                        if (have_power[i] == 1) R_silent++;
                    }

                    continue;
                }

                // senate[i] == 'D'
                if (R_silent > 0 && have_power[i] == 1) {
                    have_power[i] = 0;
                    can_silent = 1;
                    R_silent--;
                } else {
                    if (have_power[i] == 1) D_silent++;
                }
            }

            if (can_silent != 0) continue;

            if (R_silent > 0) return "Radiant";
            return "Dire";
        }
        return "error";
    }
};
int main(int argc, char* argv[]) {
    string test1{"RD"};
    Solution a;
    cout << a.predictPartyVictory(test1);
    return 0;
}
