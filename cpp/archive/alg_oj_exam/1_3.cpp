#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct Combine
{
	int val; //编号
	int income;
	int weight;
	//这个号对应的物品取多少个 0~1
	float howmuch{ -1 };
};

int main() {
	int M, n;
	scanf("%d%d", &M, &n);

	//编号 利润 重量的顺序
	vector<Combine> array(n, { 0,0,0 });
	//从1开始
	for (int i = 0; i <= n - 1; i++) {
		int weighti;
		scanf("%d", &weighti);
		array[i].weight = weighti;
		//编号也要改一下
		array[i].val = i;
	}
	for (int i = 0; i <= n - 1; i++) {
		int incomei;
		scanf("%d", &incomei);
		array[i].income = incomei;
	}

	sort(array.begin(), array.end(), [](const Combine&a, const Combine&b) {
		if ((double)a.income / a.weight > (double)b.income / b.weight) return true;
		return false;
	});
/*
	for (auto i : array) {
		printf("编号%d,利润%d,重量%d\n", i.val, i.income, i.weight);
	}
*/

	//按照p/w的顺序依次取出
	for (auto &i : array) {
		if (i.weight > M) {
			i.howmuch = (float)M / i.weight;
			M = 0;
		}
		else if (i.weight == M) {
			M = 0;
			i.howmuch = 1;
		}
		else {
			i.howmuch = 1;
			M -= i.weight;
		}

		if (M == 0)break;
	}

	vector<float> printresult(n, 0);
	double maxincome = 0;
	for (auto i : array) {
		if (i.howmuch < 0) break;

		//只要不是小于0就装了这个
		maxincome += i.howmuch*i.income;
		printresult[i.val] = i.howmuch;

	}

	printf("%g\n", maxincome);
	for (int i=0; i<n-1; i++) {
		printf("%.2f ", printresult[i]);
	}
    printf("%.2f", printresult[n-1]);
	return 0;
}
