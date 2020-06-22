#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::vector;

// Using partition as index
// |a|c|
// |a|*|c|
// 0 1 2 3
class Solution
{
public:
    bool isMatch(string s, string p) {
        vector<vector<bool>> dp(s.size() + 1, vector<bool>(p.size() + 1, false));

        // Note that 'i', 'j' represent partition index.
        for (int i = 0; i <= s.size(); i++)
        {
            for (int j = 0; j <= p.size(); j++)
            {
                if (i == 0 && j == 0)
                {
                    dp[i][j] = true;
                }
                else if (i == 0 && j != 0)
                {
                    dp[i][j] = (p[j - 1] == '*') ? dp[i][j - 1] : false;
                }
                else if (i != 0 && j != 0)
                {
                    if (s[i - 1] == p[j - 1] || p[j - 1] == '?')
                    {
                        dp[i][j] = dp[i - 1][j - 1];
                    }
                    else if (p[j - 1] == '*')
                    {
                        dp[i][j] = dp[i - 1][j - 1] /* match 1 char */ | dp[i][j - 1] /* match 0 char */ | dp[i - 1][j] /* match multiple char */;
                    }
                }
            }
        }

        return dp.back().back();
    }
};

int main()
{
    Solution s;

    // Test 1:
    std::cout << s.isMatch("aa", "a*") << std::endl;

    // Test 2:
    std::cout << s.isMatch("adceb", "a*b*") << std::endl;

    // Test 3:
    std::cout << s.isMatch("aaaaaa", "aa*a*") << std::endl;
}