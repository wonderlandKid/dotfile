#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

struct myTreeNode {
    myTreeNode(int _val) {
        val = _val;
        father_node = nullptr;
    }
    int val;
    myTreeNode* father_node;

    static myTreeNode* cal_father_node(myTreeNode* root) {
        // 返回root结点的father结点 同时进行路径压缩
        if (root->father_node == root) return root;

        auto father_node_fanode = cal_father_node(root->father_node);
        root->father_node = father_node_fanode;
        return root->father_node;
    }
};

class Solution {
   public:
    struct way {
        way(int _end, int _direction) {
            end = _end;
            direction = _direction;
        }
        int end{0};        // 这条路径的目的地
        int direction{0};  // 1正向 -1反向
    };

    int change_times{0};
    const int FORWARD = 1;
    const int BACKWARD = -1;

    int minReorder(int n, vector<vector<int>>& connections) {
        // 使用dfs 关键是深度优先遍历什么图
        // 新建一个路线vector
        auto ways = vector<vector<way>>(n, vector<way>());
        for (auto& i : connections) {
            ways[i[0]].push_back(way{i[1], FORWARD});
            ways[i[1]].push_back(way{i[0], BACKWARD});
        }

        // 路线已经搞好了现在开始dfs
        vector<int> has_visited(n, 0);
        has_visited[0] = 1;

        dfs(ways, 0, has_visited);
        return change_times;
    }

    void dfs(vector<vector<way>> const& ways, int cur, vector<int>& has_visited) {
        // cur表示现在遍历到哪个节点了 has_visited 表示是不是所有的已经遍历完了
        for (auto& i : ways[cur]) {
            // 保证每一条路径都是反的
            // 先确定终点是不是已经走过了
            if (has_visited[i.end] == 1) continue;

            // 此处是没有走过
            has_visited[i.end] = 1;
            if (i.direction == FORWARD) {
                change_times++;
            }

            dfs(ways, i.end, has_visited);
        }
    }
};

int main(int argc, char* argv[]) {
    // vector<vector<int>> test1{{1, 0}, {1}, {0, 1, 1, 1}, {1, 0, 1, 1}};
    vector<vector<int>> case1{{1, 0}, {1, 2}, {3, 2}, {3, 4}};
    Solution test;
    cout << test.minReorder(5, case1);
    Solution a;
}
