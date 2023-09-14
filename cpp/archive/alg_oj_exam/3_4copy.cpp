#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

int number[100]{0};

int haveresult = 0;

int quecount = 0;

int can_cal_it_count = 0;

struct TreeNode {
    // 现在这个节点的集合包含哪些数字
    vector<int> curset{};
};

queue<TreeNode*> que;

void f(TreeNode* root, int n) {
    // 生成节点来加入队列
    if (root->curset.size() == n) return;

    auto& curset = root->curset;
    vector<int> notused;
    for (int i = 1; i <= n; i++) {
        auto result = find(curset.begin(), curset.end(), i);
        if (result == curset.end()) notused.push_back(i);
    }

    // 对于每一个不在里面的节点都新建一个节点
    // 限界不了一点
    for (int i = 0; i <= notused.size() - 1; i++) {
        auto tmp = new TreeNode(*root);
        tmp->curset.push_back(notused[i]);
        quecount++;
        que.push(tmp);
    }
    return;
}

string can_cal_it(int down_index, vector<int>& target, float m) {
    can_cal_it_count++;
    // 从下标0到下标down_index的运行结果能否等于m
    // 这里down_index不能为0
    if (down_index == 1) {
        // 递归出口
        if (target[0] + target[1] == m) return to_string(target[0]) + "+" + to_string(target[1]);
        if (target[0] - target[1] == m) return to_string(target[0]) + "-" + to_string(target[1]);
        if (target[0] * target[1] == m) return to_string(target[0]) + "*" + to_string(target[1]);
        if (target[0] / target[1] == m) return to_string(target[0]) + "/" + to_string(target[1]);
        return "";
    }

    string plusresult = can_cal_it(down_index - 1, target, m - target[down_index]);
    if (plusresult != "") return plusresult + "+" + to_string(target[down_index]);

    string minusresult = can_cal_it(down_index - 1, target, m + target[down_index]);
    if (minusresult != "") return minusresult + "-" + to_string(target[down_index]);

    string mulityresult = can_cal_it(down_index - 1, target, m / target[down_index]);
    if (mulityresult != "") return mulityresult + "*" + to_string(target[down_index]);

    string divideresult = can_cal_it(down_index - 1, target, m * target[down_index]);
    if (divideresult != "") return divideresult + "/" + to_string(target[down_index]);

    return "";
}

void whole_function(TreeNode* root, int n, float m) {
    while (que.empty() != true) {
        auto tmp = que.front();
        que.pop();
        if (tmp->curset.size() == 1) {
            if (tmp->curset[0] == m) {
                cout << to_string(m) << endl;
                return;
            }
        } else if (tmp->curset.size() != 0) {
            // 下面检查这个节点能否运算出结果
            vector<int> target;
            for (auto i : tmp->curset) target.push_back(number[i]);
            string result = can_cal_it(target.size() - 1, target, m);
            if (result != "") {
                int count = 0;
                for (auto const& i : result) {
                    if (i == '+' || i == '-' || i == '*' || i == '/') count++;
                }
                cout << count << endl;
                cout << result << endl;
                haveresult = 1;
                return;
            }
        } else
            ;
        f(tmp, n);
    }
}

int main() {
    // n个数字 运算的结果是m
    // freopen("in.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> number[i];

    // 初始节点入队
    TreeNode* root = new TreeNode;
    que.push(root);
    whole_function(root, n, m);
    if (haveresult == 0) cout << -1;
    cout<<endl<<quecount<<endl;
    cout<<endl<<can_cal_it_count<<endl;
    return 0;
}
