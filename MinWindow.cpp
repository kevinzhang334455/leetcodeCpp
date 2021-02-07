#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;

// Given a string S and a string T, find the minimum window in S which will contain all the characters in T 
// in complexity O(n).

// Input: S = "ADOBECODEBANC", T = "ABC"
// Output: "BANC"

// Algo: Two pointers

class Solution {
public:
    string minWindow(string s, string t) {
        if (t.empty() || s.empty()) {
            return string();
        }

        unordered_map<char, int> um;
        for (int i = 0; i < t.size(); i++) {
            if (um.find(t[i]) != um.end()) {
                um.insert(make_pair(t[i], 0));
            }

            um[t[i]]++;
        }

        string result;

        int p1 = 0, p2 = 0, remain = t.size();       
        for (; p2 < s.size(); p2++) {
            if (um.find(s[p2]) != um.end()) {

                // The below comment lines are not correct as this indicates that it won't allow redundant chars.
                // while (um[s[p2]] == 0) {
                //     if (um.find(s[p1]) != um.end()) {
                //         um[s[p1]]++;
                //         remain++;
                //     }

                //     p1++;
                // }

                um[s[p2]]--;
                if (um[s[p2]] >= 0) {
                    remain--;
                }

                if (remain == 0) {
                    while (um.find(s[p1]) == um.end() || um[s[p1]] < 0) {
                        if (um.find(s[p1]) != um.end()) {
                            um[s[p1]]++;
                        }

                        p1++;
                    }

                    string candidate = s.substr(p1, p2 - p1 + 1);
                    result = result.empty() || result.size() > candidate.size() ? candidate : result;
                }
            }
        }

        return result;
    }
};

// This sliding window algorithm should be a greedy algorithm where we want to find the best local result given
// s[p2]. The foundation of the this algo is that suppose s[p1:p2] and s[p1':p2'] can be both local optimal results 
// (not necessary best, but local optimal), if p2' > p2, then p1' > p1. So when we find the local optimal result for
// s[p2] (s[p1:p2]), we should safely push p1 -> p1 + 1 to exactly where remain != 0 (loop 102). The condition that
// s[p2] have optimal is that remain == 0, otherwise, there won't be any optimal results for s[p2] then we can safely
// pass it.
class Solution2 {
public:
    string minWindow(string s, string t) {
        if (t.empty() || s.empty()) {
            return string();
        }

        unordered_map<char, int> um;
        for (int i = 0; i < t.size(); i++) {
            if (um.find(t[i]) != um.end()) {
                um.insert(make_pair(t[i], 0));
            }

            um[t[i]]++;
        }

        int minLen = INT_MAX;
        int start = -1;
        int p1 = 0, p2 = 0, remain = t.size();
        for (; p2 < s.size(); p2++) {
            if (um.find(s[p2]) != um.end()) {
                um[s[p2]]--;
                if (um[s[p2]] >= 0) {
                    remain--;
                }
            }

            while (remain == 0) {
                if (p2 - p1 + 1 < minLen) {
                    minLen = p2 - p1 + 1;
                    start = p1;
                }

                if (um.find(s[p1]) != um.end()) {
                    um[s[p1]]++;
                    if (um[s[p1]] > 0) {
                        remain++;
                    }
                }

                p1++;
            }
        }

        return minLen != INT_MAX ? s.substr(start, minLen) : "";
    }    
};

int main () {
    Solution s;

    // Test 1:
    string s1 = "ADOBECODEBANC";
    string t1 = "ABC";
    cout << s.minWindow(s1, t1) << endl;

    // Test 2:
    string s2 = "AAAAABC";
    string t2 = "ABC";
    cout << s.minWindow(s2, t2) << endl;

    // Test 3:
    string s3 = "BACDCCBA";
    string t3 = "DDCA";
    cout << s.minWindow(s3, t3) << endl;

    // Test 4:
    string s4 = "BACDCCBA";
    string t4 = "AABB";
    cout << s.minWindow(s4, t4) << endl;

    // Test 5:
    string s5 = "BACDCCBA";
    string t5 = "BACC";
    cout << s.minWindow(s5, t5) << endl;

    // Test 6:
    string s6 = "aaaaaaaaaaaabbbbbcdd";
    string t6 = "abcdd";
    cout << s.minWindow(s6, t6) << endl;
}