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

// 仍然是leetcode872 试图优化
class Solution {
   public:
    bool leafSimilar(TreeNode *root1, TreeNode *root2) {
        vector<int> seq1{};
        vector<int> seq2{};
        cal_sequence(root1, seq1);
        cal_sequence(root2, seq2);
        return seq1 == seq2;
    }

    void cal_sequence(TreeNode *const &root, vector<int> &seq) {
        if (root == nullptr) return;
        if (root->left == nullptr && root->right == nullptr)
            seq.push_back(root->val);
        cal_sequence(root->left, seq);
        cal_sequence(root->right, seq);
        return;
    }
};
