#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int rob(vector<int>& nums) {
        // 前k项的最大金额0 - k-1
        if (nums.size() <= 2) {
            if (nums.size() == 0)
                return 0;
            else if (nums.size() == 1)
                return nums[0];
            else
                return max(nums[0], nums[1]);
        }

        // 大于三的时候就可以用
        vector<int> max_income(nums.size(), 0);
        // 先把前几个初始化
        max_income[0] = nums[0];
        max_income[1] = max(nums[0], nums[1]);

        for (int i = 2; i < nums.size(); i++) {
            int robi = max_income[i - 2] + nums[i];
            int dont_robi = max_income[i - 1];
            max_income[i] = max(robi, dont_robi);
        }
        return max_income[nums.size() - 1];
    }
};

int main(int argc, char* argv[]) { return 0; }
