#include <iostream>
#include <numeric>
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
    queue<TreeNode*> que{};
    vector<int> nodevec{};
    vector<int> rightSideView(TreeNode* root) {
        // 遍历每层求最右侧结点
        if (root == nullptr) return {};
        que.push(root);
        // nullptr是换层标记
        que.push(nullptr);
        while (!que.empty()) {
            TreeNode* que_out = que.front();
            if(que_out == nullptr) break;
            que.pop();
            if (que_out->left != nullptr) que.push(que_out->left);
            if (que_out->right != nullptr) que.push(que_out->right);
            if (que.front() == nullptr) {
                // 表示上面那个弹出的是最后一个元素
                nodevec.push_back(que_out->val);
                que.pop();
                que.push(nullptr);
            }
        }
        return nodevec;
    }
};

int main(int argc, char* argv[]) {
    auto a = new TreeNode(1);
    auto b = new TreeNode(2);
    auto c = new TreeNode(3);
    auto d = new TreeNode(4);
    auto e = new TreeNode(5);
    a->left = b;
    a->right = c;
    b->right = e;
    c->right = d;
    Solution test;
    auto result = test.rightSideView(a);
    return 0;
}
