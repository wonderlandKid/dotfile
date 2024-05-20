#include <iostream>
#include <vector>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
   public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 尝试用深度优先做
        // 通过这个TreeNode*的返回值来传递信息
        if (root == nullptr) return nullptr;
        if (root == p || root == q) return root;

        // 现在root不是p 不是q 不是空 那么就需要递归左右子树
        TreeNode* left_result = lowestCommonAncestor(root->left, p, q);
        TreeNode* right_result = lowestCommonAncestor(root->right, p, q);

        if (left_result != nullptr && right_result != nullptr) return root;

        if (left_result != nullptr) return left_result;

        return right_result;
    }
};
