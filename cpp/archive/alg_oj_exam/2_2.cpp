// 动态规划解决01背包问题
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
int global_income[1000][10000]{0};

void f(int i, int weight, vector<int>& p, vector<int>& w) {
    // 求global_income[i][weight] 需要[i-1][weight]和[i-1][weight-w[i]]
    if (i == 1 && weight >= w[1]) {
        global_income[1][weight] = p[1];
        return;
    }
    if (i == 1 && weight < w[1]) {
        global_income[1][weight] = 0;
        return;
    }
    if (global_income[i - 1][weight] == 0) f(i - 1, weight, p, w);
    if (weight >= w[i]) {
        if (global_income[i - 1][weight - w[i]] == 0) f(i - 1, weight - w[i], p, w);
        if (global_income[i - 1][weight - w[i]] + p[i] > global_income[i - 1][weight])
            global_income[i][weight] = global_income[i - 1][weight - w[i]] + p[i];
        else
            global_income[i][weight] = global_income[i - 1][weight];
        return;
    }
    global_income[i][weight] = global_income[i - 1][weight];
    return;
}

int main() {
    freopen("in.txt", "r", stdin);
    int M, n;
    cin >> M >> n;
    int copyM = M;
    vector<int> w(n + 1, 0);
    vector<int> p(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 1; i <= n; i++) cin >> p[i];
    f(n, M, p, w);

    vector<int> result(n + 1, 1);
    for (int i = n; i >= 1; i--) {
        if (global_income[i][M] == global_income[i - 1][M])
            result[i] = 0;
        else {
            // 物品i被放进来了
            M -= w[i];
        }
    }
    int weight_sum = 0;
    for (int i = 1; i < result.size(); i++) {
        if (result[i] == 1) weight_sum += w[i];
    }
    cout << global_income[n][copyM] << ' ' << weight_sum << endl;
    for (int i = 1; i < result.size(); i++) {
        if (i == result.size() - 1)
            cout << result[i];
        else
            cout << result[i] << ' ';
    }
    return 0;
}
