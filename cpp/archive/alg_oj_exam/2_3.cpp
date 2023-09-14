#include <iostream>
using namespace std;

struct equipment {
    int pgcost{-1};
    int runecost{-1};
    int times{-1};   // 为0买无数件
    int income{-1};  // 能力值
};

// [i][pg][rune]
// 前1~i个装备 耗费点数pg和rune能够购买的最大收益
int global_income[500][1000][1000] = {};

void f(int i, int pg, int rune, equipment earray[1000]) {
    // 用来求[i][pg][rune]
    // 要求[i][pg][rune] 要求earray[i].times+1次
    if (i == 1) {
        if (pg >= earray[1].pgcost && rune >= earray[1].runecost) {
            int finaltimes = 0;
            int copypg = pg;
            int copyrune = rune;
            while (1) {
                copypg -= earray[1].pgcost;
                copyrune -= earray[1].runecost;
                if (copyrune >= 0 && copypg >= 0)
                    finaltimes++;
                else
                    break;
                if (finaltimes == earray[1].times) break;
            }
            global_income[1][pg][rune] = finaltimes * earray[1].income;
            return;
        } else {
            global_income[1][pg][rune] = 0;
            return;
        }
    }

    // 现在i不为1 则需要从许多结果里面找最大的
    int max_final_result = 0;
    if (earray[i].times == 0) {
        // 则可以买无数次
        for (int flag = 0;; flag++) {
            if (pg >= flag * earray[i].pgcost && rune >= flag * earray[i].runecost) {
                // 表明可以买flag个
                if (global_income[i - 1][pg - flag * earray[i].pgcost][rune - flag * earray[i].runecost] == 0)
                    f(i - 1, pg - flag * earray[i].pgcost, rune - flag * earray[i].runecost, earray);
                int newincome = global_income[i - 1][pg - flag * earray[i].pgcost][rune - flag * earray[i].runecost] +
                                flag * earray[i].income;
                if (newincome > max_final_result) max_final_result = newincome;
            } else
                break;
        }
    } else {
        // 这里是有限次循环
        for (int flag = 0; flag <= earray[i].times; flag++) {
            if (pg >= flag * earray[i].pgcost && rune >= flag * earray[i].runecost) {
                // 表明可以买flag个
                if (global_income[i - 1][pg - flag * earray[i].pgcost][rune - flag * earray[i].runecost] == 0)
                    f(i - 1, pg - flag * earray[i].pgcost, rune - flag * earray[i].runecost, earray);
                int newincome = global_income[i - 1][pg - flag * earray[i].pgcost][rune - flag * earray[i].runecost] +
                                flag * earray[i].income;
                if (newincome > max_final_result) max_final_result = newincome;
            } else
                break;
        }
    }
    global_income[i][pg][rune] = max_final_result;
    return;
}

int main() {
    int N, P, R;
    cin >> N >> P >> R;
    equipment earray[1000];  // 下标从1开始
    for (int i = 1; i <= N; i++) {
        int pgcost;
        int runecost;
        int times;
        int income;
        cin >> pgcost >> runecost >> times >> income;
        earray[i].pgcost = pgcost;
        earray[i].runecost = runecost;
        earray[i].times = times;
        earray[i].income = income;
    }
    f(N, P, R, earray);
    cout << global_income[N][P][R];
    return 0;
}
