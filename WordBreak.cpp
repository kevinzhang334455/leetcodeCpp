#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;

// Given a string s and a dictionary of strings wordDict, 
// return true if s can be segmented into a space-separated sequence of one or more dictionary words.

// Note that the same word in the dictionary may be reused multiple times in the segmentation.

// Example 1:

// Input: s = "leetcode", wordDict = ["leet","code"]
// Output: true
// Explanation: Return true because "leetcode" can be segmented as "leet code".

// DFS with memoization.

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        if (s.empty()) {
            return false;
        }

        unordered_set<string> words;
        for (string word : wordDict) {
            words.insert(word);
        }

        int N = s.size();

        // dp[i][j] ==> string[i..j] can be segmented. -1 marked as unvisited.
        vector<vector<int>> dp(N, vector<int>(N, -1));
        return dfs(s, words, 0, N - 1, dp);
    }
private:
    bool dfs(
        const string& s, 
        const unordered_set<string>& words,
        int start, 
        int end, 
        vector<vector<int>>& dp) {
            int N = s.size();
            if (start >= N) {
                return true;
            }

            if (dp[start][end] != -1) {
                return dp[start][end] == 1 ? true : false;
            }

            for (int i = start; i <= end; i++) {
                string curr = s.substr(start, i - start + 1);
                if (words.find(curr) != words.end() && dfs(s, words, i + 1, end, dp)) {
                    dp[start][end] = 1;
                    return true;
                }
            }

            dp[start][end] = 0;
            return false;
    }
};

int main () {
    Solution s;
    vector<string> words = {"leet", "code"};
    cout << s.wordBreak("leetcode", words) << endl;
}