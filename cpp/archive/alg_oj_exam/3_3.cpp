#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct gem {
    // 这两个的值都是从1~n
    int colorx{-1};
    int shapey{-1};
};

struct TreeNode {
    TreeNode(int n) { curgrid.assign(n + 1, vector<gem>(n + 1, gem())); }
    vector<vector<gem>> curgrid{};

    vector<vector<int>> isused{};
    int x{1};
    int y{0};
    TreeNode* myfather{nullptr};
};

// FILO
vector<TreeNode*> stk;

int finalresult = 0;

void f(TreeNode* root, int n) {
    // 现在开始计算这个节点的子节点
    int newx = root->x;
    int newy = root->y + 1;
    if (newy > n) {
        newy = 1;
        newx++;
    }
    if (newx > n) {
        finalresult++;
        return;
    }

    // curgrid[newx][newy]
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (root->isused[i][j] == 0) {
                auto tmp = gem{i, j};
                // check this tmp can be put in curgrid[newx][newy]
                int breakflag = 0;
                for (int k = 1; k <= newy; k++) {
                    if (root->curgrid[newx][k].colorx == tmp.colorx || root->curgrid[newx][k].shapey == tmp.shapey) {
                        breakflag = 1;
                        break;
                    }
                }

                if (breakflag == 1) continue;

                breakflag = 0;
                for (int k = 1; k <= newx; k++) {
                    if (root->curgrid[k][newy].colorx == tmp.colorx || root->curgrid[k][newy].shapey == tmp.shapey) {
                        breakflag = 1;
                        break;
                    }
                }

                if (breakflag == 1) continue;

                TreeNode* newnode = new TreeNode(*root);
                newnode->curgrid[newx][newy] = tmp;
                newnode->isused[tmp.colorx][tmp.shapey] = 1;
                newnode->x = newx;
                newnode->y = newy;
                newnode->myfather = root;
                stk.push_back(newnode);
            }
        }
    }
}

TreeNode* find_node() {
    if (stk.empty() == true)
        return nullptr;
    else {
        auto tmp = stk.back();
        stk.pop_back();
        return tmp;
    }
}

void whole_function(int n) {
    TreeNode* root = nullptr;
    while ((root = find_node()) != nullptr) {
        f(root, n);
        delete root;
    }
}

int main() {
    // 最终的顺序还是按照行优先 行完了再列
    int n;
    cin >> n;
    TreeNode* root = new TreeNode(n);
    root->curgrid.assign(n + 1, vector<gem>(n + 1, gem()));
    root->isused.assign(n + 1, vector<int>(n + 1, 0));
    stk.push_back(root);
    whole_function(n);
    cout<<finalresult<<endl;
    return 0;
}
