#include <string>
using namespace std;
class Solution {
   public:
    string mergeAlternately(string word1, string word2) {
        string returnvalue = string{};
        returnvalue.reserve(word1.length() + word2.length());
        auto iter1 = word1.begin();
        auto iter2 = word2.begin();
        auto iter1endflag = 0;
        auto iter2endflag = 0;
        while (!(iter1endflag && iter2endflag)) {
            if (iter1endflag == 1) {
            } else {
                returnvalue.push_back(*iter1);
                iter1 += 1;
                if (iter1 == word1.end()) iter1endflag = 1;
            }

            if (iter2endflag == 1) {
            } else {
                returnvalue.push_back(*iter2);
                iter2 += 1;
                if (iter2 == word2.end()) iter2endflag = 1;
            }
        }
        return returnvalue;
    }
};
int main() {
    Solution a;
    cout << a.mergeAlternately(string("wowow"), string("aaaa"));
}
