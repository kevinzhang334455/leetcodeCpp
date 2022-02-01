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
    }

private:
    void dfs(
        string num, 
        int idx, 
        string currExpr, 
        int curr_eval, 
        int target,
        vector<string>& ans) {
            if (idx == num.size()) {
                if (curr_eval == target) {
                    ans.push_back(currExpr);
                }
                
                return;
            }

            
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