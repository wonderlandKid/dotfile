#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
using namespace std;

class cell {
public:
  cell(void) {
    before = nullptr;
    next = nullptr;
  }
  cell(char a) {
    before = nullptr;
    next = nullptr;
    ch = a;
  }
  char ch;
  cell *before;
  cell *next;
};

int main(void) {
  cell *end, *cursor;
  auto beforehead = new cell(0); // 哨兵结点
  end = beforehead;
  char chartmp = '0';
  cursor = beforehead; // 对cursor后面进行插入操作
  while ((chartmp = getchar()) != -1) {

    if (chartmp == '{')
      cursor = beforehead;

    else if (chartmp == '}')
      cursor = end;

    else if (chartmp == '#') {
      // 链表是空就别删除了
      if (cursor == beforehead)
        ;
      else {
        auto cursorcopy = cursor;
        cursor = cursor->before;
        if (cursorcopy->next == nullptr) {
          cursor->next = nullptr;
          delete cursorcopy;
        } else {
          cursor->next = cursorcopy->next;
          cursor->next->before = cursor;
          delete cursorcopy;
        }
      }
    }

    else if (chartmp == '<') {
      if (cursor == beforehead)
        ;
      else
        cursor = cursor->before;
    }

    else if (chartmp == '>') {
      if (cursor == end)
        ;
      else
        cursor = cursor->next;
    }

    else if (chartmp == '\n')
      ;
    else {
      // 分两种情况是因为如果光标不是在字符串末尾那么输入完字符还需要连接上后面的链表
      if (cursor->next == nullptr) {
        auto celltmp = new cell(chartmp);
        cursor->next = celltmp;
        celltmp->before = cursor;
        end = celltmp;
        cursor = cursor->next;
      } else {
        auto cursor_next = cursor->next;
        auto celltmp = new cell(chartmp);
        cursor->next = celltmp;
        celltmp->before = cursor;
        celltmp->next = cursor_next;
        cursor_next->before = celltmp;
        cursor = cursor->next;
      }
    }
  }

  // 打印环节
  if (beforehead->next == nullptr)
    ;
  else {
    auto p1 = beforehead->next;
    while (p1 != nullptr) {
      printf("%c", p1->ch);
      p1 = p1->next;
    }
  }
  return 0;
}
