#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// The idea was using DFS to backtrack.
// Note that we need an unordered_set to avoid duplicate mapping. (a.k.a. diff chars map to same value)

class Solution {
public:
    bool wordPatternMatch(string pattern, string s) {
        unordered_map<char, string> m;
        unordered_set<string> vis;
        return dfs(pattern, s, 0, 0, m, vis);
    }
private:
    bool dfs(
        string pattern, 
        string s,
        int pcurr,
        int scurr,
        unordered_map<char, string>& m,
        unordered_set<string>& vis) {
        if (pcurr == pattern.size() && scurr == s.size()) {
            return true;
        } else if (pcurr == pattern.size() && scurr != s.size()) {
            return false;
        } else if (pcurr != pattern.size() && scurr == s.size()) {
            return false;
        }
        
        char c = pattern[pcurr];

        if (m.find(c) != m.end()) {
            string match = m[c];
            if (scurr + match.size() - 1 >= s.size()) {
                return false;
            }

            if (match != s.substr(scurr, match.size())) {
                return false;
            } else {
                return dfs(pattern, s, pcurr + 1, scurr + match.size(), m, vis);
            }
        } else {
            for (int i = scurr; i < s.size(); i++) {
                string curr = s.substr(scurr, i - scurr + 1);
                if (vis.find(curr) != vis.end()) {
                    continue;
                }

                m.emplace(c, curr);
                vis.insert(curr);
                if (!dfs(pattern, s, pcurr + 1, i + 1, m, vis)) {
                    m.erase(c);
                    vis.erase(curr);
                } else {
                    return true;
                }
            }
        }
        
        return false;
    }
};

struct TestString
{
    string pattern;
    string s;
};

int main () {
    Solution s;
    TestString ts1 { .pattern = "abab", .s = "reblrebl" };
    TestString ts2 { .pattern = "ab", .s = "abcdef" };
    TestString ts3 { .pattern = "ab", .s = "rbrb" };
    TestString ts4 { .pattern = "ab", .s = "aa" };
    TestString ts5 { .pattern = "sucks", .s = "teezmmmmteez" };

    //cout << s.wordPatternMatch(ts1.pattern, ts1.s) << endl;
    //cout << s.wordPatternMatch(ts2.pattern, ts2.s) << endl;
    //cout << s.wordPatternMatch(ts3.pattern, ts3.s) << endl;
    //cout << s.wordPatternMatch(ts4.pattern, ts4.s) << endl;
    cout << s.wordPatternMatch(ts5.pattern, ts5.s) << endl;
}