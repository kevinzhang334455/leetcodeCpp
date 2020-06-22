#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using std::vector;
using std::string;
using std::pair;
using std::unordered_map;

// Symbol       Value
// I             1
// V             5
// X             10
// L             50
// C             100
// D             500
// M             1000

class Solution 
{
public:
    string intToRoman(int num) 
    {
        if (num <= 0 || num > 3999)
        {
            return string("");
        }

        vector<pair<int, string>> intToRomanTable = 
        {
            { 1000, "M" },
            { 900, "CM" },
            { 500, "D" },
            { 400, "CD" },
            { 100, "C" },
            { 90, "XC" },
            { 50, "L" },
            { 40, "XL" },
            { 10, "X" },
            { 9, "IX" },
            { 5, "V" },
            { 4, "IV" },
            { 1, "I" }
        };

        string result;
        int curr = num;
        for (int i = 0; i < intToRomanTable.size(); i++)
        {
            auto integer = intToRomanTable[i].first;
            auto roman = intToRomanTable[i].second;

            int times = curr / integer;
            for (int i = 0; i < times; i++)
            {
                result += roman;
                curr -= integer;
            }
        }

        return result;
    }

    int romanToInt(string roman)
    {
        unordered_map<string, int> romanToIntTable = 
        {
            { "M", 1000 },
            { "CM", 900 },
            { "D", 500 },
            { "CD", 400 },
            { "C", 100 },
            { "XC", 90 },
            { "L", 50 },
            { "XL", 40 },
            { "X", 10 },
            { "IX", 9 },
            { "V", 5 },
            { "IV", 4 },
            { "I", 1 }
        };

        int result = 0;
        for (int i = 0; i < roman.size(); )
        {
            string key;
            if (i != roman.size() - 1 && (roman[i] == 'C' || roman[i] == 'X' || roman[i] == 'I'))
            {
                key = roman.substr(i, 2);
                if (romanToIntTable.find(key) != romanToIntTable.end())
                {
                    result += romanToIntTable[key];
                    i = i + 2;
                    continue;
                }
            }

            key = roman.substr(i, 1);
            result += romanToIntTable[key];
            i = i + 1;
        }

        return result;
    }
};

int main ()
{
    Solution s;
    for (int i = 3999; i > 0; i--)
    {
        int num = s.romanToInt(s.intToRoman(i));
        if (num != i)
        {
            std::cout << "Error case: " << "Correct, " << i << "Wrong, " << num << std::endl;
        }
    }
}