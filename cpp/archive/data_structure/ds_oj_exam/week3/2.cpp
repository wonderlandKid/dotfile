#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

class Node {
  // 二叉树结点
public:
  Node() {
    left = right = father = nullptr;
    val = 0;
  }
  Node(int _val) {
    left = right = father = nullptr;
    val = _val;
  }
  Node *left;
  Node *right;
  int val;
  Node *father;
};

Node *buildtree() {
  // 先根 带父节点信息的队列
  int val;
  scanf("%d", &val);
  if (val == 0)
    return nullptr;

  auto root = new Node(val);

  root->left = buildtree();
  if (root->left != nullptr)
    root->left->father = root;

  root->right = buildtree();
  if (root->right != nullptr)
    root->right->father = root;

  return root;
}

Node *find_the_node(int target, Node *root) {
  if (root == nullptr)
    return nullptr;
  if (root->val == target)
    return root;

  auto left_result = find_the_node(target, root->left);
  auto right_result = find_the_node(target, root->right);

  if (left_result == nullptr)
    return right_result;

  return left_result;
}

int main(void) {
  #ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin);
  #endif
  auto root = buildtree();
  int times;
  scanf("%d", &times);
  for (int p1 = 1; p1 <= times; p1++) {
    int m, n;
    scanf("%d%d", &m, &n); // 找到从值为m的点到值为n的点的路径并输出
    Node *mptr = nullptr, *nptr = nullptr;
    mptr = find_the_node(m, root);
    nptr = find_the_node(n, root);
    vector<Node *> marray;
    vector<Node *> narray;

    // 先对m n求完整的路径
    Node *tmp_m = mptr;
    while (tmp_m != nullptr) {
      marray.push_back(tmp_m);
      tmp_m = tmp_m->father;
    }

    Node *tmp_n = nptr;
    while (tmp_n != nullptr) {
      narray.push_back(tmp_n);
      tmp_n = tmp_n->father;
    }

    if (marray.size() >= narray.size()) {
      // n数组下标从0开始
      int marray_downmark = marray.size() - narray.size();
      int narray_downmark = 0;
      while (1) {
        if (marray[marray_downmark] == narray[narray_downmark])
          break;
        ++marray_downmark;
        ++narray_downmark;
      }
      printf("%d\n", marray_downmark + narray_downmark);
      for (int i = 0; i <= marray_downmark; i++)
        printf("%d ", marray[i]->val);
      for (int i = narray_downmark - 1; i >= 0; i--)
        printf("%d ", narray[i]->val);

      printf("\n");
    } else {
      // m下标从0开始
      int narray_downmark = narray.size() - marray.size();
      int marray_downmark = 0;
      while (1) {
        if (marray[marray_downmark] == narray[narray_downmark])
          break;
        ++marray_downmark;
        ++narray_downmark;
      }
      printf("%d\n", marray_downmark + narray_downmark);
      for (int i = 0; i <= marray_downmark; i++)
        printf("%d ", marray[i]->val);
      for (int i = narray_downmark - 1; i >= 0; i--)
        printf("%d ", narray[i]->val);

      printf("\n");
    }
  }
  return 0;
}