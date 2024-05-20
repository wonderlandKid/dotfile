#include <queue>
#include <vector>
using namespace std;

class Solution {
   public:
    struct aPoint {
        aPoint(int _x, int _y) {
            x = _x;
            y = _y;
        }
        int x;
        int y;

        bool operator==(aPoint const& other) const {
            if (other.x == x && other.y == y) return true;
            return false;
        }
    };
    const int YESSS = 1;
    const int NOOO = -1;

    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        // 创建一个对应maze的数组 表示有没有被访问过, 确保不走回头路
        auto start_point = aPoint{entrance[0], entrance[1]};
        queue<aPoint> que;
        que.push(start_point);
        que.push({-1, -1});
        // -1 -1表示该换层了

        auto foot_count = 0;
        while (!que.empty()) {
            auto que_top = que.front();
            que.pop();

            if (que_top == aPoint{-1, -1}) return -1;

            if (is_the_end(start_point, que_top, maze) == YESSS) return foot_count;
            maze[que_top.x][que_top.y] = '+';

            auto up = aPoint{que_top.x - 1, que_top.y};
            auto down = aPoint{que_top.x + 1, que_top.y};
            auto left = aPoint{que_top.x, que_top.y - 1};
            auto right = aPoint{que_top.x, que_top.y + 1};

            if (is_valid(maze, up) == YESSS) {
                maze[up.x][up.y] = '+';
                que.push(up);
            }
            if (is_valid(maze, down) == YESSS) {
                maze[down.x][down.y] = '+';
                que.push(down);
            }
            if (is_valid(maze, left) == YESSS) {
                maze[left.x][left.y] = '+';
                que.push(left);
            }
            if (is_valid(maze, right) == YESSS) {
                maze[right.x][right.y] = '+';
                que.push(right);
            }

            if (que.front() == aPoint{-1, -1}) {
                // 该换层了
                foot_count++;
                que.pop();
                que.push({-1, -1});
            }
        }
        return -1;
    }

    int is_valid(vector<vector<char>>& maze, aPoint const& cur_p) {
        // 返回这个点位是不是可以走 包括判断回头路
        // 1 合法 -1 不能走
        if (cur_p.x < 0 || cur_p.y < 0 || cur_p.x >= maze.size() || cur_p.y >= maze[0].size()) return NOOO;

        if (maze[cur_p.x][cur_p.y] == '+') return NOOO;

        // 既不越界 又没有障碍 又没有重复
        return YESSS;
    }

    int is_the_end(aPoint const& start_point, aPoint const& judge_point, vector<vector<char>> const& maze) {
        // 返回某一个点是不是出口
        if (judge_point.x == start_point.x && judge_point.y == start_point.y) return NOOO;

        if (judge_point.x == 0 || judge_point.y == 0 || judge_point.x == maze.size() - 1 || judge_point.y == maze[0].size() - 1)
            return YESSS;

        return NOOO;
    }
};

int main(int argc, char* argv[]) {
    vector<int> entry1{42, 4};
    Solution a;
    // cout << a.nearestExit(case1, entry1);
}
