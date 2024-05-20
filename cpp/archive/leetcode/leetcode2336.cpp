#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

class SmallestInfiniteSet {
    // 太难绷了 直接用set偷懒算了
   public:
    set<int> my_set;
    SmallestInfiniteSet() {
        for (int i = 1; i <= 1000; i++) my_set.insert(i);
    }

    int popSmallest() {
        int first = *my_set.begin();
        my_set.erase(first);
        return first;
    }

    void addBack(int num) { my_set.insert(num); }
};

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */
int main(int argc, char* argv[]) {
    vector<vector<int>> case1{{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    // Solution a;
    // cout << a.orangesRotting(case1);
}
