#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 第三题C版本代码
typedef struct Tree {
    char str[17];
    struct Tree *index[17];
    // int distance_to_root;
    int freq;
} Tree;

typedef struct myresult {
    Tree *result;
    int status;
} myresult;

int min(int a, int b) {
    if (a < b) return a;
    return b;
}
int max(int a, int b) {
    if (a > b) return a;
    return b;
}

int buffer[20][20];

int get_distance_loop(char *word1, int i, char *word2, int j) {
    // 求word1的前i项和word2的前j项的编辑距离
    // buffer需要的空间是0~i和0~j
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
int get_edit_distance(char *a, char *b) {
    if (strlen(a) * strlen(b) == 0) return strlen(a) + strlen(b);
    // a为行 b为列
    // buffer.assign(a.size() + 1, vector<int>(b.size() + 1, -1));
    int alen = strlen(a);
    int blen = strlen(b);
    if (alen < blen) {
        return get_distance_loop(a, alen, b, blen);
    } else {
        return get_distance_loop(b, blen, a, alen);
    }
}
// function
void printalltree(Tree *root) {
    // 先根
    if (root == NULL) return;
    printf("%s\n", root->str);
    // printf("%d\n%d\n", root->distance_to_root, root->freq);
    for (int i = 1; i <= 16; i++) printalltree(root->index[i]);
    return;
}

void Treeinsert(Tree *root, Tree *target) {
    // 手动保证root不是空
    // 把新建的target节点插入到root为根节点的树里面
    if (root == NULL) printf("ERROR");

    int distance = get_edit_distance(root->str, target->str);
    if (distance == 0) return;

    if (root->index[distance] == NULL) {
        root->index[distance] = target;
        return;
    } else {
        Treeinsert(root->index[distance], target);
        return;
    }
}

void check(char *target, int d, Tree *root, myresult *myresult) {
    // 求字符串target在这个字典中最满足条件的 结果存储在result
    if (root == NULL) return;
    if (myresult->status == 1) {
        // 此时已经匹配到一个了
        return;
    }

    // 此时没有找到一个元素和target完全一致

    int distance = get_edit_distance(target, root->str);

    if (distance == 0) {
        myresult->result = root;
        myresult->status = 1;
        return;
    }

    if (distance > d) {
        // 继续递归地在子树找
        for (int i = max(1, distance - d); i <= min(15, distance + d); i++) {
            if (root->index[i] == NULL) {
            } else {
                check(target, d, root->index[i], myresult);
            }
        }
    } else {
        // 现在没有找到完美符合的 但是当前节点root满足
        if (myresult->result == NULL)
            myresult->result = root;
        else {
            // 比较取优
            if (myresult->result->freq > root->freq)
                ;
            else if (myresult->result->freq == root->freq) {
                // 按照字典序
                if (myresult->result->str < root->str)
                    ;
                else
                    myresult->result = root;
            } else {
                myresult->result = root;
            }
        }
        // 然后还是在递归寻找
        for (int i = max(1, distance - d); i <= min(15, distance + d); i++) {
            if (myresult->status == 1) return;
            if (root->index[i] == NULL)
                ;
            else
                check(target, d, root->index[i], myresult);
        }
    }
    return;
}

int main() {
    for (int tmp = 0; tmp <= 17; tmp++) buffer[tmp][0] = tmp;
    for (int tmp = 0; tmp <= 17; tmp++) buffer[0][tmp] = tmp;
    // freopen("in.txt", "r", stdin);
    Tree *root = NULL;
    int m, n, d;
    // m个单词 n此查询操作 距离不超过d
    scanf("%d%d%d", &m, &n, &d);
    // int outtmp1;
    // char outtmp2[20];
    // scanf("%d%s", &outtmp1, outtmp2);
    root = (Tree *)malloc(sizeof(Tree));
    // root->distance_to_root = 0;
    for (int i = 0; i <= 16; i++) root->index[i] = NULL;
    scanf("%d%s", &root->freq, root->str);
    // 给一个大于15位的值
    for (int i = 2; i <= m; i++) {
        Tree *newnode = (Tree *)malloc(sizeof(Tree));
        scanf("%d%s", &newnode->freq, newnode->str);
        Treeinsert(root, newnode);
    }

    // printalltree(root);

    for (int i = 1; i <= n; i++) {
        char tmp2[20] = {'0'};
        scanf("%s", tmp2);
        myresult result;
        result.result = NULL;
        result.status = 0;
        check(tmp2, d, root, &result);
        if (result.result == NULL)
            printf("No similar word in dictionary\n");
        else
            printf("%s\n", result.result->str);
    }
    return 0;
}
