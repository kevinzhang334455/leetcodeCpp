#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Note: the question (https://leetcode.com/problems/alien-dictionary/) mentioned
// that *words* are sorted lexicographically, rather than the *letters within the words*
// are sorted lexicographically.

class Solution {
public:
    string alienOrder(vector<string>& words) {
        words.erase(std::remove_if(
            words.begin(),
            words.end(),
            [](string word) { return word.empty(); }
        ), words.end());
        
        if (words.empty()) {
            return "";
        } else if (words.size() == 1) {
            return words[0];
        }
        
        unordered_map<char, unordered_set<char>> g;
        if (!build_directed_graph(words, g)) {
            return "";
        }
        
        string result;
        unordered_set<char> settled;
        unordered_set<char> visited;
        
        for (auto& word : words) {
            for (int i = 0; i < word.size(); i++) {
                if (settled.find(word[i]) == settled.end() && 
                    !dfs(word[i], g, visited, settled, result)) {
                    return "";
                }
            }
        }
        
        return result;
    }
private:
    bool build_directed_graph(
        const vector<string>& words,
        unordered_map<char, unordered_set<char>>& graph) {
        for (int i = 0; i < words.size() - 1; i++) {
            auto w1 = words[i]; auto w2 = words[i + 1];
            bool adj = false;
            for (int j = 0; j < std::min(w1.size(), w2.size()); j++) {
                if (w1[j] == w2[j]) {
                    continue;
                }
                
                if (graph.find(w1[j]) == graph.end()) {
                    graph.insert(make_pair(w1[j], unordered_set<char>()));
                }
                
                graph[w1[j]].insert(w2[j]);
                adj = true;
                break;
            }
            
            if (adj == false && w1.size() > w2.size()) {
                return false;
            }
        }
        
        return true;
    }
    
    bool dfs(
        char curr, 
        const unordered_map<char, unordered_set<char>>& g,
        unordered_set<char>& vis,
        unordered_set<char>& settled,
        string& res) {
        if (vis.find(curr) != vis.end()) {
            return false;
        } else if (settled.find(curr) != settled.end()) {
            return true;
        }
        
        if (g.find(curr) == g.end()) {
            res.insert(res.begin(), curr);
            settled.insert(curr);
            return true;
        }
        
        auto& edges = g.at(curr);
        vis.insert(curr);
        
        for (auto it = edges.begin(); it != edges.end(); it++) {
            if (!dfs(*it, g, vis, settled, res)) {
                return false;
            }
        }
        
        vis.erase(curr);
        res.insert(res.begin(), curr);
        settled.insert(curr);
        
        return true;
    }
};

int main () {
    Solution s;

    // test 0:
    vector<string> test0 = {"abc", "ab"};
    cout << s.alienOrder(test0) << endl;

    // test 1:   
    vector<string> test1 = {"wrt", "wrf", "er", "ett", "rftt"};
    cout << s.alienOrder(test1) << endl;

    // test 2:
    vector<string> test2 = {"xz", "zx"};
    cout << s.alienOrder(test2) << endl;

    // test3:
    vector<string> test3 = {"abc", "acd", "dd"};
    cout << s.alienOrder(test3) << endl;
}