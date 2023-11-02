#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
using namespace std;
    class Solution {
    public:
        auto return_quotient_and_remain(string_view str1, string_view str2) {
            // 用str1除以str2 余数是多少 商是多少
            auto i = str1.find(str2);
            if (i != 0 || i == string::npos) return tuple{0, str1};
            int quotient = 0;
            while (true) {
                str1.remove_prefix(str2.length());
                quotient += 1;
                auto i = str1.find(str2);
                if (i != 0 || i == string::npos) return tuple{quotient, str1};
            }
        }

        string_view gcd(string_view str1, string_view str2) {
            auto [quotient, remain] = return_quotient_and_remain(str1, str2);
            if (quotient == 0 && remain == str1) return "";
            if (remain == "") return str2;
            return gcd(str2, remain);
        }

        string gcdOfStrings(string str1, string str2) {
            // 辗转相除法
            // if (str1.find(str2) == string::npos) return {""};
            string_view refstr1{str1};
            string_view refstr2{str2};
            if (str2.length() > str1.length()) {
                refstr1 = str2;
                refstr2 = str1;
            }

            return string(gcd(refstr1, refstr2));
        }
    };

int main() {
    Solution a;
    cout << a.gcdOfStrings(
                string("TAUXXTAUXXTAUXXTAUXXTAUXX"),
                string("TAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXX"))
         << '\n';
}
