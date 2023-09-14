#include <iostream>
using namespace std;
int number[210]{};
int havesolution = 0;
void copyarr(int srcarr[210], int targetarr[210]) {
    for (int i = 1; i <= 209; i++) targetarr[i] = srcarr[i];
}

struct TreeNode {
    TreeNode* myfather{nullptr};
    int arr[210]{0};
    // 左1右0
    TreeNode* left{nullptr};
    TreeNode* right{nullptr};
    // 为1则标记为死节点
    int isdead{0};
    // 最高到n
    int depth{0};
    // 这是当前的数字和
    int cursum{0};
};

void f(TreeNode* root, int M, int n) {
    // f函数是用来处理当前节点的 并且生成当前节点
    // 先判断当前节点是不是合法
    if (root->isdead == 1) return;
    if (root->depth == n) {
        if (root->cursum == M) {
            // 这个时候找到一组解
            for (int i = 1; i <= n; i++) cout << root->arr[i];
            cout << endl;
            havesolution = 1;
        }
    }

    if (root->depth == n) {
        // 不需要再有子节点了
    } else if (root->cursum > M) {
        // 也不需要生成了 因为一个节点的子节点至少比它自己要大
    } else {
        root->left = new TreeNode();
        root->left->myfather = root;
        copyarr(root->arr, root->left->arr);
        root->left->depth = root->depth + 1;
        root->left->arr[root->left->depth] = 1;
        root->left->cursum = number[root->left->depth] + root->cursum;

        root->right = new TreeNode();
        root->right->myfather = root;
        copyarr(root->arr, root->right->arr);
        root->right->depth = root->depth + 1;
        root->right->cursum = root->cursum;
    }
    root->isdead = 1;
    return;
}

TreeNode* find_live_node(TreeNode* root) {
    if (root->isdead == 0)
        return root;
    else {
        if (root->left != nullptr && root->left->isdead == 0) return root->left;
        if (root->right != nullptr && root->right->isdead == 0) return root->right;
        if (root->myfather == nullptr) return nullptr;

        // 运行到这里 现在情况是这个节点和左右节点都是死节点
        return find_live_node(root->myfather);
    }
}

void whole_function(TreeNode* root, int M, int n) {
    while ((root = find_live_node(root)) != nullptr) {
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
    whole_function(root, M, n);
    if (havesolution == 0) cout << "no solution!" << endl;
    return 0;
}
