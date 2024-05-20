#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

struct myPair {
    double x;
    double y;
};

// 1拉伸 2旋转
#define STRETCH 1
#define ROTATE 2
struct Op {
    double stretch_k;
    double rotate_sita;
};

myPair stretchK(myPair a, double k) {
    a.x = k * a.x;
    a.y = k * a.y;
    return a;
}

myPair rotate(myPair a, double sita) {
    auto cos_sita = cos(sita);
    auto sin_sita = sin(sita);
    myPair returnPair{0, 0};
    returnPair.x = a.x * cos_sita - a.y * sin_sita;
    returnPair.y = a.x * sin_sita + a.y * cos_sita;
    return returnPair;
}

int main() {
    // freopen("in.txt", "r", stdin);
    int n, m;

    // n是操作 m是查询个数
    scanf("%d %d", &n, &m);

    // 操作是从1 开始
    vector<Op> operations;

    // 从1开始
    operations.push_back({0, 0});
    for (int i = 1; i <= n; i++) {
        // 先输入n个操作
        int tmp;
        double num;
        scanf("%d %lf", &tmp, &num);
        if (i == 1) {
            if (tmp == STRETCH) {
                // 拉伸
                operations.push_back({num, 0});
            } else {
                // 旋转
                operations.push_back({1, num});
            }
        } else {
            // 开始做累计
            if (tmp == STRETCH) {
                auto tmpop = operations.back();
                tmpop.stretch_k = tmpop.stretch_k * num;
                operations.push_back(tmpop);
            } else {
                // 旋转
                auto tmpop = operations.back();
                // 这个地方要取余数2pi
                tmpop.rotate_sita = tmpop.rotate_sita + num;
                operations.push_back(tmpop);
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        int begin;
        int end;
        double pointx;
        double pointy;
        scanf("%d %d %lf %lf", &begin, &end, &pointx, &pointy);

        myPair cur_p{pointx, pointy};
        // 对cur_p进行闭区间 就是begin end的闭区间的操作
        // 积累到一起算

        if (begin == 1) {
            // 这种情况就不需要找到begin前的那个操作反来
            cur_p = stretchK(cur_p, operations[end].stretch_k);

            cur_p = rotate(cur_p, operations[end].rotate_sita);
        } else {
            cur_p = stretchK(cur_p, operations[end].stretch_k);

            cur_p = rotate(cur_p, operations[end].rotate_sita);

            cur_p = stretchK(cur_p, 1.0 / operations[begin - 1].stretch_k);

            cur_p = rotate(cur_p, -operations[begin - 1].rotate_sita);
        }
        printf("%lf %lf\n", cur_p.x, cur_p.y);
    }
    return 0;
}
