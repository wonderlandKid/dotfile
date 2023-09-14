#include <climits>
#include <cmath>
#include <cstdio>
using namespace std;

class Solution {
 public:
  long int myabs(long int a) {
    if (a < 0) return -a;
    return a;
  }
  int divide(int a, int b) {
    if (a == b) return 1;
    if (a == INT_MIN && myabs(b) < 1) return INT_MAX;  // 绝对值溢 abs(INT_MIN)
    if (a == INT_MIN && b == 1) return INT_MIN;
    if (a == INT_MIN && b == -1) return INT_MAX;
    long int return_result = 0;
    // a/b
    long int remain = myabs(a);
    long int result = 1;
    long int abs_b = myabs(b);
    long int copyb = myabs(b);
    while (remain >= copyb) {
      while (remain - abs_b > abs_b) {
        abs_b += abs_b;
        result += result;
      }
      remain = remain - abs_b;
      return_result += result;
      abs_b = copyb;
      result = 1;
    }
    if ((a < 0 && b < 0) || (a > 0 && b > 0)) return return_result;
    return -return_result;
  }
};

int main() {
  Solution a;
  printf("%d\n", a.divide(-2147483648, -2147483648));
  return 0;
}
