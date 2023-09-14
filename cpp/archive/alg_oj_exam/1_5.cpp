
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
using namespace std;

// 并查集
class Tree {
public:
	Tree() = default;
	Tree(int _number) :number(_number) {};
	Tree* father{ nullptr };
	int number{ 0 }; //这个节点代表的是几号时间片.
	int val{ -1 }; //这个时间片放的活动的编号.
	static Tree* findroot(Tree* root) {
		if (root->father == nullptr) return root;
		//路径压缩
		root->father = findroot(root->father);
		return root->father;
	}
};

int main() {
	int n; //作业规模
	scanf("%d", &n);

	//利润 截止日期 活动编号 0 1 2
	vector<tuple<int, int, int>> array;
	array.reserve(n);


	int maxd = 0;
	for (int i = 1; i <= n; i++) {
		int income, deadline;
		scanf("%d%d", &deadline, &income);
		if (maxd < deadline) maxd = deadline;
		//i号活动
		array.push_back({ income, deadline, i });
	}

	//按照活动利润升序排列
	sort(array.begin(), array.end(), greater<tuple<int, int, int>>());

	/*
	for (auto i : array) {
		printf("这是%d号节点,利润是%d,截止日期是%d\n", get<2>(i), get<0>(i), get<1>(i));
	}
	*/
	
	//建立并查集 有0号节点
	n = min(n, maxd);
	vector<Tree*> set(n + 1, nullptr);
	for (int i = 0; i <= n; i++) {
		set[i] = new Tree(i);
	}

	int maxincome{ 0 }; //最优效益值

	for (auto i : array) {
		auto[income, deadline, val] = i;
		//应对那些时间很宽松的活动
		deadline = min(deadline, n);
		Tree* thisact_root = Tree::findroot(set[deadline]);
		if (thisact_root->val < 0 && thisact_root->number != 0) {
			//这就表明这个时间片是空的
			maxincome += income;
			thisact_root->val = val;
			thisact_root->father = Tree::findroot(set[thisact_root->number - 1]);
		}
	}
	printf("%d\n", maxincome);
	for (int i = 1; i < n; i++) {
		if (set[i]->val > 0) printf("%d ", set[i]->val);
	}
	if (set[n]->val > 0) printf("%d", set[n]->val);

	return 0;
}

