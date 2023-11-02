#include <iostream>
#include <vector>
using namespace std;
class Solution {
   public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        int len = gas.size();
        int residue, j, cnt;
        for (int i = 0; i < len; i++) {
            residue = 0;
            for (j = i, cnt = 0; cnt < 5; cnt++) {
                residue = residue + gas[j] - cost[j];
                if (residue >= 0) {
                    j = (j + 1) % 5;
                } else {
                    break;
                }
            }
            if (cnt == 5) {
                return i;
            }
        }
        return -1;
    }
};

int main() {
    vector<int> a{2, 3, 4};
    vector<int> b{3, 4, 3};
    Solution test;
    cout << test.canCompleteCircuit(a, b);
}
