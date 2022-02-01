#include <string>
#include <vector>
using namespace std;

// Approach 1: to get every possible substring [1..len/2] and see whether the given substring
// an be repeated. 

// time complexity: O(N^2). Space complexity O(N)

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int N = s.size();
        
        bool ans = false;
        for (int len = 1; len <= s.size() / 2; len++) {
            string pattern = s.substr(0, len);
            int startIdx = len;
            while (startIdx < s.size() && s.substr(startIdx, len) == pattern) {
                startIdx += len;
            }
            
            if (startIdx == s.size()) {
                ans = true;
                break;
            }
        }
        
        return ans;
    }
};

// Approach 2: KMP approach. 
// The general idea is to use the concept of prefix table (a.k.a suffix == prefix).
// we build a prefix table in which dp[i] == is repeated string up to s[i].
// Then the final answer is dp[n] (in which it means it is repeated) and dp[n] % (n - dp[n]) == 0.

// Reference:
// 1) KMP: https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm
// 2) How to build prefix table: http://www.btechsmartclass.com/data_structures/knuth-morris-pratt-algorithm.html

class Solution2 {
public:
   bool repeatedSubstringPattern(string s) {
       int N = s.size();
       vector<int> dp(N, 0);
       for (int i = 0, j = 1; j < s.size(); j++) {
           if (s[i] == s[j]) {
               // e.g. abab, i = 0, j = 2. dp[2] = 1. dp[3] = 2
               dp[j] = dp[i] + 1;
               i++;
           } else if (i == 0) {
               // e.g. abc
               dp[j] = 0;
           } else {
               // e.g. ababc, i = 2, j = 4. 
               dp[j] = dp[i];
           }
       }

       return dp.back() != 0 && (N % (N - dp.back()));
   }
};

int main () {

}