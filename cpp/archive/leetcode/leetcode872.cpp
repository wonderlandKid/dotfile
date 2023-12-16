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
    bool leafSimilar(TreeNode *root1, TreeNode *root2) {
        return get_the_sequence(root1) == get_the_sequence(root2);
    }

    list<int> get_the_sequence(TreeNode *root) {
        if (root == nullptr) return {};
        if (root->left == nullptr && root->right == nullptr)
            return list<int>{root->val};

        auto leftlist = get_the_sequence(root->left);
        auto rightlist = get_the_sequence(root->right);
        leftlist.splice(leftlist.end(), rightlist);
        return leftlist;
    }
};
