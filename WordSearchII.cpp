#include "PrintUtil.hpp"
#include <vector>
#include <string>

using namespace std;

/* Given an m x n board of characters and a list of strings words, 
return all words on the board.
Each word must be constructed from letters of sequentially adjacent cells, 
where adjacent cells are horizontally or vertically neighboring. The same 
letter cell may not be used more than once in a word. */

class Solution {
    struct Trie {
        string word;
        Trie* nodes[26];
        Trie() {
            for (int i = 0; i < 26; i++) {
                nodes[i] = nullptr;
            }
        }
    };
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> results;
        if (board.empty() || words.empty()) {
            return results;
        }

        Trie* root = BuildTrie(words);
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                dfs(board, i, j, root, results);
            }
        }

        return results;
    }
private:
    void dfs(
        vector<vector<char>>& board, 
        int i, 
        int j, 
        Trie* curr, 
        vector<string>& results) {
        if (i < 0 || i >= board.size()) {
            return;
        } else if (j < 0 || j >= board[0].size()) {
            return;
        } else if (board[i][j] == '#') {
            return;
        } 

        char c = board[i][j];
        Trie* next = curr->nodes[c - 'a'];

        if (next == nullptr) {
            return;
        } else if (!next->word.empty()) {
            results.push_back(next->word);
            next->word = "";
        }

        board[i][j] = '#';

        dfs(board, i - 1, j, next, results);
        dfs(board, i + 1, j, next, results);
        dfs(board, i, j - 1, next, results);
        dfs(board, i, j + 1, next, results);

        board[i][j] = c;
    }

    Trie* BuildTrie(const vector<string>& words) {
        Trie* root = new Trie();
        for (auto word : words) {
            Trie* curr = root;
            for (int i = 0; i < word.size(); i++) {
                if (curr->nodes[word[i] - 'a'] == nullptr) {
                    curr->nodes[word[i] - 'a'] = new Trie();
                }
                
                curr = curr->nodes[word[i] - 'a'];
            }

            curr->word = word;
        }

        return root;
    }
};

int main () {
    Solution s;
    vector<vector<char>> board(1, vector<char>(2, 'a'));
    vector<string> words = {"aa"};
    PrintUtil::printVectorOf(s.findWords(board, words));
}