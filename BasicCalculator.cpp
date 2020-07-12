#include <string>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <cctype>
#include <algorithm>

using namespace std;

// The calculator should support integer calculations ('+ - * /') and parathesis ('()')
// we can assume no invalid characters except for ' ', and we can assume that the expression is valid.
// Input integers should be non-negative.

class Solution
{
public:
    int calculate(string s)
    {
        unordered_map<char, int> level_map;

        level_map.emplace('(', 0);
        level_map.emplace('+', 1);
        level_map.emplace('-', 1);
        level_map.emplace('*', 2);
        level_map.emplace('/', 2);

        s.erase(std::remove_if(s.begin(), s.end(), [](unsigned char x) {
            return std::isspace(x);
            }), s.end());

        s.push_back('&'); // EOF

        stack<int> nums;
        stack<char> ops;

        int curr = 0;

        for (int i = 0; i < s.size(); i++)
        {
            if (isdigit(s[i]))
            {
                curr = curr * 10 + (s[i] - '0');
                continue;
            }

            if (s[i] == '(')
            {
                ops.push(s[i]);
                continue;
            }

            if (level_map.find(s[i]) != level_map.end() && (ops.empty() || level_map[ops.top()] < level_map[s[i]]))
            {
                nums.push(curr);
                ops.push(s[i]);
                curr = 0;
            }
            else
            {
                while (!ops.empty() && ops.top() != '(' && level_map[ops.top()] >= level_map[s[i]])
                {
                    int prev = nums.top();
                    nums.pop();
                    char op = ops.top();

                    curr = Calc(prev, curr, op);
                    ops.pop();
                }

                if (s[i] == ')')
                {
                    ops.pop(); // pop for the left '('
                }
                else if (s[i] != '&')
                {
                    ops.push(s[i]);
                    nums.push(curr);
                    curr = 0;
                }
            }
        }

        return curr;
    }

private:
    int Calc(int num1, int num2, char op)
    {
        int res = 0;
        switch (op)
        {
            case '+':
            res = num1 > 0 ? (INT_MAX - num1 > num2 ? num1 + num2 : INT_MAX) : num1 + num2;
            break;
            case '-':
            res = num2 > 0 ? (num1 > num2 + INT_MIN ? num1 - num2 : INT_MIN) : num1 - num2;
            break;
            case '*':
            res = num1 != 0 ? (INT_MAX / num1 > num2 ? num1 * num2 : INT_MAX) : 0;
            break;
            case '/':
            res = num2 != 0 ? num1 / num2 : INT_MAX;
            break;
        }

        return res;
    }
};

int main ()
{
    Solution s;

    // test 1:
    cout << s.calculate("3 + 5") << endl;

    // test 2:
    cout << s.calculate("3 + ((5 + 8) - 2)") << endl;

    // test 3:
    cout << s.calculate("3 * 6 - 2 / 2") << endl;

    // test 4:
    cout << s.calculate("3 * (2 + (7 - 3) * 4) - 2 * (7 * 1)") << endl;

    // test 5:
    cout << s.calculate("3 * ((2 + 6) - (3 * 2) + (2 + 3) * 4)") << endl;

    // test 6:
    cout << s.calculate("1 * 2 - 3 / 4 + 5 * 6 - 7 * 8 + 9 / 10") << endl;

    // Test 7:
    cout << s.calculate("(3 * ((2 + 6) - (3 * 2) + (2 + 3) * 4)) + (1 * 2 - 3 / 4 + 5 * 6 - 7 * 8 + 9 / 10)") << endl;

    // Test 8:
    cout << s.calculate("1 + 2 * 5 / 3 + 6 / 4 * 2") << endl;

    // Test 9:
    cout << s.calculate("1 * 2 - 3 * 4 - 5 * 6 - 7 * 8") << endl;
}