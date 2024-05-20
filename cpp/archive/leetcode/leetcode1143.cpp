#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int longestCommonSubsequence(string text1, string text2) {
        // dp[m][n]表示子串1的前m和子串2的前n个字母的最长公共子序列长度是多少
        vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size() + 1, 0));
        for (int i = 1; i <= text1.size(); i++) {
            for (int j = 1; j <= text2.size(); j++) {
                if (text1[i - 1] == text2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[text1.size()][text2.size()];
    }
};

int main(int argc, char* argv[]) {
    Solution a;
    string t1("abc");
    string t2("def");
    cout << a.longestCommonSubsequence(t1, t2);
    return 0;
}
