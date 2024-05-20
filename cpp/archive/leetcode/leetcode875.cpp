#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    bool testSpeed(vector<int> const& piles, long int h, int k) {
        // 返回这个速度是不是可以做到
        // 速度k 时间h
        long int sum_time = 0;
        for (auto const& i : piles) {
            double result = (double)i / k;
            sum_time += ceil(result);
        }

        if (h - sum_time >= 0) return true;
        return false;
    }

    int minEatingSpeed(vector<int>& piles, int h) {
        // 先求一个绝对可以完成的速度
        // 因为总会有piles.size()堆 所以最快的速度就是piles里面的最大的
        auto it = max_element(piles.begin(), piles.end());
        int right = *it;
        int left = 1;
        int mid = (left + right) / 2;
        while (left + 1 < right) {
            if (testSpeed(piles, h, mid))
                right = mid;
            else
                left = mid;

            mid = (left + right) / 2;
        }
        if (testSpeed(piles, h, left)) return left;
        return right;
    }
};
int main(int argc, char* argv[]) {
    vector<int> piles{312884470};
    int h = 968709470;
    Solution a;
    cout << a.minEatingSpeed(piles, h);
    return 0;
}
