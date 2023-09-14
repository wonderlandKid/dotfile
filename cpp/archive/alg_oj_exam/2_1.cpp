// 最优二分检索树问题
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

struct Tree {
    int number{-1};
    Tree* left{nullptr};
    Tree* right{nullptr};
};

void create_tree(Tree*& root, vector<vector<float>>& R, int left, int right) {
    int tmp = R[left][right];
    if (tmp == -1) {
        root = nullptr;
        return;
    }
    root = new Tree{tmp, nullptr, nullptr};
    create_tree(root->left, R, left, tmp - 1);
    create_tree(root->right, R, tmp, right);
}

void pre_root_iter(Tree* root) {
    if (root == nullptr) return;
    cout << root->number << ' ';
    pre_root_iter(root->left);
    pre_root_iter(root->right);
}

int main() {
    // freopen("in.txt", "r", stdin);
    float n;
    cin >> n;
    vector<float> p(n + 2, 0);  // 下标从1开始用
    vector<float> q(n + 2, 0);
    for (int i = 1; i <= n; i++) cin >> p[i];
    for (int i = 0; i <= n; i++) cin >> q[i];
    vector<vector<float>> C(n + 2, vector<float>(n + 2, 10000));
    vector<vector<float>> R(n + 2, vector<float>(n + 2, -1));
    vector<vector<float>> W(n + 2, vector<float>(n + 2, 0));
    for (int i = 0; i <= n; i++) C[i][i] = 0;
    for (int i = 1; i <= n; i++) R[i - 1][i] = i;
    for (int i = 0; i <= n; i++) R[i][i] = -1;
    for (int k = 1; k <= n; k++) {
        int i = 0;
        int j = i + k;
        while (j <= n) {
            // 求这里的W
            W[i][j] += q[i];
            for (int tmp = i+1; tmp <= j; tmp++) {
                W[i][j] += q[tmp];
                W[i][j] += p[tmp];
            }
            for (int root = i + 1; root <= j; root++) {
                float newC = W[i][j] + C[i][root - 1] + C[root][j];
                if (newC < C[i][j]) {
                    C[i][j] = newC;
                    R[i][j] = root;
                }
            }
            i++;
            j++;
        }
    }
    // 接下来递归建立树
    Tree* root = nullptr;
    create_tree(root, R, 0, n);
    pre_root_iter(root);
    return 0;
}
