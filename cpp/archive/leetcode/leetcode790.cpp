#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    vector<vector<long int>> dp{1010, vector<long int>(4, 0)};
    const long int NUM = 1e9 + 7;
    void cal() {
        // 因为n只有1k个 直接先计算完就行
        dp[1][0] = 1;
        dp[1][1] = dp[1][2] = 0;
        dp[1][3] = 1;

        dp[2][0] = 1;
        dp[2][1] = 1;
        dp[2][2] = 1;
        dp[2][3] = 2;

        for (int i = 3; i < 1001; i++) {
            dp[i][0] = dp[i - 1][3];
            dp[i][1] = (dp[i - 1][2] + dp[i - 1][0]) % NUM;
            dp[i][2] = (dp[i - 1][1] + dp[i - 1][0]) % NUM;
            dp[i][3] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2] + dp[i - 1][3]) % NUM;
        }
        return;
    }

    int numTilings(int n) {
        cal();
        return dp[n][3];
    }
};

int main(int argc, char* argv[]) {
    Solution a;
    int k = 3;
    int n = 7;
    // auto res = a.combinationSum3(3, 7);
    // for (auto i : res) {
    //     for (auto j : i) {
    //         cout << j << endl;
    //     }
    // }
    // a.letterCombinations("23");
    return 0;
}
