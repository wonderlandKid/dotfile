//归并分类
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>
using namespace std;


void mergesort(vector<int> &a, int m, int n) {
	//对m和n之间的部分进行归并排序 小->大
	if (n == m + 1) {
		if (a[n] < a[m]) swap(a[n], a[m]);
		return;
	}
	if (m == n) return;
	int mid = (m + n) / 2;
	mergesort(a, m, mid);
	mergesort(a, mid + 1, n);
	int i = m, j = mid + 1;
	vector<int> newa(n - m + 1, 0); //归并的新结果
	for (int &tgt : newa) {
		if (i > mid) { tgt = a[j]; j++; continue; }
		if (j > n) { tgt = a[i]; i++; continue; }
		if (a[i] <= a[j]) {
			tgt = a[i];
			i++;
		}
		else {
			tgt = a[j];
			j++;
		}
	}
	int begin = m;
	for (int i : newa) {
		a[begin] = i;
		begin++;
	}
	
}

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
	mergesort(array, 0, array.size() - 1);
	for (int i = 0; i < array.size() - 1; i++) printf("%d ", array[i]);
	printf("%d", array[array.size()-1]);
	return 0;
}
