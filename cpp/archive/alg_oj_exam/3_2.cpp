#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int number[210]{};

int havesolution = 0;

void print_vint(const vector<int>& target) {
    for (auto i : target) cout << i << ' ';
    cout << endl;
}

struct TreeNode {
    TreeNode* myfather{nullptr};

    // 里面存的都是number数组的下标
    vector<int> curresult{};

    // 当前的循环从start的下一个开始
    int start{0};

    // 这是当前的数字和
    int cursum{0};
};

queue<TreeNode*> que;

void f(TreeNode* root, int M, int n) {
    // 理论上不会出现这一支
    if (root->start == n) return;
    TreeNode* tmp{nullptr};
    for (int i = root->start + 1; i <= n; i++) {
        tmp = new TreeNode();
        tmp->myfather = root;
        tmp->curresult = root->curresult;
        tmp->curresult.push_back(i);
        tmp->start = i;
        tmp->cursum = root->cursum + number[i];
        if (tmp->cursum == M) {
            print_vint(tmp->curresult);
            havesolution = 1;
        }

        else if (tmp->cursum > M) {
            // nothing
        } else {
            que.push(tmp);
        }
    }
}

TreeNode* find_live_node() {
    if (que.empty() == true)
        return nullptr;
    else {
        auto tmp = que.front();
        que.pop();
        return tmp;
    }
}

void whole_function(int M, int n) {
    TreeNode* root{nullptr};
    while ((root = find_live_node()) != nullptr) {
        // 现在root不为空指针 开始从这个节点开始生成
        f(root, M, n);
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    int n, M;
    cin >> n >> M;

    // 下标从1开始
    for (int i = 1; i <= n; i++) cin >> number[i];
    TreeNode* root = new TreeNode();
    que.push(root);
    whole_function(M, n);
    if (havesolution == 0) cout << "no solution!" << endl;
    return 0;
}
