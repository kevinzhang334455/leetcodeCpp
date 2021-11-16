#include "TreeNode.hpp"
#include <algorithm>

// The idea here is the post-order traversal. 
// First you can think there is no limitation, that's being said, it will be 
// a tree sum (for all nodes) problem. Then, think back to the origin problem, 
// basically you can think whether the current node should be selected after
// process the left sub-tree and right sub-tree. The current node can be selected
// *only if* neither the direct left node nor direct right node are selected.
// Then return the current result with selected and unselected result.

// time complexity O(n), space complexity O(n).

class Solution {
    struct ResType {
        int RootOn;
        int RootOff;
        ResType(): RootOff(0), RootOn(0) {}
    };

public:
    int rob(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        
        int global = 0;
        robHelper(root, global);
        
        return global;
    }
private:
    ResType robHelper(
        TreeNode* curr, 
        int& global) {
        ResType result, left, right;
        if (curr->left != nullptr) {
            left = robHelper(curr->left, global);
        }

        if (curr->right != nullptr) {
            right = robHelper(curr->right, global);
        }

        result.RootOff = std::max(left.RootOn, left.RootOff) 
        + std::max(right.RootOn, right.RootOff);

        result.RootOn = curr->val + left.RootOff + right.RootOff;

        global = std::max(result.RootOn, result.RootOff);
        return result;
    }
};

int main () {

}