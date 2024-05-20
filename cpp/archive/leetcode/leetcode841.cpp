#include <climits>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
   public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        unordered_set<int> solvedset{};
        solvedset.insert(0);
        vector<int> has_checked(rooms.size(), 0);
        queue<int> checking_list;
        checking_list.push(0);
        while (!checking_list.empty()) {
            int cur_checking_num = checking_list.front();
            checking_list.pop();

            if (has_checked[cur_checking_num] == 1) continue;

            has_checked[cur_checking_num] = 1;

            for (auto const& i : rooms[cur_checking_num]) {
                solvedset.insert(i);
                checking_list.push(i);
            }

            if (solvedset.size() == rooms.size()) return true;
        }

        return false;
    }
};

int main(int argc, char* argv[]) {}
