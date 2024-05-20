#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int getVectorVal(vector<vector<int>> const& dp, int x, int y) {
        // 返回dp[x][y] 如果超出索引则返回0
        if (x >= dp.size() || y >= dp[0].size()) return 0;

        return dp[x][y];
    }

    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = 1;
        for (int i = 1; i < n; i++) dp[0][i] = 1;
        for (int i = 1; i < m; i++) dp[i][0] = 1;

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }

        return dp[m - 1][n - 1];
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
