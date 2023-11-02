#include <fmt/core.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <iostream>
#include <type_traits>
#include <vector>
using namespace std;
class Solution {
   public:
    bool check_place_can(const vector<int>& flowerbed, int index) {
        if (flowerbed[index] == 1) return false;
        bool leftok = 0;
        bool rightok = 0;
        if (index - 1 < 0)
            leftok = true;
        else {
            if (flowerbed[index - 1] == 0) leftok = true;
        }

        if (leftok == false) return false;

        if (index + 1 >= flowerbed.size())
            rightok = true;
        else {
            if (flowerbed[index + 1] == 0) rightok = true;
        }

        return rightok && leftok;
    }

    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int count = 0;
        for (int i = 0; i < flowerbed.size(); i += 1) {
            bool curresult = true;
            if (flowerbed[i] == 1) {
                curresult = false;
                i += 1;
            } else {
                curresult = check_place_can(flowerbed, i);
                if (curresult == true) {
                    flowerbed[i] = 1;
                    count += 1;
                    i += 1;
                }
            }
        }

        return count >= n;
    }
};

int main() {
    Solution a;
    vector<int> test1{1, 0, 0, 0, 0, 0, 1};
    fmt::print("{}", a.canPlaceFlowers(test1, 2));
}
