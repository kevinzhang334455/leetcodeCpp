#include "PrintUtil.hpp"
#include <vector>
#include <string>
#include <stack>
#include <unordered_set>

using namespace std;

/* 
Given a string s that contains parentheses and letters, remove the 
minimum number of invalid parentheses to make the input string valid.
Return all the possible results. You may return the answer in any order.
*/

/* 
Example 1:
Input: s = "()())()"
Output: ["(())()","()()()"]

Example 2:
Input: s = "(a)())()"
Output: ["(a())()","(a)()()"]

Example 3:
Input: s = ")("
Output: [""]
*/

// we should do depth-first search on this case.
// When we remove '(', there is only 1 case that there are not enough ')'.
// when we remove ')', there are a couple of cases 1) no enough '(', 2) not
// select this ')' because there are possibility there are ')' after.

// Note, from test 6 below it indicates that a ')' doesn't have to match with
// the nearest '(', instead, it can match any of the previous '(', making final
// strings look different. 
// Another example: "(c(s(k()((" => it can be ["csk()","cs(k)","c(sk)","(csk)"]

// this solution is correct from algorithm perspective but it is TLE.
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> ans;
        if (s.empty()) {
            ans.push_back(s);
            return ans;
        }

        vector<int> lefts;

        dfs("", lefts, s, 0, ans);
        unordered_set<string> us;
        for (auto i : ans) {
            us.insert(i);
        }

        ans.clear();
        for (auto i = us.begin(); i != us.end(); i++) {
            ans.push_back(*i);
        }
        return ans;
    }
private:
    void dfs(string curr, vector<int> lefts, string s, int idx, vector<string>& ans) {
        if (idx == s.size()) {
            while (!lefts.empty()) {
                curr.erase(curr.begin() + lefts.back());
                lefts.pop_back();
            }

            if (ans.empty() || ans[0].size() == curr.size()) {
                ans.push_back(curr);
            } else if (ans[0].size() < curr.size()) {
                ans.clear();
                ans.push_back(curr);
            }

            return;
        }

        if (s[idx] == '(') {
            // Instead of directly append and then remove, consider
            // branch two dfs recursions.
            curr.append(1, '(');
            lefts.push_back(curr.size() - 1);
            dfs(curr, lefts, s, idx + 1, ans);
        } else if (s[idx] == ')') {
            if (!lefts.empty()) {
                // this will add extra overhead to 1 dfs branch.
                for (int i = 0; i < lefts.size(); i++) {
                    auto next = lefts;
                    next.erase(next.begin() + i);
                    curr.append(1, ')');
                    dfs(curr, next, s, idx + 1, ans);
                    curr.pop_back();
                }
            }

            // or not remove lefts at all.
            dfs(curr, lefts, s, idx + 1, ans);
        } else {
            curr.append(1, s[idx]);
            dfs(curr, lefts, s, idx + 1, ans);
        }
    }
};

struct Test {
    Solution s;
    string str;
    Test(Solution s, string str): s(s), str(str) {}
    void Run() {
        PrintUtil::printVectorOf(s.removeInvalidParentheses(str));
    }
};

int main () {
    Solution s;
    Test test0(s, "((()");
    Test test1(s, "()())()");
    Test test2(s, "(a)())()");
    Test test3(s, "()");
    Test test4(s, ")(");
    Test test5(s, "()()))(())");
    Test test6(s, "(((k()(("); // => k(), (k)
    Test test7(s, "(c(s(k()((");

    test0.Run();
    test1.Run();
    test2.Run();
    test3.Run();
    test4.Run();
    test5.Run();
    test6.Run();
    test7.Run();
}