#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
using namespace std;

class Node {
 public:
  Node(int _x, int _y, int _len) {
    x = _x;
    y = _y;
    next = nullptr;
    len = _len;
  }
  int x;
  int y;
  int len;
  Node *next;
};

class Myqueue {
 public:
  Myqueue() { end = begin = nullptr; }
  Node *end;
  Node *begin;
  void queuein(int x, int y, int len) {
    auto tmp = new Node(x, y, len);
    if (end == nullptr) {
      end = begin = tmp;
    } else {
      end->next = tmp;
      end = end->next;
    }
  }

  Node *queueout() {
    if (end == begin) {
      auto tmp = end;
      end = begin = nullptr;
      return tmp;
    } else if (end == nullptr) {
      return nullptr;
    } else {
      auto copybegin = begin;
      begin = begin->next;
      return copybegin;
    }
  }

  void queueclear() { begin = end = nullptr; }
};

int find_the_length(int array[102][102], int length[102][102], int startx,
                    int starty, int n, int m) {
  Myqueue queue;
  queue.queuein(startx, starty, 0);
  length[startx][starty] = 0;
  while (queue.begin != nullptr) {
    auto temp = queue.queueout();

    if (temp->x - 1 <= 0 || array[temp->x - 1][temp->y] == 1 ||
        length[temp->x - 1][temp->y] != -1)
      ;
    else if (array[temp->x - 1][temp->y] == 4) {
      return (temp->len) + 1;
    } else {
      length[temp->x - 1][temp->y] = temp->len + 1;
      queue.queuein(temp->x - 1, temp->y, temp->len + 1);
    }

    if (temp->x + 1 > n || array[temp->x + 1][temp->y] == 1 ||
        length[temp->x + 1][temp->y] != -1)
      ;
    else if (array[temp->x + 1][temp->y] == 4) {
      return (temp->len) + 1;
    } else {
      length[temp->x + 1][temp->y] = temp->len + 1;
      queue.queuein(temp->x + 1, temp->y, temp->len + 1);
    }

    if (temp->y - 1 <= 0 || array[temp->x][temp->y - 1] == 1 ||
        length[temp->x][temp->y - 1] != -1)
      ;
    else if (array[temp->x][temp->y - 1] == 4) {
      return (temp->len) + 1;
    } else {
      length[temp->x][temp->y - 1] = temp->len + 1;
      queue.queuein(temp->x, temp->y - 1, temp->len + 1);
    }

    if (temp->y + 1 > m || array[temp->x][temp->y + 1] == 1 ||
        length[temp->x][temp->y + 1] != -1)
      ;
    else if (array[temp->x][temp->y + 1] == 4) {
      return (temp->len) + 1;
    } else {
      length[temp->x][temp->y + 1] = temp->len + 1;
      queue.queuein(temp->x, temp->y + 1, temp->len + 1);
    }
  }
  return -1;
}

int main(void) {
  int array[102][102] = {0};  // 保存输入
  int length[102][102];       // 标志已经走过了 避免重复路
  int n = 0, m = 0, startx = 0, starty = 0;
  int tmp = 0;
  while (scanf("%d%d", &n, &m) != -1) {
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) length[i][j] = -1;
    // 每次都要初始化
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
        scanf("%d", &tmp);
        array[i][j] = tmp;
        if (tmp == 3) {
          startx = i;
          starty = j;
        }
      }
    // input
    int result = find_the_length(array, length, startx, starty, n, m);
    if (result == -1)
      printf("unreachable\n");
    else
      printf("%d\n", result);
  }
  return 0;
}