#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int calVal(vector<int>& cur_result, int p) {
        const int MINUS_P = -1;
        const int BREAK = -2;
        // 计算p位置值应该变为多少 如果是-1表示这个位置已经穷尽了 需要p--
        // -2表示直接退出
        if (p == 0) {
            int newval = cur_result[p] + 1;
            int zero_max_val = 9 - (cur_result.size() - 1);
            if (newval > zero_max_val) return BREAK;
            return newval;
        }

        if (cur_result[p] == 0) {
            // 表示这个地方是新开拓的
            int preval = cur_result[p - 1];
            int newval = preval + 1;
            if (newval <= 9) return newval;

            // 需要p--
            return MINUS_P;
        }

        int newval = cur_result[p] + 1;
        if (newval <= 9) return newval;

        // 需要p--
        return MINUS_P;
    }

    vector<vector<int>> combinationSum3(int k, int n) {
        // 和为n         个数为k
        // 0 - k-1个数字需要选择
        const int MINUS_P = -1;
        const int BREAK = -2;
        {
            // 先做特判
            int sum = 0;
            for (int i = 1; i <= k; i++) sum += i;
            if (sum > n) return {};
        }

        int p = 0;
        vector<int> cur_result(k, 0);
        vector<vector<int>> return_vec;

        while (true) {
            if (p == k) {
                // 判断和
                auto sum = accumulate(cur_result.begin(), cur_result.end(), 0);
                if (sum == n) return_vec.push_back(cur_result);

                p--;
            }

            if (p == -1) break;

            // 当前值的确定需要依赖上一个值
            int cal_val_res = calVal(cur_result, p);

            if (cal_val_res == MINUS_P) {
                // 表示当前p的位置已经穷尽了
                cur_result[p] = 0;
                p--;
            } else if (cal_val_res == BREAK) {
                break;
            } else {
                // 正常求出来的值
                cur_result[p] = cal_val_res;
                p++;
            }
        }

        return return_vec;
    }
};

int main(int argc, char* argv[]) {
    Solution a;
    int k = 3;
    int n = 7;
    auto res = a.combinationSum3(3, 7);
    for (auto i : res) {
        for (auto j : i) {
            cout << j << endl;
        }
    }
    // a.letterCombinations("23");
    return 0;
}
