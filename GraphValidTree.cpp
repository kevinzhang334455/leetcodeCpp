#include <vector>
#include <unordered_set>
#include <iostream>
using namespace std;

/* You have a graph of n nodes labeled from 0 to n - 1. 
You are given an integer n and a list of edges where edges[i] = [ai, bi] 
indicates that there is an undirected edge between nodes ai and bi in the graph.
Return true if the edges of the given graph make up a valid tree, and false 
otherwise. */

// General idea:
// The definition of tree: 1) all n nodes are connected. 2) n - 1 edges in which
// there is only 1 path from any two nodes. 3) Given the graph is un-directed
// graph, it means there is no cycle among two connected nodes. So, we can use
// topological sort (DFS) to determine whether this is a valid tree. 

class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        vector<unordered_set<int>> g(n, unordered_set<int>());
        for (auto edge : edges) {
            g[edge.at(0)].insert(edge[1]);
            g[edge.at(1)].insert(edge[0]);
        }

        vector<bool> vis(n, false);
        unordered_set<int> curr_path;
        
        // Tree should be fully connected graph. Thus, starting from one node should be 
        // sufficient.
        if (!topoSort(g, -1, 0, vis, curr_path)) {
            return false;
        }
        
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                return false;
            }
        }

        return true;
    }

private:
    bool topoSort(
        const vector<unordered_set<int>>& g,
        int prev_node,
        int curr_node,
        vector<bool>& vis,
        unordered_set<int>& curr_path) {
            if (vis[curr_node]) {
                return true;
            }
        
            if (curr_path.find(curr_node) != curr_path.end()) {
                return false; // a cycle detected thus return false.
            }

            curr_path.insert(curr_node);
            for (auto it = g[curr_node].begin(); it != g[curr_node].end(); it++) {
                int adj = *it;
                if (adj == prev_node) {
                    continue;
                }

                if (!topoSort(g, curr_node, adj, vis, curr_path)) {
                    return false;
                }
            }

            curr_path.erase(curr_node);
            vis[curr_node] = true;

            return true;
    }
};

struct Test {
    Solution s;
    int n;
    vector<vector<int>> edges;
    Test(Solution s, int n, const vector<vector<int>>& edges) : 
    s(s), 
    n(n),
    edges(edges) {}

    void Run () {
        cout << s.validTree(n, edges) << endl;
    }
};

int main () {
    Solution s;
    Test test1(s, 5, {{0,1},{0,2},{0,3},{1,4}});
    Test test2(s, 5, {{0,1},{1,2},{2,3},{1,3},{1,4}});
    Test test3(s, 5, {{0,1},{1,2},{2,3},{1,3}});
    test1.Run();
    test2.Run();
    test3.Run();
}