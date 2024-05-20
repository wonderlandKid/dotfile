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
    queue<TreeNode*> que{};

    int maxLevelSum(TreeNode* root) {
        int result_sum = INT_MIN;
        int result_level = 0;

        int tmp_sum = 0;
        int tmp_level = 0;

        que.push(root);
        que.push(nullptr);
        while (!que.empty()) {
            auto que_top = que.front();
            que.pop();
            
            // 最后一层退出
            if (que_top == nullptr) break;

            tmp_sum += que_top->val;

            if (que_top->left != nullptr) que.push(que_top->left);
            if (que_top->right != nullptr) que.push(que_top->right);

            if (que.front() == nullptr) {
                // 计算完了一整层的
                que.pop();
                que.push(nullptr);
                tmp_level++;

                // 开始判断是不是要更新
                if (tmp_sum > result_sum) {
                    result_level = tmp_level;
                    result_sum = tmp_sum;
                }

                // 准备计算下一层
                tmp_sum = 0;
            }
        }
        return result_level;
    }
};
int main(int argc, char* argv[]) {
    auto a = new TreeNode(1);
    auto b = new TreeNode(7);
    auto c = new TreeNode(0);
    auto d = new TreeNode(7);
    auto e = new TreeNode(-8);
    a->left = b;
    a->right = c;
    b->left = d;
    b->right = e;
    Solution test;
    auto result = test.maxLevelSum(a);
    cout << result;
    return 0;
}
