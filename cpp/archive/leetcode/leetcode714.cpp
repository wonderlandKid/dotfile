#include <bits/stdc++.h>
using namespace std;


class Solution {
   public:
    int maxProfit(vector<int>& prices, int fee) {
        // dp[i][0] 表示在第i天结束之后未持有股票获得的最大利润
        vector<vector<int>> dp(prices.size(), vector<int>(2, 0));

        dp[0][0] = 0;
        dp[0][1] = -prices[0];

        for (int i = 1; i < prices.size(); i++) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i] - fee);
            dp[i][1] = max(dp[i - 1][0] - prices[i], dp[i - 1][1]);
        }

        return dp[prices.size() - 1][0];
    }
};

int main(int argc, char* argv[]) {
    Solution a;
    string t1("abc");
    string t2("def");
    // cout << a.longestCommonSubsequence(t1, t2);
    return 0;
}
