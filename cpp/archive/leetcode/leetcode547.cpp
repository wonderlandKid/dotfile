#include <climits>
#include <iostream>
#include <queue>
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
    int findCircleNum(vector<vector<int>>& isConnected) {
        // 这个得写并查集
        // 城市的编号是从0号开始
        int city_num = isConnected.size();
        vector<myTreeNode*> city_array(city_num, nullptr);
        for (int i = 0; i < city_num; i++) {
            city_array[i] = new myTreeNode(i);
            city_array[i]->father_node = city_array[i];
        }

        // 现在开始读取矩阵内容
        // 只是需要遍历这个二维数组的半边
        for (int x = 0; x < city_num; x++) {
            for (int y = 0; y < city_num; y++) {
                if (!(y - x > 0)) continue;
                if (isConnected[x][y] == 1) {
                    auto x_father = myTreeNode::cal_father_node(city_array[x]);
                    auto y_father = myTreeNode::cal_father_node(city_array[y]);
                    y_father->father_node = x_father;
                }
            }
        }

        // 进行路径压缩
        for (int i = 0; i < city_num; i++) {
            if (city_array[i]->father_node != nullptr)
                city_array[i]->father_node = myTreeNode::cal_father_node(city_array[i]->father_node);
        }
        // 最后计数
        unordered_set<myTreeNode*> count_set{};
        int finalresult = 0;
        for (int i = 0; i < city_num; i++) {
            count_set.insert(city_array[i]->father_node);
        }

        return count_set.size();
    }
};

int main(int argc, char* argv[]) {
    vector<vector<int>> test1{{1,0,0,1},{0,1,1,0},{0,1,1,1},{1,0,1,1}};
    Solution a;
    cout << a.findCircleNum(test1);
}
