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
        vector<TreeNode*> p_path{};
        vector<TreeNode*> q_path{};
        return_path_to_root(p, root, p_path);
        return_path_to_root(q, root, q_path);

        // loop
        auto it1 = p_path.begin();
        auto it2 = q_path.begin();
        while (it1 != p_path.end() && it2 != q_path.end()) {
            if (*it1 == *it2)
                it1++, it2++;
            else
                break;
        }
        it1--;
        return *it1;
    }

    int return_path_to_root(TreeNode* findnode, TreeNode* root, vector<TreeNode*>& cur_path) {
        if (root->val == findnode->val) {
            cur_path.push_back(root);
            // 找到了
            return 1;
        }

        cur_path.push_back(root);
        if (root->left != nullptr) {
            int tmp = return_path_to_root(findnode, root->left, cur_path);
            if (tmp == 1) return 1;
        }

        if (root->right != nullptr) {
            int tmp = return_path_to_root(findnode, root->right, cur_path);
            if (tmp == 1) return 1;
        }

        cur_path.pop_back();
        return 0;
    }
};
