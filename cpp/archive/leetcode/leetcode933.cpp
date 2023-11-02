#include <bits/stdc++.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

#include "backward.hpp"
using namespace std;
class RecentCounter {
   public:
    RecentCounter() : q(), count(0) {}

    int ping(int t) {
        q.push_back(t);
        int begin = t - 3000;
        int end = t;
        int return_val = 0;
        while (q.front() < begin) {
            q.pop_front();
        }
        return q.size();
    }

    deque<int> q{};
    int count{};
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
int main(int argc, char* argv[]) {
    RecentCounter a;
    cout << a.ping(1) << endl;
    cout << a.ping(100) << endl;
    cout << a.ping(3001) << endl;
    cout << a.ping(3002) << endl;
    return 0;
}
