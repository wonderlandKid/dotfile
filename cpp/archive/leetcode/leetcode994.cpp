#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Solution {
   public:
    struct aPoint {
        int x;
        int y;

        bool operator==(aPoint const& other) const { return (x == other.x && y == other.y); }
    };

    const int YES = 1;
    const int NO = -1;
    int orangesRotting(vector<vector<int>>& grid) {
        // 本身是一个简单的广度有限搜索问题 关键在于如何判断是不是所有橘子都被感染了 什么时候判断
        // 判断所有橘子都被感染了这个时间复杂度肯定是所有的橘子 应该是如果这一轮没有橘子被感染 则尝试看看是不是都感染了
        queue<aPoint> que;
        // 找到所有腐烂的橘子
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 2) que.push({i, j});
            }
        }
        que.push({-1, -1});
        auto turn_number = 0;
        auto rot_this_turn = 0;

        while (!que.empty()) {
            auto que_top = que.front();
            que.pop();

            if (que_top == aPoint{-1, -1}) break;

            auto up = aPoint{que_top.x - 1, que_top.y};
            auto down = aPoint{que_top.x + 1, que_top.y};
            auto left = aPoint{que_top.x, que_top.y - 1};
            auto right = aPoint{que_top.x, que_top.y + 1};

            if (is_valid(grid, up) == YES) {
                grid[up.x][up.y] = 2;
                que.push(up);
                rot_this_turn = 1;
            }
            if (is_valid(grid, down) == YES) {
                grid[down.x][down.y] = 2;
                que.push(down);
                rot_this_turn = 1;
            }
            if (is_valid(grid, left) == YES) {
                grid[left.x][left.y] = 2;
                que.push(left);
                rot_this_turn = 1;
            }
            if (is_valid(grid, right) == YES) {
                grid[right.x][right.y] = 2;
                que.push(right);
                rot_this_turn = 1;
            }

            if (que.front() == aPoint{-1, -1}) {
                // 表示进到下一层了
                if (rot_this_turn == 0) break;
                turn_number++;
                rot_this_turn = 0;
                que.pop();
                que.push({-1, -1});
            }
        }

        // 现在检测是不是还有没有腐烂的
        for (auto const& i : grid) {
            for (auto const& j : i) {
                if (j == 1) return -1;
            }
        }
        return turn_number;
    }

    int is_valid(vector<vector<int>>& grid, aPoint const& cur) {
        if (cur.x < 0 || cur.y < 0 || cur.x >= grid.size() || cur.y >= grid[0].size()) return NO;
        if (grid[cur.x][cur.y] == 0 || grid[cur.x][cur.y] == 2) return NO;

        // cur既不是越界 而且是新鲜橘子 不是烂橘子或者没有橘子
        return YES;
    }
};

int main(int argc, char* argv[]) {
    vector<vector<int>> case1{{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    Solution a;
    cout << a.orangesRotting(case1);
}
