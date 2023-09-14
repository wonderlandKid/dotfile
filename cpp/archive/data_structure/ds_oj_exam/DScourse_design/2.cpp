// BST
#include <iostream>
#include <string>
using namespace std;

struct TreeNode {
    TreeNode(int _val) : val(_val) { left = right = nullptr; }
    int val;
    TreeNode* left;
    TreeNode* right;

    // Insert and delete method
    static void treeinsert(TreeNode*& root, int _val) {
        if (root == nullptr) {
            root = new TreeNode(_val);
            return;
        }

        if (root->val == _val) return;

        if (root->val > _val)
            treeinsert(root->left, _val);
        else
            treeinsert(root->right, _val);

        return;
    }

    static void treedelete(TreeNode*& root, int _val) {
        if (root == nullptr) return;

        if (root->val > _val)
            treedelete(root->left, _val);
        else if (root->val < _val)
            treedelete(root->right, _val);
        else {
            if (root->left == nullptr && root->right == nullptr)
                root = nullptr;
            else if ((root->left == nullptr && root->right != nullptr) ||
                     (root->left != nullptr && root->right == nullptr)) {
                if (root->left != nullptr)
                    root = root->left;
                else
                    root = root->right;
            } else {
                auto tmp1 = root->right;
                if (tmp1->left == nullptr) {
                    root->val = tmp1->val;
                    root->right = tmp1->right;
                    // delete tmp1;
                } else {
                    auto tmp2 = tmp1->left;
                    while (tmp2->left != nullptr) {
                        tmp1 = tmp1->left;
                        tmp2 = tmp2->left;
                    }
                    root->val = tmp2->val;
                    TreeNode::treedelete(tmp1->left, tmp2->val);
                }
            }
        }
    }

    static void print_preorder(TreeNode* root) {
        if (root == nullptr) return;
        printf("%d ", root->val);
        print_preorder(root->left);
        print_preorder(root->right);
        return;
    }

    static void print_midorder(TreeNode* root) {
        if (root == nullptr) return;
        print_midorder(root->left);
        printf("%d ", root->val);
        print_midorder(root->right);
        return;
    }
};

int main() {
    int t = 0;
    cin >> t;
    TreeNode* root = nullptr;
    for (int i = 1; i <= t; i++) {
        int val;
        string tmp = "2222222";
        cin >> tmp;
        cin >> val;
        if (tmp == "Insert") {
            TreeNode::treeinsert(root, val);
        } else if (tmp == "Remove") {
            TreeNode::treedelete(root, val);
        } else {
            cout << "ERROR!" << endl;
        }
    }

    TreeNode::print_midorder(root);
    cout << endl << endl;
    TreeNode::print_preorder(root);
    cout << endl;
    return 0;
}
