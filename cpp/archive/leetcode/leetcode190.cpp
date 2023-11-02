#include <fmt/core.h>
#include <fmt/ranges.h>

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;
class Solution {
   public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t returnval = 0;
        for (int i = 31; i >= 0; i -= 1) {
            // 每次循环是更改returnval的第i位
            int tmp = n & 1;
            returnval |= (tmp << i);
            n >>= 1;
        }
        return returnval;
    }
};

int main() {
    Solution a;
    cout << a.reverseBits(43261596);
    return 0;
}
