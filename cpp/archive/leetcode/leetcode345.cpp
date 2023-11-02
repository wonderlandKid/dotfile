#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Solution {
   public:
    array<char, 10> vowels{'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};

    bool is_vowel(const char& i) {
        return any_of(vowels.begin(), vowels.end(),
                      [&i](const char& i_arr) { return i_arr == i; });
    }
    string reverseVowels(string s) {
        vector<char> savechar;
        for (const auto& i : s)
            if (is_vowel(i)) savechar.push_back(i);

        int count = 0;
        for (int i = s.length() - 1; i >= 0; i--) {
            if (is_vowel(s[i])) {
                s[i] = savechar[count];
                count += 1;
            }
        }
        return s;
    }
};

int main() {
    Solution a;
    cout << a.reverseVowels("hello");
}
