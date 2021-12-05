#include "PrintUtil.hpp"
#include <vector>
#include <iostream>
#include <unordered_set>
#include <queue>

using namespace std;

// The general idea here is that we start traversal from leaf nodes, then
// rule-out the leaf nodes as they cannot be the answers. The last 1 or 2
// nodes are the answers as they traversed the most longest path.

// That's being said, we can always see the base case as 1) o--o--o or 2)
// o--o--o--o

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        vector<int> ans;
        if (n == 1) {
            ans.push_back(n);
            return ans;
        } else if (n == 2) {
            ans.push_back(edges.at(0).at(0));
            ans.push_back(edges.at(0).at(1));
            return ans;
        }

        vector<unordered_set<int>> g(n, unordered_set<int>());
        for (auto edge : edges) {
            g[edge[0]].emplace(edge[1]);
            g[edge[1]].emplace(edge[0]);
        }

        vector<int> leaves;
        int leafNodeCnt = 0;
        for (int i = 0; i < n; i++) {
            if (g[i].size() == 1) {
                leaves.push_back(i);
            }
        }

        // Invariant: the elements in the queue are always leaf-nodes.
        // The terminate condition would be for every node we peel it
        // till it becomes a leaf node.

        // Note: seems we cannot use queue as queue would only pop 1 leaf
        // at one time. Then for case o--o--o--o it's impossible to determine
        // all of these two (correct) records at same time.
        int remain = n;

        while (remain > 2) {
            remain -= leaves.size();
            vector<int> next_leaves;
            for (auto leaf : leaves) {
                int adj = *g[leaf].begin();
                g[leaf].erase(adj);
                g[adj].erase(leaf);
                if (g[adj].size() == 1) {
                    next_leaves.push_back(adj);
                }
            }

            leaves = next_leaves;
        }

        return leaves;
    }
};

struct Test
{
    int n;
    vector<vector<int>> edges;
    Solution s;

    Test(
        Solution s, 
        int num, 
        const vector<vector<int>>& edges): 
        s(s), n(num), edges(edges) {}

    void Run() {
        PrintUtil::printVectorOf(s.findMinHeightTrees(n, edges));
    }
};

int main ()
{
    Solution s;
    Test test1(s, 6, {{3,0},{3,1},{3,2},{3,4},{5,4}});
    Test test2(s, 4, {{1,0},{1,2},{1,3}});

    test1.Run();
    test2.Run();
}