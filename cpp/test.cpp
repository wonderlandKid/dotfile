#include <bits/stdc++.h>

#include <iostream>
#include <memory>
using namespace std;

class StockSpanner {
   public:
    StockSpanner() {}

    int next(int price) {
        if (stk.empty()) {
            stk.push_back(price);
            return 1 + count;
        }

        int cur_back = stk.back();
        if (cur_back > price) {
            stk.push_back(price);
            return 1;
        } else {
            count = 0;
            while (!stk.empty() && stk.back() < price) {
                stk.pop_back();
                count++;
            }
            stk.push_back(price);
            return 1 + count;
        }
    }

    vector<int> stk{};

    // 用来测试弹出的个数
    int count{0};
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */

int main(int argc, char* argv[]) {
    StockSpanner* obj = new StockSpanner();
    cout << obj->next(29);
    cout << obj->next(91);
    cout << obj->next(62);
    cout << obj->next(76);
    cout << obj->next(51);

    // cout << obj->next(75);
    // cout << obj->next(85);

    // Solution a;
    // auto res = a.dailyTemperatures(test1);
    return 0;
}
