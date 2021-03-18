#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/* 

Given a string containing just the characters '(' and ')', 
find the length of the longest valid (well-formed) parentheses substring.

Example 1:

Input: s = "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()".
Example 2:

Input: s = ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()". 
*/

// Basic Idea: Dynamic Programming. 
// record dp[i] == length of valid parenthesis where the last char is i. So if s[i] == '('
// then dp[i] = 0, else if s[i] has a match parenthesis we record the length of valid parenthsis.
// Then dp[i] == s[i] == ')' ? dp[matchedLeft - 1] + (i - matchedLeft + 1) <current length>. 

class Solution {
public:
    int longestValidParentheses(string s) {
        if (s.size() == 0 || s.size() == 1) {
            return 0;
        }

        vector<int> dp(s.size(), 0);
        stack<int> leftParIdx;
        int result = 0;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                leftParIdx.push(i);
            } else if (!leftParIdx.empty()) {
                int matchedLeftIdx = leftParIdx.top();
                leftParIdx.pop();

                int currLen = i - matchedLeftIdx + 1;
                int adjLen = matchedLeftIdx > 0 ? dp[matchedLeftIdx - 1] : 0;
                currLen += adjLen;
                dp[i] = currLen;

                result = max(result, currLen);
            }
        }

        return result;
    }
};

void TestUtil(string s)
{
    Solution solution;
    cout << solution.longestValidParentheses(s) << endl;
}

int main () {
    string s1 = "(()";
    string s2 = "()()()";
    string s3 = "((()()(";
    string s4  = "((()()()))";
    TestUtil(s1);
    TestUtil(s2);
    TestUtil(s3);
    TestUtil(s4);
}