#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <utility>
#include <string>

using namespace std;

int partition(vector<int> &a, int m, int n) {
	//对m和n之间分划
	//递增
	int i = m, j = n + 1;

	//选第一个元素为基准元素
	int k = a[m];

	while (i < j) {
		i++;
		while (i <= n && a[i] <= k) i++; //找一个比k大的
		j--;
		while (a[j] > k) j--;
		if (i < j) swap(a[i], a[j]);
	}
	swap(a[m], a[j]);
	return j;
}

void quicksort(vector<int> &a, int m, int n) {
	//代码太少不敢调库QAQ
	if (m < n) {
		int j = partition(a, m, n);
		quicksort(a, m, j - 1);
		quicksort(a, j + 1, n);
	}
}


int main() {
	vector<int> array;
	array.reserve(5000);
	while (1) {
		char tmp;
		int i;
		scanf("%c", &tmp);
		if (tmp == ']') break;
		scanf("%d", &i);
		array.push_back(i);
	}
	quicksort(array, 0, array.size() - 1);
    
	//for (auto i : array) printf("%d", i);

	if (array.size() % 2 == 1) {
		if (array[(array.size() - 1) / 2] == array[0] || array[(array.size() - 1) / 2] == array[array.size() - 1]) printf("%d", array[(array.size() - 1) / 2]);
		else printf("NA");
	}
	else {
		int flag = 0;
		if (array[array.size() / 2 - 1] == array[array.size() - 1]) {
			printf("%d", array[array.size() / 2 - 1]);
			flag = 1;
		}
		if (array[array.size() / 2] == array[0]) {
			printf("%d", array[array.size() / 2]);
			flag = 1;
		}
		if (flag == 0) printf("NA");
	}
	return 0;
}
