#include <bits/stdc++.h>
using namespace std;

class Trie {
   public:
    Trie() {
        is_end = false;
        for (int i = 0; i < 26; i++) {
            search_array[i] = nullptr;
        }
    }

    void insert(string word) {
        // 从根节点开始搜索
        Trie* cur = this;
        for (size_t i = 0; i < word.size(); i++) {
            if (cur->search_array[word[i] - 'a'] == nullptr) {
                cur->search_array[word[i] - 'a'] = new Trie();
            }
            cur = cur->search_array[word[i] - 'a'];
            if (i == word.size() - 1) cur->is_end = true;
        }
        return;
    }

    bool search(string word) {
        Trie* cur = this;
        for (size_t i = 0; i < word.size(); i++) {
            if (cur->search_array[word[i] - 'a'] == nullptr) return false;
            cur = cur->search_array[word[i] - 'a'];
            if (i == word.size() - 1 && cur->is_end == false) return false;
        }
        return true;
    }

    bool startsWith(string prefix) {
        Trie* cur = this;
        for (size_t i = 0; i < prefix.size(); i++) {
            if (cur->search_array[prefix[i] - 'a'] == nullptr) return false;
            cur = cur->search_array[prefix[i] - 'a'];
        }
        return true;
    }

   private:
    bool is_end;
    Trie* search_array[26];
};

int main(int argc, char* argv[]) {
    // Solution test;
    int a = 2;
    int b = 6;
    int c = 5;
    // cout << test.minFlips(a, b, c);
    // cout << a.longestCommonSubsequence(t1, t2);
    return 0;
}
