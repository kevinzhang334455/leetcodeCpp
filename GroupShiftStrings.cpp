#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

/* We can shift a string by shifting each of its letters to its successive letter.

For example, "abc" can be shifted to be "bcd".
We can keep shifting the string to form a sequence.

For example, we can keep shifting "abc" to form the sequence: "abc" -> "bcd" -> ... -> "xyz".
Given an array of strings strings, group all strings[i] that belong to the same shifting sequence. You may return the answer in any order.

Example 1:

Input: strings = ["abc","bcd","acef","xyz","az","ba","a","z"]
Output: [["acef"],["a","z"],["abc","bcd","xyz"],["az","ba"]]
Example 2:

Input: strings = ["a"]
Output: [["a"]] */

// Possible Clarfications:
// 1) How can 'z' right shift or how can 'a' left shift? E.g. Does ["az", "ba"] belong to same group?
// 2) Can input have duplicate string? do we need to de-dedup?
// 3) Can input has upper cases or any invalid characters?

class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        unordered_map<string, vector<string>> mp;
        for (auto str : strings) {
            auto key = shiftStr(str);
            if (mp.find(key) == mp.end()) {
                mp.emplace(key, vector<string>());
            }
            
            mp[key].push_back(str);
        }
        
        vector<vector<string>> result;
        
        // this is structured binding which is new in C++17. See: https://en.cppreference.com/w/cpp/language/structured_binding
        for (const auto& [k, v] : mp) {
            result.push_back(v);
        }
        
        return result;
    }
private:
    string shiftStr(string str) {
        if (str.empty()) {
            return str;
        } else if (str.size() == 1) {
            // return "a"; Wrong case -- cannot return "a" as "aa" will be same encoding.
            // just return anything to represent single string.
            return "-";
        }
        
        string result;
        
        for (int i = 1; i < str.size(); i++) {
            int diff = str[i] - str[i - 1];
            if (diff < 0) {
                diff += 26;
            }
            
            result.append(1, static_cast<char>('a' + diff));
        }
        
        return result;
    }
};

void print(const vector<vector<string>>& strGroups) {
    for (auto strGroup : strGroups) {
        for (auto str : strGroup) {
            cout << str << ' ';
        }

        cout << endl;
    }

    cout << endl;
}

int main() {
    Solution s;
    vector<string> test1 = {"abc","bcd","acef","xyz","az","ba","a","z"};
    print(s.groupStrings(test1));


    vector<string> test2 = { "a", "bb", "aa"};
    print(s.groupStrings(test2));
}