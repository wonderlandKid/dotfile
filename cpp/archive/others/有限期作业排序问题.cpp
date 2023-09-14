#include <algorithm>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

class Tree {
 public:
  Tree(int _val, int _mynumber) : val(_val), mynumber(_mynumber){};
  static Tree* whos_father(Tree* root) {
    // 寻找给定结点的父亲 如果已经是最上侧的结点就返回自己
    if (root->myfather == nullptr) return root;

    root->myfather = whos_father(root->myfather);
    return root->myfather;
  }
  Tree* myfather{nullptr};
  int val{-1};  // 存当前结点被几号活动占用
  int mynumber;
};

int main() {
  int n;
  cout << "输入一个n表示数据规模,然后输入n行 收益 活动号 截止日期" << endl;
  cin >> n;  // 给定数据规模
  vector<tuple<int, int, int>> array;
  array.reserve(n);
  for (int i = 1; i <= n; i++) {
    int p, number, d;  // 分别是收益, 对应的号, 对应的截止日期 编号0 1 2
    cin >> p >> number >> d;
    array.push_back({p, number, d});
  }

  // 升序排列
  sort(array.begin(), array.end(), greater<tuple<int, int, int>>());

  // 升序排列后的array
  // for (auto i : array) {
  //   auto [p1, p2, p3] = i;
  //   cout << "收益,号,日期: " << p1 << " " << p2 << " " << p3 << endl;
  // }
  //
  // 遍历看一下截止日期哪个最大
  int maxd = 0;
  for (auto i : array) {
    auto result = get<2>(i);
    if (result > maxd) maxd = result;
  }

  // 并查集初始化 用maxd和n的较小值+1来初始化set
  vector<Tree*> set(
      [](int a, int b) -> int {
        if (a >= b) return b;
        return a;
      }(maxd, n) + 1,
      nullptr);

  // 注意从0开始到n
  for (int i = 0; i <= n; i++) {
    set[i] = new Tree(-1, i);
  }

  for (auto i : array) {
    auto [p, activity, deadline] = i;
    auto target = Tree::whos_father(set[min(deadline, n)]);
    if (target->mynumber != 0) {
      target->val = activity;
      target->myfather = Tree::whos_father(set[target->mynumber - 1]);
    }
  }

  for (auto i : set) {
    if (i->val != -1) {
      cout << i->mynumber << "时间片被" << i->val << "占用" << endl;
    }
  }

  return 0;
}
