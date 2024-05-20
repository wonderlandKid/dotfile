#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
   public:
    struct Edge {
        Edge(double _weight, string _end) : weight(_weight), end(_end){};
        double weight{};
        string end{};
    };

    // struct Node {
    //     Node(string _id) : id(_id){};
    //     string id{};
    //     vector<Edge> edges{};
    // };

    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // 这里不同节点采用string作为标识符 需要使用onordered_map
        unordered_map<string, vector<Edge>> un_map{};
        for (int i = 0; i < equations.size(); i++) {
            auto cur_equation = equations[i];
            auto cur_value = values[i];

            // 现在开始创建cur_equation[0] 和 cur_equation[1]这两个节点
            if (un_map.find(cur_equation[0]) == un_map.end())
                // 表示这里第一个节点没有被创建
                un_map.insert({cur_equation[0], vector<Edge>{}});

            if (un_map.find(cur_equation[1]) == un_map.end())
                // 表示第二个节点没有被创建
                un_map.insert({cur_equation[1], vector<Edge>{}});

            // 现在开始储存道路信息
            // 道路注意双向插入
            cout << un_map.size() << endl;

            auto node1 = un_map.find(cur_equation[0]);
            node1->second.push_back(Edge{cur_value, cur_equation[1]});

            auto node2 = un_map.find(cur_equation[1]);
            node2->second.push_back(Edge{1 / cur_value, cur_equation[0]});
        }

        unordered_set<string> has_visited{};
        vector<double> return_result_vec{};
        // 现在开始解决询问问题
        for (auto& i : queries) {
            has_visited.clear();
            auto tmp = return_cal_result(i[0], i[1], un_map, 1.0, has_visited);
            return_result_vec.push_back(tmp);
        }
        return return_result_vec;
    }

    double return_cal_result(string const& begin, string const& end, unordered_map<string, vector<Edge>>& un_map,
                             double sumresult, unordered_set<string>& has_visited) {
        // 返回从begin到end的值
        if (un_map.find(begin) != un_map.end() && begin == end) return 1.0;
        if (un_map.find(begin) == un_map.end()) return -1.0;

        has_visited.insert(begin);
        auto tmp = un_map.find(begin);
        auto edge_vec = tmp->second;

        for (auto& i : edge_vec) {
            // 现在是每一个边
            if (i.end == end) {
                sumresult *= i.weight;
                return sumresult;
            }

            // 假如说已经
            if (has_visited.find(i.end) != has_visited.end()) continue;

            // 现在是没有找到 就继续深度搜索
            auto the_rest_result = return_cal_result(i.end, end, un_map, 1.0, has_visited);
            if (the_rest_result != -1.0) return i.weight * the_rest_result;

            // 表示某个点没搜到 则尝试下一条边
            continue;
        }
        return -1.0;
    }
};

int main(int argc, char* argv[]) {
    vector<vector<string>> case1{{"x1", "x2"}, {"x2", "x3"}, {"x3", "x4"}, {"x4", "x5"}};
    vector<double> case1_value{3.0, 4.0, 5.0, 6.0};
    vector<vector<string>> case1_query{{"x1", "x5"}, {"x5", "x2"}, {"x2", "x4"}, {"x2", "x2"}, {"x2", "x9"}, {"x9", "x9"}};
    Solution test;
    test.calcEquation(case1, case1_value, case1_query);
    Solution a;
}
