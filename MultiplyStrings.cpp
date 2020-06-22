#include "PrintUtil.hpp"
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class Solution
{
public:
    string multiply(string num1, string num2)
    {
        string zero("0");
        string one("1");
        if (num1 == zero || num2 == zero)
        {
            return zero;
        }

        if (num1 == one || num2 == one)
        {
            return num1 == one ? num2 : num1;
        }

        if (num1.size() > num2.size())
        {
            std::swap(num1, num2);
        }

        std::reverse(num1.begin(), num1.end());
        std::reverse(num2.begin(), num2.end());
        string result(num1.size() + num2.size(), '0');

        for (int i = 0; i < num1.size(); i++)
        {
            int carry = 0;
            for (int j = 0; j < num2.size(); j++)
            {
                int curr = (num1[i] - '0') * (num2[j] - '0') + carry + (result[i + j] - '0');
                result[i + j] = ((curr % 10) + '0');
                carry = curr / 10;
            }

            if (carry != 0)
            {
                result[i + num2.size()] = carry + '0';
            }
        }

        while (result.back() == '0')
        {
            result.pop_back();
        }

        std::reverse(result.begin(), result.end());
        return result;
    }
};

int main()
{
    Solution s;

    // Test 1:
    string s11("6");
    string s12("7");
    std::cout << s.multiply(s11, s12) << std::endl;

    // Test 2:
    string s21("5");
    string s22("350");
    std::cout << s.multiply(s21, s22) << std::endl;

    // Test 3:
    string s31("9999");
    string s32("999");
    std::cout << s.multiply(s31, s32) << std::endl;

    // Test 4:
    string s41("999");
    string s42("9999");
    std::cout << s.multiply(s41, s42) << std::endl;

    // Test 5:
    string s51("99999");
    string s52("99999");
    std::cout << s.multiply(s51, s52) << std::endl;

    // Test 6:
    string s61("10000");
    string s62("10000");
    std::cout << s.multiply(s61, s62) << std::endl;

    // Test 7:
    string s71, s72;
    for (int i = 0; i < 110; i++)
    {
        char c = '9';
        s71.push_back(c);
        s72.push_back(c);
    }

    std::cout << s.multiply(s71, s72) << std::endl;
}