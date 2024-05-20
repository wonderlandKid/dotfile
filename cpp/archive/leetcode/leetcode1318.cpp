#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int minFlips(int a, int b, int c) {
        // 逐个遍历位即可

        int sum_reverse{};
        for (int i = 0; i < 32; i++) {
            // int是32bit
            int tmpa = a & 1;
            int tmpb = b & 1;
            int tmpc = c & 1;

            if (tmpc == 0) {
                // 翻转次数就是a b中为1的个数
                if (tmpa == 0 && tmpb == 0)
                    ;
                else if (tmpa == 1 && tmpb == 1)
                    sum_reverse += 2;
                else
                    sum_reverse += 1;
            } else {
                // tmpc == 1
                if ((tmpa | tmpb) == 1)
                    // 这里不能是continue 不然底下就不会右移了
                    ;
                else
                    sum_reverse += 1;
            }

            a = a >> 1;
            b = b >> 1;
            c = c >> 1;

            // bitset<8> aa(a);
            // bitset<8> bb(b);
            // bitset<8> cc(c);

            // cout << aa << ' ' << bb << ' ' << cc << endl;
        }
        return sum_reverse;
    }
};

int main(int argc, char* argv[]) {
    Solution test;
    int a = 2;
    int b = 6;
    int c = 5;
    cout << test.minFlips(a, b, c);
    // cout << a.longestCommonSubsequence(t1, t2);
    return 0;
}
