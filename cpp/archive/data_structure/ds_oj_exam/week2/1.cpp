#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
using namespace std;
//+ 43
//- 45
//* 42
// / 47
// ^ 94
class Mystack {
public:
  Mystack() {
    for (int i = 0; i <= 999; i++)
      array[i] = 0;
    size = 0;
    p = 0;
  }
  int array[1000];
  int p;
  int size;
  void pop() {
    if (p == 0)
      ;
    else {
      p--;
      size--;
    }
  }

  void push(int _x) {
    if (p == 1000)
      ;
    else {
      array[p] = _x;
      size++;
      p++;
    }
  }

  int top() {
    if (p == 0)
      return -1;
    else
      return array[p - 1];
  }

  void clear() {
    p = 0;
    size = 0;
  }
};

int mypow(int x, int y) {
  // 计算x^y 其中x和y都是正整数
  if (y == 0)
    return 0;
  if (y == 1)
    return x;
  if (y % 2 == 0) {
    int tmp = mypow(x, y / 2);
    return tmp * tmp;
  } else {
    int tmp = mypow(x, (y - 1) / 2);
    return tmp * tmp * x;
  }
}

int priority(int a, int b) {
  // a b是两个操作符的ascii码 如果a的优先级比b高 则返回正数 反之返回负数
  // 优先级相等返回零
  //  char tmp='+'; //43
  //  char tmp2='-'; //45
  //  char tmp3='*'; //42
  //  char tmp4='/'; //47
  //  char tmp5='^'; //94
  if (a == 43)
    a = a + 2;
  if (a == 42)
    a = a + 5;
  if (a == '(')
    a = 1;
  if (b == 43)
    b = b + 2;
  if (b == 42)
    b = b + 5;
  if (b == '(')
    b = 1;
  if (a == b && a == 94)
    return 1;
  return a - b;
}

int calculate(Mystack *pstack_num, Mystack *pstack_symbol) {
  // 运算正常返回0 不正常返回-1
  int num1 = pstack_num->top();
  pstack_num->pop();
  int num2 = pstack_num->top();
  pstack_num->pop();

  int op = pstack_symbol->top();
  pstack_symbol->pop();

  if (op == '+')
    pstack_num->push(num2 + num1);
  else if (op == '-')
    pstack_num->push(num2 - num1);
  else if (op == '*')
    pstack_num->push(num2 * num1);
  else if (op == '^')
    pstack_num->push(mypow(num2, num1));
  else if (op == '/') {
    if (num1 == 0)
      return -1;
    else
      pstack_num->push(num2 / num1);
  }
  return 0;
}

int main(void) {
  Mystack stack_num, stack_symbol;
  char expression[1010] = {0};
  int i = 0;
  int abs = 0;
  int haveabs = -1; // 如果abs已经被压栈了 就别重复压了
  while (scanf("%s", expression) != -1) {
    stack_num.clear();
    stack_symbol.clear();
    i = 0;
    while (1) {
      char tmp = expression[i];
      i++;
      if (tmp == '\0') {
        if (haveabs != -1) {
          stack_num.push(abs);
          abs = 0;
          haveabs = -1;
        }
        int flag = 0;
        while (stack_symbol.size != 0) {
          int p1 = calculate(&stack_num, &stack_symbol);
          if (p1 == -1)
            flag = -1;
        }
        if (flag == -1)
          printf("INVALID\n");
        else
          printf("%d\n", stack_num.top());
        break;
      }

      else if (tmp >= '0' && tmp <= '9') {
        abs = abs * 10 + tmp - 48;
        haveabs = 1;
      }

      else if (tmp == '+' || tmp == '-' || tmp == '*' || tmp == '/' ||
               tmp == '^') {
        int flag = 0;
        if (haveabs != -1) {
          stack_num.push(abs);
          abs = 0;
          haveabs = -1;
        }
        while (1) {
          if (priority(tmp, stack_symbol.top()) > 0) {
            stack_symbol.push(tmp);
            break;
          } else {
            int tmp = calculate(&stack_num, &stack_symbol);
            if (tmp == -1) {
              printf("INVALID\n");
              flag = -1;
              break;
            }
          }
        }
        if (flag == -1)
          break;
      }

      else if (tmp == '(')
        stack_symbol.push('(');

      else if (tmp == ')') {
        if (haveabs != -1) {
          stack_num.push(abs);
          abs = 0;
          haveabs = -1;
        }
        int flag = 0; // 用来查除数是否发生异常
        int tmp = 0;
        while (1) {
          tmp = stack_symbol.top();
          if (tmp == '(') {
            stack_symbol.pop();
            break;
          } else {
            int p1 = calculate(&stack_num, &stack_symbol);
            if (p1 == -1) {
              flag = 1;
              break;
            }
          }
        }
        if (flag == 1)
          break;
      }
    }
  }
  return 0;
}