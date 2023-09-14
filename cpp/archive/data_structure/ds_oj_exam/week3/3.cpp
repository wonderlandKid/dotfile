#include <cstdio>
using namespace std;

class Node {
  // 二叉树结点
public:
  Node() {
    val = 0;
    left = nullptr;
    right = nullptr;
  }
  Node(int _val) {
    val = _val;
    left = nullptr;
    right = nullptr;
  }
  int val;
  Node *left;
  Node *right;
};

class queuenode {
  // 队列结点
public:
  queuenode() {
    left = nullptr;
    right = nullptr;
    valptr = nullptr;
  }
  queuenode(Node *_valptr) {
    left = nullptr;
    right = nullptr;
    valptr = _valptr;
  }
  queuenode *left;
  queuenode *right;
  Node *valptr;
};

class queue {
public:
  queue() {
    begin = end = nullptr;
    size = 0;
  }
  queuenode *begin;
  queuenode *end;
  int size;
  void push(Node *_valptr) {
    size++;
    auto tmp = new queuenode(_valptr);
    if (end == nullptr) {
      begin = end = tmp;
    } else if (begin == end) {
      end->right = tmp;
      tmp->left = end;
      end = tmp;
    } else {
      end->right = tmp;
      tmp->left = end;
      end = tmp;
    }
  }

  void pop() {
    if (begin == nullptr)
      ;
    else if (begin == end) {
        end = begin = nullptr;
        size--;
      } else {
        auto copy = begin->right;
        copy->left = nullptr;
        begin = copy;
        size--;
      }
  }

  queuenode *front() { return begin; }
};

Node *BuildTree(void) {
  int x = 0;
  scanf("%d", &x);
  if (x == 0)
    return nullptr;

  auto root = new Node(x);

  root->left = BuildTree();
  root->right = BuildTree();

  return root;
}

int main(void) {
  //freopen("in.txt", "r", stdin);
  auto root = BuildTree();

  queue que;
  que.push(nullptr);
  que.push(root);
  int m, n;
  int flag = 0;
  scanf("%d%d", &m, &n);
  int whatline = 0; // 为0反向遍历 为1正向遍历
  while (que.size != 0) {
    auto tmp = que.front();
    que.pop();
    if (tmp->valptr == nullptr) {
      if (whatline == 0) {
        // 反遍历
        for (auto i = que.end; i != nullptr; i = i->left) {
          if (i->valptr->val == m)
            flag = 1;
          if (flag)
            printf("%d ", i->valptr->val);
          if (i->valptr->val == n)
            return 0;
        }
      } else {
        // 正遍历
        for (auto i = que.begin; i != nullptr; i = i->right) {
          if (i->valptr->val == m)
            flag = 1;
          if (flag)
            printf("%d ", i->valptr->val);
          if (i->valptr->val == n)
            return 0;
        }
      }
      if (whatline == 0)
        whatline = 1;
      else
        whatline = 0;
      que.push(nullptr);
    } else {
      if (tmp->valptr->left != nullptr)
        que.push(tmp->valptr->left);
      if (tmp->valptr->right != nullptr)
        que.push(tmp->valptr->right);
    }
  }

  return 0;
}
