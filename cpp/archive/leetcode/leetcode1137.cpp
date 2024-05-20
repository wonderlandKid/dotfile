#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int tribonacci(int n) {
        if (n <= 2) {
            if (n == 0)
                return 0;
            else if (n == 1)
                return 1;
            else
                return 1;
        }
        vector<int> nums(n + 1, -1);
        nums[0] = 0;
        nums[1] = 1;
        nums[2] = 1;
        for (int i = 3; i < n + 1; i++) {
            nums[i] = nums[i - 1] + nums[i - 2] + nums[i - 3];
        }
        return nums[n];
    }
};

int main(int argc, char *argv[]) { return 0; }
