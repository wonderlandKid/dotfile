#include <bits/stdc++.h>

#include <algorithm>
#include <cstddef>

using namespace std;
/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
   public:
    int maxlen;

    int longestZigZag(TreeNode *root) {
        maxlen = 0;
        dfs(root, 0, 1);
        dfs(root, 0, -1);
        return maxlen;
    }

    void dfs(TreeNode *root, int curlen, int direction) {
        // curlen为1走左 为-1走右
        // 左右都要有
        if (root == nullptr) return;
        maxlen = max(maxlen, curlen);
        if (direction > 0) {
            // 接下来走左
            dfs(root->left, curlen + 1, -1);
            dfs(root->right, 1, 1);
        } else {
            // 接下来走右
            dfs(root->right, curlen + 1, 1);
            dfs(root->left, 1, -1);
        }
        return;
    }
};

int main(int argc, char *argv[]) {
    auto p1 = new TreeNode(1, nullptr, nullptr);
    auto p2 = new TreeNode(1, nullptr, nullptr);
    auto p3 = new TreeNode(1, nullptr, nullptr);
    auto p4 = new TreeNode(1, nullptr, nullptr);
    auto p5 = new TreeNode(1, nullptr, nullptr);
    auto p6 = new TreeNode(1, nullptr, nullptr);
    auto p7 = new TreeNode(1, nullptr, nullptr);

    p5->right = p7;
    p4->right = p6;
    p4->left = p5;
    p2->right = p4;
    p1->left = p2;
    p1->right = p3;

    Solution a;
    cout << a.longestZigZag(p1) << endl;
    return 0;
}
