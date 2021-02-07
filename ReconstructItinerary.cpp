#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <iostream>


using namespace std;
using strpq = priority_queue<string, vector<string>, std::greater<string> >;

// Leetcode 332: Reconstruct Itinerary
// Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], 
// reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK. 
// Thus, the itinerary must begin with JFK.

// E.G:
// Input: [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
// Output: ["JFK", "MUC", "LHR", "SFO", "SJC"]

// The problem can be traversed to Euler Path (where each edge needs to be tranversed by exactly once).

class Solution {
public:
    vector<string> findItinerary(vector<vector<string> >& tickets) {
        vector<string> result;
        auto graph = build_graph(tickets);
        if (graph.empty()) {
            return result;
        }

        string curr_loc = "JFK";
        dfs(curr_loc, graph, result);
        return result;
    }

private:
    unordered_map<string, strpq> build_graph(vector<vector<string> >& tickets) {
        unordered_map<string, strpq> graph;
        for (auto ticket : tickets) {
            if (graph.find(ticket[0]) == graph.end()) {
                graph.insert(make_pair(ticket[0], strpq()));
            }

            graph[ticket[0]].push(ticket[1]);
        }

        return graph;
    }

    void dfs(
        string curr_loc,
        unordered_map<string, strpq>& g, 
        vector<string>& result) {
        while (g.find(curr_loc) != g.end() && !g[curr_loc].empty()) {
            auto next = g[curr_loc].top();
            
            g[curr_loc].pop(); // Since we remove each edge before proceed with DFS so that we don't have 
                               // to use unordered_set to record the visited nodes.

            dfs(next, g, result);
        }

        // Note that DFS is in reverse order so that the correct edge to insert is the first element in the
        // list as the oldest one of tranversed elements.
        if (result.empty()) {
            result.push_back(curr_loc);
        } else {
            result.insert(result.begin(), curr_loc);
        }
    }
};

void print (vector<string> result) {
    for (auto res : result) {
        cout << res << " ";
    }

    cout << endl;
}

int main () {
    Solution s;
    vector<vector<string>> test1 = {{"JFK", "SFO"}, {"SFO", "JFK"}};
    vector<vector<string>> test2 = {{"JFK", "SFO"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"JFK", "ZXX"}};
    vector<vector<string>> test3 = {{"JFK","SFO"}, {"JFK","ATL"}, {"SFO","ATL"}, {"ATL","JFK"}, {"ATL","SFO"}};
    vector<vector<string>> test4 = {{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}};
    vector<vector<string>> test5 = {{"JFK","KUL"},{"JFK","NRT"},{"NRT","JFK"}};
    vector<vector<string>> test6 = {{"JFK", "A"}, {"A", "B"}, {"B", "A"}, {"A", "C"}, {"A", "D"}, {"D", "A"}};

    print(s.findItinerary(test1));
    print(s.findItinerary(test2));
    print(s.findItinerary(test3));
    print(s.findItinerary(test4));
    print(s.findItinerary(test5));
    print(s.findItinerary(test6));
}