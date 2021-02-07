#include "TreeNode.hpp"
#include <queue>
#include <string>
#include <sstream>

using namespace std;

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string result;
        if (root == nullptr) {
            return result;
        }
        
        queue<TreeNode* > q;
        q.push(root);
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            
            if (curr != nullptr) {
                result += to_string(curr->val);
                q.push(curr->left);
                q.push(curr->right);
            } else {
                result.append(1, '#');
            }
            
            if (!q.empty()) {
                result.append(1, ',');
            }
        }
        
        return result;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) {
            return nullptr;
        }
        
        stringstream ss(data);
        vector<string> nodes;
        while (ss.good()) {
            string node;
            getline(ss, node, ',');
            nodes.push_back(node);
        }
        
        TreeNode* root = new TreeNode(stoi(nodes[0]));
        queue<TreeNode* > q;
        q.push(root);
        int i = 1;
        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();
            if (curr != nullptr) {
                TreeNode* leftNode = nodes[i][0] != '#' ? new TreeNode(stoi(nodes[i])) : nullptr;
                i = i + 1;
                TreeNode* rightNode = nodes[i][0] != '#' ? new TreeNode(stoi(nodes[i])) : nullptr;
                i = i + 1;
                curr->left = leftNode;
                curr->right = rightNode;
                q.push(leftNode);
                q.push(rightNode);
            }
        }
        
        return root;
    }
};

int main () {
    Codec codec;

    // Test 1
    TreeNode* n1 = new TreeNode(2);
    TreeNode* n2 = new TreeNode(1);
    TreeNode* n3 = new TreeNode(3);
    TreeNode* n4 = new TreeNode(4);

    n1->left = n2;
    n2->right = n3;
    n1->right = n4;

    auto* deserializedTreeNode = codec.deserialize(codec.serialize(n1));
}