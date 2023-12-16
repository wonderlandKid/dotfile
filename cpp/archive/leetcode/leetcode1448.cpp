#include <bits/stdc++.h>

#include <array>
#include <optional>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution {
   public:
    int goodNodes(TreeNode *root) { return dfs_cal_goodnodes(root, INT_MIN); }

    int dfs_cal_goodnodes(TreeNode *root, int curmaxval) {
        // 计算当前结点下的好结点个数
        // 其中curmaxval是当前已经经历过的路径的最大值
        if (root == nullptr) return 0;
        if (root->left == nullptr && root->right == nullptr)
            return int(curmaxval <= root->val);
        auto leftresult =
            dfs_cal_goodnodes(root->left, max(curmaxval, root->val));
        auto rightresult =
            dfs_cal_goodnodes(root->right, max(curmaxval, root->val));
        return leftresult + rightresult + int(curmaxval <= root->val);
    }
};

int main() {
    auto p1 = new TreeNode(3);
    auto p2 = new TreeNode(1);
    auto p3 = new TreeNode(4);
    auto p4 = new TreeNode(3);
    auto p5 = new TreeNode(1);
    auto p6 = new TreeNode(5);
    p1->left = p2;
    p1->right = p3;
    p2->left = p4;
    p3->left = p5;
    p3->right = p6;
    Solution a;
    cout << a.goodNodes(p1);
}
