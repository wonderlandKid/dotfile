#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <queue>
#include <set>
#include <stdexcept>
#include <vector>
using namespace std;

class Solution {
    using myPair = pair<int, int>;

   public:
    void debugprint(string const& str, vector<pair<int, int>> const& new_costs) {
        cout << str << "   ";
        for (auto const& i : new_costs) {
            cout << '{' << i.first << ',' << i.second << '}' << ' ';
        }
        cout << '\n';
    }

    template <typename Comp>
    void debugprint(string const& str, priority_queue<myPair, vector<myPair>, Comp> const& que) {
        cout << str << "   ";
        auto que_copy = que;
        // 拷贝一份que
        while (!que_copy.empty()) {
            cout << que_copy.top().first << ',' << que_copy.top().second << ' ';
            que_copy.pop();
        }
        cout << '\n';
    }

    long long totalCost(vector<int>& costs, int k, int candidates) {
        // 先改造costs这个数组 让他变成带下标的costs
        // 调用系统的接口 建立自定义类的堆
        // 第一个放下标 第二个放cost
        vector<myPair> new_costs;
        new_costs.reserve(costs.size());
        for (int i = 0; i < costs.size(); i++) {
            new_costs.push_back(myPair{i, costs[i]});
        }

        // debugprint("new_consts", new_costs);

        int left = candidates - 1;
        int right = costs.size() - candidates;

        // 先初始化这个堆
        // 如果特化greater就是最小堆
        auto cmp = [](myPair const& a1, myPair const& a2) {
            // 注意这里和sort相反 返回true的时候a2排在前面
            if (a2.second < a1.second) return true;
            if (a2.second == a1.second && a2.first < a1.first) return true;

            return false;
        };
        priority_queue<myPair, vector<myPair>, decltype(cmp)> que(cmp);

        // 现在这个priority_queue应该是越往上cost越小了

        // 现在先做初始化
        // 0-left right-new_costs.size()-1的数字都拿进来
        if (left >= right)
            // 直接整个接入数组
            for (auto const& i : new_costs) que.push(i);
        else {
            for (int i = 0; i < left + 1; i++) que.push(new_costs[i]);
            for (int i = right; i < new_costs.size(); i++) que.push(new_costs[i]);
        }

        // debugprint("优先队列", que);

        // 现在开始计算最小代价
        long long min_cost = 0;
        for (size_t i = 1; i <= k; i++) {
            // 这里是循环k次来取得k个最小的
            if (que.empty()) return min_cost;

            auto cur_top = que.top();
            que.pop();
            min_cost += cur_top.second;

            // 现在开始移动left和right
            if (left >= right - 1)
                // 这种情况就是不需要移动了
                continue;

            if (cur_top.first >= 0 && cur_top.first <= left) {
                left++;
                que.push(myPair{left, costs[left]});
            } else {
                right--;
                que.push(myPair{right, costs[right]});
            }
        }
        return min_cost;
    }
};

int main(int argc, char* argv[]) {
    vector<int> test1 = {17, 12, 10, 2, 7, 2, 11, 20, 8};
    vector<int> test2 = {1, 2, 4, 1};
    int k = 3;
    int candidates = 4;
    Solution a;
    cout << a.totalCost(test2, k, candidates);
    return 0;
}
