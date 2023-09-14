#include <cstdio>
#include <string>
using namespace std;
//[i, j]表示a的前i个字母和b的前j个字母之间的编辑距离
// vector<vector<int>> buffer;

struct Tree;

struct myresult {
    Tree *result{nullptr};
    int status{0};
};

int buffer[20][20]{};
int get_distance_loop(string &word1, int i, string &word2, int j) {
    // 求word1的前i项和word2的前j项的编辑距离
    // buffer需要的空间是0~i和0~j
    for (int tmp = 0; tmp <= i; tmp++) buffer[tmp][0] = tmp;
    for (int tmp = 0; tmp <= j; tmp++) buffer[0][tmp] = tmp;
    for (int p1 = 1; p1 <= i; p1++) {
        for (int p2 = 1; p2 <= j; p2++) {
            // 现在计算buffer[p1][p2]
            int left = buffer[p1][p2 - 1];
            int down = buffer[p1 - 1][p2];
            int left_down = buffer[p1 - 1][p2 - 1];
            if (word1[p1 - 1] == word2[p2 - 1]) {
                buffer[p1][p2] = min(min(left + 1, down + 1), left_down);
            } else {
                buffer[p1][p2] = min(min(left + 1, down + 1), left_down + 1);
            }
        }
    }
    return buffer[i][j];
}

// 计算编辑距离
int get_edit_distance(string a, string b) {
    if (a.size() * b.size() == 0) return a.size() + b.size();
    // a为行 b为列
    // buffer.assign(a.size() + 1, vector<int>(b.size() + 1, -1));
    if (a.size() < b.size()) {
        return get_distance_loop(a, a.size(), b, b.size());
    } else {
        return get_distance_loop(b, b.size(), a, a.size());
    }
}

struct Tree {
    Tree(string _str) : str(_str) {}
    Tree(string _str, int _distance_to_root, int _freq)
        : str(_str), distance_to_root(_distance_to_root), freq(_freq) {}
    Tree(string _str, int _freq) : str(_str), freq(_freq) {}
    string str{};
    Tree *index[17]{nullptr};
    int distance_to_root{0};
    int freq{0};
};

// function
void printalltree(Tree *root) {
    // 先根
    if (root == nullptr) return;
    printf("%s\n", root->str.c_str());
    printf("%d\n%d\n", root->distance_to_root, root->freq);
    for (int i = 1; i <= 16; i++) printalltree(root->index[i]);
    return;
}

void Treeinsert(string &_str, Tree *&root, int _freq) {
    // 插入一个节点 这个节点的字符串是_str 插入到根节点为root的树里面
    // freq是_freq
    if (root == nullptr) root = new Tree(_str, _freq);

    // root不为空
    int distance = get_edit_distance(root->str, _str);
    if (distance == 0) return;

    if (root->index[distance] == nullptr) {
        root->index[distance] = new Tree(_str, distance, _freq);
    } else {
        Treeinsert(_str, root->index[distance], _freq);
    }
}

void check(string &target, int d, Tree *&root, myresult &result) {
    // 求字符串target在这个字典中最满足条件的 结果存储在result
    if (root == nullptr) return;
    if (result.status == 1) {
        // 此时已经匹配到一个了
        return;
    }

    // 此时没有找到一个元素和target完全一致

    int distance = get_edit_distance(target, root->str);

    if (distance == 0) {
        result.result = root;
        result.status = 1;
        return;
    }

    if (distance > d) {
        // 继续递归地在子树找
        for (int i = max(1, distance - d); i <= min(15, distance + d); i++) {
            if (root->index[i] == nullptr) {
            } else {
                check(target, d, root->index[i], result);
            }
        }
    } else {
        // 现在没有找到完美符合的 但是当前节点root满足
        if (result.result == nullptr)
            result.result = root;
        else {
            // 比较取优
            if (result.result->freq > root->freq)
                ;
            else if (result.result->freq == root->freq) {
                // 按照字典序
                if (result.result->str < root->str)
                    ;
                else
                    result.result = root;
            } else {
                result.result = root;
            }
        }
        // 然后还是在递归寻找
        for (int i = max(1, distance - d); i <= min(15, distance + d); i++) {
            if (root->index[i] == nullptr)
                ;
            else
                check(target, d, root->index[i], result);
        }
    }
    return;
}

int main() {
    // freopen("in.txt", "r", stdin);
    Tree *root = nullptr;
    int m, n, d;
    // m个单词 n此查询操作 距离不超过d
    scanf("%d%d%d", &m, &n, &d);

    for (int i = 1; i <= m; i++) {
        int tmp1;
        char tmp2[20]{};
        scanf("%d%s", &tmp1, tmp2);
        string tmp3(tmp2);
        Treeinsert(tmp3, root, tmp1);
    }

    // printalltree(root);

    for (int i = 1; i <= n; i++) {
        char tmp2[20]{};
        scanf("%s", tmp2);
        string tmp3(tmp2);
        myresult result{};
        check(tmp3, d, root, result);
        if (result.result == nullptr)
            printf("No similar word in dictionary\n");
        else
            printf("%s\n", result.result->str.c_str());
    }
    return 0;
}
