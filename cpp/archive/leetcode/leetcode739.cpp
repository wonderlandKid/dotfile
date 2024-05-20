#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> return_vec(temperatures.size(), 0);
        // 单调栈
        struct myPair {
            int downindex;
            int temp;
        };
        vector<myPair> stk;
        for (int i = 0; i < temperatures.size(); i++) {
            // 要是栈为空 就直接压入
            if (stk.empty()) {
                stk.push_back({i, temperatures[i]});
                continue;
            }

            // 栈不为空
            auto cur_pair = myPair{i, temperatures[i]};
            auto stk_back = stk.back();
            if (stk_back.temp >= cur_pair.temp) {
                // 直接压入 维护一个一直减小的栈
                stk.push_back(cur_pair);
            } else {
                // 一直弹栈
                while (!stk.empty() && stk.back().temp < cur_pair.temp) {
                    auto tmp = stk.back();
                    stk.pop_back();
                    return_vec[tmp.downindex] = cur_pair.downindex - tmp.downindex;
                }

                stk.push_back(cur_pair);
            }
        }

        return return_vec;
    }
};

int main(int argc, char* argv[]) {
    vector<int> test1{73, 74, 75, 71, 69, 72, 76, 73};
    Solution a;
    auto res = a.dailyTemperatures(test1);
    return 0;
}
