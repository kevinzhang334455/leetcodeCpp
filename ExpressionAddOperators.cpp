#include "PrintUtil.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

// Given a string num that contains only digits and an integer target, 
// return all possibilities to insert the binary operators '+', '-', and/or '*' 
// between the digits of num so that the resultant expression evaluates 
// to the target value.

// Note that operands in the returned expressions should not contain leading zeros.

class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> ans;
        int pos = 0;
        string expr;
        dfs(num, expr, '+', pos, 0, target, ans);
        
        return ans;
    }

private:
    void dfs(
        const string& num, 
        string expr,
        char op,
        int pos,
        int eval,
        int target,
        vector<string>& ans) {
            if (pos == num.size()) {
                if (eval == target) {
                    ans.push_back(expr);
                }
                return;
            }

            bool numOverflow = false;
            for (int i = pos; i < num.size(); i++) {
                if (num[pos] == '0' && i != pos) {
                    // skip with head of 0.
                    break;
                } else if (i == pos ? false : stoi(num.substr(pos, i - pos)) > INT_MAX/10) {
                    // skip if the current number is overflow.
                    break;
                }

                int curr = stoi(num.substr(pos, i - pos + 1));
                int newEval;
                if (!tryCalc(eval, curr, op, newEval)) {
                    break;
                }

                string nextExpr;
                if (!expr.empty()) {
                    nextExpr = expr + op + num.substr(pos, i - pos + 1);
                } else {
                    nextExpr = num.substr(pos, i - pos + 1);
                }

                if (i + 1 < num.size()) {
                    dfs(num, nextExpr, '+', i + 1, newEval, target, ans);
                    dfs(num, nextExpr, '-', i + 1, newEval, target, ans);
                    dfs(num, nextExpr, '*', i + 1, newEval, target, ans);
                } else {
                    dfs(num, nextExpr, '+', i + 1, newEval, target, ans);
                }
            }
        }

    bool tryCalc(int eval, int curr, char op, int& result) {
        if (op == '+') {
            if (eval <= INT_MAX - curr) {
                result = eval + curr;
                return true;
            } else {
                return false;
            }
        } else if (op == '-') {
            if (eval >= INT_MIN + curr) {
                result = eval - curr;
                return true;
            } else {
                return false;
            }
        } else if (op == '*') {
            if (curr == 0) {
                result = 0;
                return true;
            } else if (eval <= INT_MAX / curr) {
                result = eval * curr;
                return true;
            } else {
                return false;
            }
        }

        return false;
    }
};

struct Test {
    Solution s;
    string testStr;
    int target;
    Test(Solution s, string str, int target) : s(s), testStr(str), target(target) {}
    void Run() {
        PrintUtil::printVectorOf(s.addOperators(testStr, target));
    }
};

int main () {
    Solution s;
    Test test1(s, "233", 8);
    Test test2(s, "123", 6);
    Test test3(s, "1342", 15);
    test1.Run();
    test2.Run();
    test3.Run();
}