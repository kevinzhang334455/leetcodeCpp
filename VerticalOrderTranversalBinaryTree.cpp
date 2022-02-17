#include "TreeNode.hpp"
#include "PrintUtil.hpp"
#include <vector>
#include <map>
#include <set>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        map<int, map<int, set<int>>> nodes;
        traverse(root, 0, 0, nodes);
        vector<vector<int>> ans;
        for (auto p : nodes) {
            vector<int> col;
            for (auto q : p.second) {
                col.insert(col.end(), q.second.begin(), q.second.end());
            }
            ans.push_back(col);
        }
        return ans;
    }
private:
    void traverse(TreeNode* root, int x, int y, map<int, map<int, set<int>>>& nodes) {
        if (root) {
            nodes[x][y].insert(root->val);
            traverse(root->left, x - 1, y + 1, nodes);
            traverse(root->right, x + 1, y + 1, nodes);
        }
    }
};

int main () {
    TreeNode* t1 = new TreeNode(3);
    TreeNode* t2 = new TreeNode(9);
    TreeNode* t3 = new TreeNode(20);
    TreeNode* t4 = new TreeNode(15);
    TreeNode* t5 = new TreeNode(7);

    t1->left = t2;
    t1->right = t3;
    t3->left = t4;
    t3->right = t5;

    Solution s;
    auto ans = s.verticalTraversal(t1);
    PrintUtil::printVectorVectorOf(ans);
}