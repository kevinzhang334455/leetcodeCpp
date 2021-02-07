#include "Node.hpp"

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        
        unordered_map<Node*, Node*> hm;
        queue<Node* > q;
        
        hm.insert(make_pair(node, new Node(node->val)));
        q.push(node); // put every node in the hashmap.

        while (!q.empty()) {
            Node* top = q.front();
            q.pop();

            Node* replicatedTop = hm[top];
            for (int i = 0; i < top->neighbors.size(); i++) {
                Node* curr = top->neighbors[i];

                if (hm.find(curr) == hm.end()) {
                    // Unvisited Node.
                    hm.insert(make_pair(curr, new Node(curr->val)));
                    q.push(curr);
                }

                Node* replicatedCurr = hm[curr];
                replicatedTop->neighbors.push_back(replicatedCurr);
            }
        }
        
        return hm[node];
    }
};

int main () {
    // Undirected, cyclic graph.
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    
    // Build Adjacencies
    n1->neighbors.push_back(n2);
    n1->neighbors.push_back(n4);
    n2->neighbors.push_back(n1);
    n2->neighbors.push_back(n3);
    n3->neighbors.push_back(n2);
    n3->neighbors.push_back(n4);
    n4->neighbors.push_back(n3);
    n4->neighbors.push_back(n1);

    Solution s;
    Node* node = s.cloneGraph(n1);
    int a = 0;
}