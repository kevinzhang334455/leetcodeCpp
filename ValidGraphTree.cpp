#include <vector>
#include <iostream>

using namespace std;

// https://leetcode.com/problems/graph-valid-tree/
// Given a set of undirect edges, determine whether this is a valid tree.

// Solution 1:
// DFS (topological sort) which can determine whether 1) it has cycles and 2) every node has been visited.

// Solution 2:
// Union Find where if parent and child belong to same set before merge child and parent to the same set.

class Solution1 {
public:
bool validTree(int n, vector<vector<int>>& edges) {
    vector<vector<int>> directedGraph(n);

    // Convert undirected graph to directed graph.
    for (auto edge : edges) {
        int n0 = edge[0];
        int n1 = edge[1];
        directedGraph[n0].push_back(n1);
        directedGraph[n1].push_back(n0);
    }

    vector<bool> vis(n, false);
    if (isCyclicGraph(directedGraph, 0, -1, vis)) return false;
    for (auto n : vis) {
        if (!n) {
            return false;
        }
    }

    return true;
}
private:
    bool isCyclicGraph(
        const vector<vector<int>>& directedGraph, 
        int child,
        int parent,
        vector<bool>& vis) {
            if (vis[child]) {
                return true;
            }

            vis[child] = true;

            for (auto edge : directedGraph[child]) {
                if (edge == parent) {
                    continue; // Basically this means we don't want to traverse the same edge.
                }

                if (isCyclicGraph(directedGraph, edge, child, vis)) {
                    return true;
                }
            }

            return false;
        }
};

class Solution2 {
public:
bool validTree(int n, vector<vector<int>>& edges) {

} 
};

int main () {
    
}