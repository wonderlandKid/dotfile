#include <climits>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TreeNode {
public:
  TreeNode() {
    left = right = nullptr;
    val = -1;
    fre = 0;
    myfather = nullptr;
  }
  TreeNode(int _val) {
    left = right = nullptr;
    val = _val;
    fre = 0;
    myfather = nullptr;
  }

  TreeNode *left;
  TreeNode *right;
  int val; // ascii码值
  int fre; // 出现频次
  TreeNode *myfather;
};

class BinaryList {
public:
  BinaryList() {
    ptr = nullptr;
    before = nullptr;
    after = nullptr;
  }
  BinaryList *before;
  BinaryList *after;
  TreeNode *ptr;
};

// void printtree(TreeNode *root) {
//   if (root == nullptr)
//     return;
//   printf("%d ", root->val);

//   printtree(root->left);
//   printtree(root->right);
// }

int main(void) {
  string str;
  cin >> str;
  const int strlen = str.length();
  TreeNode *indexarray[26] = {0};
  for (int i = 0; i <= 25; i++) {
    indexarray[i] = new TreeNode('a' + i);
  }
  int order[26] = {0};
  int mark = 1; // 和order数组配套用
  for (int i = 0; i <= strlen - 1; i++) {
    indexarray[str[i] - 'a']->fre++;
    if (order[str[i] - 'a'] == 0) {
      order[str[i] - 'a'] = mark;
      mark++;
    }
  }

  // for (int i = 0; i <= 25; i++) {
  //   printf("%c出现%d次\n", indexarray[i]->val, indexarray[i]->fre);
  //   printf("order值是%d", order[i]);
  //   printf("\n\n");
  // }

  // 排序 fre越往右越大 order越大越靠右
  for (int i = 1; i <= 25; i++) {
    // for (int p = 0; p <= 25; p++) {
    //   printf("%c", indexarray[p]->val);
    // }
    // printf("\n");
    int p = i;
    while (1) {
      if (p == 0)
        break;
      if (indexarray[p]->fre < indexarray[p - 1]->fre ||
          (indexarray[p]->fre == indexarray[p - 1]->fre &&
           order[indexarray[p]->val - 'a'] <
               order[indexarray[p - 1]->val - 'a'])) {
        auto tmp = indexarray[p - 1];
        indexarray[p - 1] = indexarray[p];
        indexarray[p] = tmp;
        p--;
      } else
        break;
    }
  }

  // printf("排序后:\n");
  // for (int i = 0; i <= 25; i++) {
  //   printf("%c出现%d次\n", indexarray[i]->val, indexarray[i]->fre);
  //   printf("order值是%d", order[indexarray[i]->val - 'a']);
  //   printf("\n\n");
  // }

  // 取得从第几位开始不是0
  int start = 0;
  while (1) {
    if (indexarray[start]->fre != 0)
      break;
    start++;
  }

  auto begin = new BinaryList();
  begin->ptr = new TreeNode('w');
  begin->ptr->fre = -1;

  auto end = new BinaryList();
  end->ptr = new TreeNode('w');
  end->ptr->fre = INT_MAX;

  begin->after = end;
  end->before = begin;

  for (int i = start; i <= 25; i++) {
    auto tmp = new BinaryList();
    tmp->ptr = indexarray[i];
    auto endbefore = end->before;
    tmp->after = end;
    end->before = tmp;
    tmp->before = endbefore;
    endbefore->after = tmp;
  }

  // // 检验函数
  // for (auto i = begin->after; i != end; i = i->after) {
  //   printf("%c的出现次数是%d\n", i->ptr->val, i->ptr->fre);
  // }

  while (begin->after->after != end) {
    auto tmp = new BinaryList();
    tmp->ptr = new TreeNode();
    tmp->ptr->fre = begin->after->ptr->fre + begin->after->after->ptr->fre;
    begin->after->ptr->myfather = tmp->ptr;
    begin->after->after->ptr->myfather = tmp->ptr;
    tmp->ptr->left = begin->after->ptr;
    tmp->ptr->right = begin->after->after->ptr;
    begin = begin->after->after;
    // 剩下的结点里面找一个比它的fre要大的
    auto tmmmp = begin->after;
    while (1) {
      if (tmmmp->ptr->fre > tmp->ptr->fre)
        break;
      tmmmp = tmmmp->after;
    }
    auto tmmmpbefore = tmmmp->before;
    tmp->after = tmmmp;
    tmp->before = tmmmp->before;
    tmmmpbefore->after = tmp;
    tmmmp->before = tmp;
  }

  auto root = begin->after->ptr;
  // printtree(begin->after->ptr);

  printf("%d ", strlen);
  int all_depth = 0;
  for (int i = start; i <= 25; i++) {
    int divite_depth = 0;
    auto tmp = indexarray[i];
    while (tmp->myfather != nullptr) {
      divite_depth++;
      tmp = tmp->myfather;
    }
    all_depth += divite_depth * indexarray[i]->fre;
  }
  if (all_depth % 8 == 0)
    printf("%d\n", all_depth / 8);
  else
    printf("%d\n", all_depth / 8 + 1);

  for (int i = start; i <= 25; i++) {
    printf("%c:", indexarray[i]->val);
    auto tmp = indexarray[i];
    string strtmp;
    while (tmp->myfather != nullptr) {
      auto tmpfather = tmp->myfather;
      if (tmp == tmpfather->left)
        strtmp.append("0");
      if (tmp == tmpfather->right)
        strtmp.append("1");
      tmp = tmpfather;
    }
    const int strtmplen = strtmp.size();
    for (int i = strtmplen - 1; i >= 0; i--) {
      printf("%c", strtmp[i]);
    }
    printf("\n");
  }

  string code1;
  string code2;
  vector<char> result;
  cin >> code1 >> code2;

  const int code1size = code1.size();
  const int code2size = code2.size();
  auto tmptmp = root;
  for (int i = 0; i <= code1size - 1; i++) {
    if (code1[i] == '0') {
      tmptmp = tmptmp->left;
    } else {
      tmptmp = tmptmp->right;
    }
    if(tmptmp->right==nullptr) {
      char wow=tmptmp->val;
      result.push_back(wow);
      tmptmp=root;
    }
  }

  if (tmptmp != root)
    printf("INVALID\n");
  else {
    for(auto be=result.begin(); be<result.end(); be++)
      printf("%c", *be);
    printf("\n");
  }

  tmptmp = root;
  result.clear();
  for (int i = 0; i <= code2size - 1; i++) {
    if (code2[i] == '0') {
      tmptmp = tmptmp->left;
    } else {
      tmptmp = tmptmp->right;
    }
    if(tmptmp->right==nullptr) {
      char wow=tmptmp->val;
      result.push_back(wow);
      tmptmp=root;
    }
  }

  if (tmptmp != root)
    printf("INVALID\n");
  else {
    for(auto be=result.begin(); be<result.end(); be++)
      printf("%c", *be);
    printf("\n");
  }
 
  return 0;
}
