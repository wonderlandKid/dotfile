#include <bits/stdc++.h>

#include <cstddef>
#include <limits>
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
    int pathSum(TreeNode *root, int targetSum) { return some_tree_nums(root, targetSum); }

    int some_node_nums(TreeNode *root, int targetSum) {
        // 返回以root为起点, 和为targetSum的路径的条数
        if (root == nullptr) return 0;

        if (root->left == nullptr && root->right == nullptr) {
            if (root->val == targetSum) return 1;
            return 0;
        } else if (root->left == nullptr && root->right != nullptr) {
            auto returnsum = 0;
            if (root->val == targetSum) returnsum += 1;
            if ((root->val >= 0 && targetSum >= numeric_limits<int>::min() + root->val) ||
                (root->val < 0 && targetSum <= numeric_limits<int>::max() + root->val))
                returnsum += some_node_nums(root->right, targetSum - root->val);

            return returnsum;
        } else if (root->left != nullptr && root->right == nullptr) {
            auto returnsum = 0;
            if (root->val == targetSum) returnsum += 1;
            if ((root->val >= 0 && targetSum >= numeric_limits<int>::min() + root->val) ||
                (root->val < 0 && targetSum <= numeric_limits<int>::max() + root->val))
                returnsum += some_node_nums(root->left, targetSum - root->val);
            return returnsum;
        } else {
            // not nullptr
            auto returnsum = 0;
            if (root->val == targetSum) returnsum += 1;
            if ((root->val >= 0 && targetSum >= numeric_limits<int>::min() + root->val) ||
                (root->val < 0 && targetSum <= numeric_limits<int>::max() + root->val)) {
                returnsum += some_node_nums(root->left, targetSum - root->val);
                returnsum += some_node_nums(root->right, targetSum - root->val);
            }
            return returnsum;
        }
    }

    int some_tree_nums(TreeNode *root, int targetSum) {
        // 返回以root为根的树的包含的路径条数
        if (root == nullptr) return 0;
        auto returnsum = 0;
        returnsum += some_node_nums(root, targetSum);
        returnsum += some_tree_nums(root->left, targetSum);
        returnsum += some_tree_nums(root->right, targetSum);

        return returnsum;
    }
};

int main(int argc, char *argv[]) {
    // 生成一个这样的单链的TreeNode来测试
    // 生成一个TreeNode节点root 它代表一个单链[1,null,2,null,3,null,4,null,5]
    auto root = new TreeNode(0, new TreeNode(1), new TreeNode(1));

    cout << Solution().pathSum(root, 1) << endl;
    return 0;
}
