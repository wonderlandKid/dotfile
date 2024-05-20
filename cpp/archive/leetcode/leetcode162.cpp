#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int getNumsVal(vector<int> const& nums, int downindex) {
        if (downindex < 0 || downindex >= nums.size())
            return INT_MIN;
        else
            return nums[downindex];
    }

    int findPeakElement(vector<int>& nums) {
        // 使用二分 实际上是爬坡方法的改进
        // 用left和right标记搜索的范围
        int left = 0;
        int right = nums.size() - 1;
        int mid = (left + right) / 2;
        while (left + 1 < right) {
            int leftval = getNumsVal(nums, mid - 1);
            int rightval = getNumsVal(nums, mid + 1);
            int val = getNumsVal(nums, mid);
            if (val > leftval && val > rightval) return mid;

            if (leftval > val)
                right = mid;
            else
                left = mid;

            mid = (left + right) / 2;
        }

        // 到最后判断一次
        if (getNumsVal(nums, left) > getNumsVal(nums, left - 1) && getNumsVal(nums, left) > getNumsVal(nums, left + 1))
            return left;
        else
            return right;
    }
};

int main(int argc, char* argv[]) { return 0; }
