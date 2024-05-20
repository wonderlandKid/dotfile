#include <climits>
#include <iostream>
#include <queue>
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
    TreeNode* not_found{nullptr};
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root == nullptr) return nullptr;
        auto& delete_node_ptr = find_node(root, key);
        if (delete_node_ptr == not_found) {
            return root;
        }
        _delete_tree_node(delete_node_ptr);
        return root;
    }

    void _delete_tree_node(TreeNode*& delete_node_ptr) {
        // 删除二叉搜索树的节点三种情况
        // 叶子节点: 直接删除
        // 只有一个子节点 直接代替
        // 有两个子节点 将当前值改为右子树的最小节点并且删除右子树的最小节点
        if (delete_node_ptr->left == nullptr && delete_node_ptr->right == nullptr)
            delete_node_ptr = nullptr;
        else if (delete_node_ptr->left == nullptr ^ delete_node_ptr->right == nullptr) {
            if (delete_node_ptr->left != nullptr) {
                delete_node_ptr->val = delete_node_ptr->left->val;
                auto delete_node_ptr_left = delete_node_ptr->left;
                delete_node_ptr->left = delete_node_ptr_left->left;
                delete_node_ptr->right = delete_node_ptr_left->right;
                delete delete_node_ptr_left;
            } else {
                // 右边不是空
                delete_node_ptr->val = delete_node_ptr->right->val;
                auto delete_node_ptr_right = delete_node_ptr->right;
                delete_node_ptr->left = delete_node_ptr_right->left;
                delete_node_ptr->right = delete_node_ptr_right->right;
                delete delete_node_ptr_right;
            }
        } else {
            // 两个都不是空 则找到右子树的最小节点的值并且把这个值拿到根 然后递归
            // 删除这个最小节点
            auto& righttree_min_node = find_righttree_min_node(delete_node_ptr->right);
            delete_node_ptr->val = righttree_min_node->val;
            _delete_tree_node(righttree_min_node);
        }
    }

    TreeNode*& find_node(TreeNode*& root, int key) {
        if (root == nullptr) return not_found;

        if (root->val == key) return root;

        if (root->left == nullptr && root->right == nullptr) {
            return not_found;
        } else if (root->left != nullptr && root->right == nullptr) {
            return find_node(root->left, key);
        } else if (root->left == nullptr && root->right != nullptr) {
            return find_node(root->right, key);
        } else {
            // 两个都不是空指针
            auto& left_result = find_node(root->left, key);

            // 能保证引用的有效性
            if (left_result != nullptr) return left_result;

            return find_node(root->right, key);
        }
    }

    TreeNode*& find_righttree_min_node(TreeNode*& root) {
        if (root->left == nullptr)
            return root;
        else {
            return find_righttree_min_node(root->left);
        }
    }
};

int main(int argc, char* argv[]) {
    auto a = new TreeNode(5);
    auto b = new TreeNode(3);
    auto c = new TreeNode(6);
    auto d = new TreeNode(2);
    auto e = new TreeNode(4);
    auto f = new TreeNode(7);
    a->left = b;
    a->right = c;
    b->left = d;
    b->right = e;
    c->right = f;
    Solution test;
    test.deleteNode(a, 3);
    return 0;
}
