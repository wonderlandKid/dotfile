#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

/**
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 */

int guess(int num);

class Solution {
   public:
    int guessNumber(int n) {
        // 范围是1 - n
        auto min = 1;
        auto max = n;
        auto mid = min + (max - min) / 2;
        while (min + 1 < max) {
            auto result = guess(mid);
            if (result == 0)
                return mid;
            else if (result == -1) {
                max = mid;
                mid = min + (max - min) / 2;
            } else {
                // result == 1
                min = mid;
                mid = min + (max - min) / 2;
            }
        }

        // 此时min + 1 == max
        if (guess(min) == 0) return min;
        return max;
    }
};

int main(int argc, char* argv[]) {
    vector<vector<int>> case1{{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    // Solution a;
    // cout << a.orangesRotting(case1);
}
