
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct mypair {
	int begin;
	int end;
};

int main() {
	//试试使用C++的风格
	int n;
	cin >> n;
	int return_result{ 0 }; //最终的计数打印结果
	vector<mypair> array;
	array.reserve(n);
	for (int i = 1; i <= n; i++) {
		int begin, end;
		cin >> begin >> end;
		array.push_back({ begin,end });
	}

	sort(array.begin(), array.end(), [](const mypair&a, const mypair&b) {
		if (a.end <= b.end) return true;
		return false;
	});
	/*
	for (auto i : array) {
		cout << i.begin << ' ' << i.end << endl;
	}
	*/
	int lastend = -1; //存储上一个活动的结束时间
	for (auto &i:array) {
		if (i.begin > lastend) {
			lastend = i.end;
			return_result++;
		}
	}
	cout << return_result;

	return 0;
}
