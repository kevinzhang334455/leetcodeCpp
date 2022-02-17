#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <iostream>
using namespace std;

// A transformation sequence from word beginWord to word endWord using a dictionary 
// wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:

// Every adjacent pair of words differs by a single letter.
// Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
// sk == endWord
// Given two words, beginWord and endWord, and a dictionary wordList, return the number of words
// in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.

// Example 1:
// Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
// Output: 5
// Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if (wordList.empty()) {
            return 0;
        }

        unordered_set<string> words;
        for (auto word : wordList) {
            words.insert(word);
        }

        int N = beginWord.size();
        queue<pair<string, int>> q;
        unordered_set<string> vis;

        q.emplace(beginWord, 1);
        vis.insert(beginWord);

        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            
            if (cur.first == endWord) {
                return cur.second;
            }

            string next = cur.first;
            for (int i = 0; i < N; i++) {
                char cp = next[i];
                for (int j = 0; j < 26; j++) {
                    char c = 'a' + j;
                    next[i] = c;
                    if (
                        (words.find(next) != words.end() || next == endWord) && 
                        vis.find(next) == vis.end()) {
                        q.emplace(next, cur.second + 1);
                        vis.insert(next);
                    }
                }

                next[i] = cp;
            }
        }

        return 0;
    }
};

int main () {
    Solution s;
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};
    cout << s.ladderLength("hit", "cog", wordList) << endl;
}