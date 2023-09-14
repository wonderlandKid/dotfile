#include <iostream>
#include <vector>
using namespace std;
int main() {
  int n;
  cin >> n;
  vector<int> array;
  array.reserve(n);
  for (int i = 1; i <= n; i++) {
    int tmp;
    cin >> tmp;
    array.push_back(tmp);
  }
  int yesterday = array[0];
  int maxincome = 0;
  for (auto i : array) {
    if (i > yesterday) {
      maxincome += i - yesterday;
      yesterday = i;
    }
      yesterday = i;
  }
  cout << maxincome;
  return 0;
}
