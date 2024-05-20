#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    unordered_map<char, string> searchmap{
        {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"},
    };

    string numbercharToString(char c) { return searchmap.operator[](c); }

    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        vector<string> return_vector;

        string cur_tmp_string;
        cur_tmp_string.reserve(digits.size());

        vector<int> downindexs(digits.size(), 0);

        // 0代表现在正在处理哪一位
        int p = 0;

        while (true) {
            if (p >= digits.size()) {
                // 这种情况就是有一种成功的结果
                return_vector.push_back(cur_tmp_string);
                p--;
                cur_tmp_string.pop_back();
            }

            // 回溯结束
            if (p < 0) break;

            // 现在开始处理p所指向的内容
            // 如果p指向的位置的下标还可以增大 就增大一个 然后p++
            // 如果不行 那么清除p的下标 p-- 处理上一个
            string const& cur_p_string = numbercharToString(digits[p]);

            // downindexs[p]存的是指向这个字符串的下标
            if (downindexs[p] < cur_p_string.size()) {
                // 这里 downindexs[p]可能会越界 越界就表明这里的情况已经尝试完了
                cur_tmp_string.push_back(cur_p_string[downindexs[p]]);
                downindexs[p]++;
                p++;
            } else {
                downindexs[p] = 0;
                p--;
                if (cur_tmp_string.empty()) break;
                cur_tmp_string.pop_back();
            }
        }

        return return_vector;
    }
};

int main(int argc, char* argv[]) {
    Solution a;
    a.letterCombinations("23");
    return 0;
}
