// 选做 传纸条问题
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
// 下标从1开始
// [x1][y1][x2][y2]表示x1y1和x2y2这两个点到右下角的最大路线的和
int global_income[51][51][51][51]{0};

void f(int x1, int y1, int x2, int y2, int income_arr[51][51], int m, int n) {
    if (x1 == x2 && y1 == y2) {
        global_income[x1][x2][y1][y2] = 0;
        return;
    }
    // 这个函数用来求global_income[x1][y1][x2][y2]
    if (x1 == m && y1 == n - 1 && x2 == m - 1 && y2 == n) {
        global_income[x1][y1][x2][y2] = income_arr[x1][y1] + income_arr[x2][y2];
        return;
    }

    if (x1 == m - 1 && y1 == n && x2 == m && y2 == n - 1) {
        global_income[x1][y1][x2][y2] = income_arr[x1][y1] + income_arr[x2][y2];
        return;
    }

    // 此时还没有递推到要到的情况
    int result1, result2, result3, result4;
    result1 = result2 = result3 = result4 = 0;

    if (y1 == n || y2 == n)
        result1 = 0;
    else {
        if (global_income[x1][y1 + 1][x2][y2 + 1] == 0) f(x1, y1 + 1, x2, y2 + 1, income_arr, m, n);
        // cout << global_income[x1][y1 + 1][x2][y2 + 1] << endl;
        result1 = max(income_arr[x1][y1] + income_arr[x2][y2] + global_income[x1][y1 + 1][x2][y2 + 1], result1);
    }

    if (y1 == n || x2 == m)
        result2 = 0;
    else {
        if (global_income[x1][y1 + 1][x2 + 1][y2] == 0) f(x1, y1 + 1, x2 + 1, y2, income_arr, m, n);
        // cout << global_income[x1][y1 + 1][x2 + 1][y2] << endl;
        result2 = max(income_arr[x1][y1] + income_arr[x2][y2] + global_income[x1][y1 + 1][x2 + 1][y2], result2);
    }

    if (x1 == m || y2 == n)
        result3 = 0;
    else {
        if (global_income[x1 + 1][y1][x2][y2 + 1] == 0) f(x1 + 1, y1, x2, y2 + 1, income_arr, m, n);
        // cout << global_income[x1 + 1][y1][x2][y2 + 1] << endl;
        result3 = max(income_arr[x1][y1] + income_arr[x2][y2] + global_income[x1 + 1][y1][x2][y2 + 1], result3);
    }

    if (x1 == m || x2 == m)
        result4 = 0;
    else {
        if (global_income[x1 + 1][y1][x2 + 1][y2] == 0) f(x1 + 1, y1, x2 + 1, y2, income_arr, m, n);
        // cout << global_income[x1 + 1][y1][x2 + 1][y2] << endl;
        result4 = max(income_arr[x1][y1] + income_arr[x2][y2] + global_income[x1 + 1][y1][x2 + 1][y2], result4);
    }

    global_income[x1][y1][x2][y2] = max(result1, max(result2, max(result3, result4)));
    return;
}

int main() {
    // m行 n列
    // freopen("in.txt", "r", stdin);
    int m, n;
    int income_arr[51][51]{0};
    cin >> m >> n;
    // cout << m << n << endl;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) cin >> income_arr[i][j];
    f(2, 1, 1, 2, income_arr, m, n);
    cout << global_income[2][1][1][2];
    return 0;
}
