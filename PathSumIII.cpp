#include "TreeNode.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

/* 
Given the root of a binary tree and an integer targetSum, return the number of paths where the sum of the values along the path equals targetSum.
The path does not need to start or end at the root or a leaf, but it must go downwards (i.e., traveling only from parent nodes to child nodes).
 */

// https://leetcode.com/problems/path-sum-iii/
// Solution 1 (origin thought): Use DFS to backtrack sum. Should be do-able but not that much
// elegant. Also the below solution1 was not correct.

// Solution 2: Prefix Sum.


class Solution1 {
public:
    int pathSum(TreeNode* root, int targetSum) {
        int result = 0;
        
        if (root != nullptr) {
            pathSumHelper(root, targetSum, result);
        }
        
        return result;
    }
    
private:
    pair<unordered_map<int, int>, unordered_map<int, int>> pathSumHelper(
    TreeNode* root, int targetSum, int& result) {
        if (root->val == targetSum) {
            result++;
        }
        
        pair<unordered_map<int, int>, unordered_map<int, int>> res;
        int target = targetSum - root->val;
        unordered_map<int, int> nextLeftRes, nextRightRes;
        
        if (root->left != nullptr) {
            auto leftRes = pathSumHelper(root->left, targetSum, result);
            result += getSubRes(leftRes.first, target) + getSubRes(leftRes.second, target);
            nextLeftRes = rekey(leftRes.first, root->val);
        }
        
        if (root->right != nullptr) {
            auto rightRes = pathSumHelper(root->right, targetSum, result);
            result += getSubRes(rightRes.first, target) + getSubRes(rightRes.second, target);
            nextRightRes = rekey(rightRes.second, root->val);
        }
        
        if (nextLeftRes.find(root->val) == nextLeftRes.end()) {
            nextLeftRes.emplace(root->val, 0);
        }
        
        nextLeftRes[root->val]++;

        if (nextRightRes.find(root->val) == nextRightRes.end()) {
            nextRightRes.emplace(root->val, 0);
        }
        
        nextRightRes[root->val]++;     

        res.first = nextLeftRes;
        res.second = nextRightRes;
        
        return res;
    }
    
    int getSubRes(const unordered_map<int, int>& vals, int target) {
        if (vals.find(target) != vals.end()) {
            return vals.at(target);
        } else {
            return 0;
        }
    }
    
    unordered_map<int, int> rekey(const unordered_map<int, int>& vals, int rootVal) {
        unordered_map<int, int> res;
        for (const auto& [k, v] : vals) {
            res.emplace(k + rootVal, v);
        }
        
        return res;
    }
};

class Solution2 {
public:
    int pathSum(TreeNode* root, int targetSum) {
        unordered_map<int, int> prefixMap;
        int currSum = 0;
        int result = 0;
        if (root != nullptr) {
            pathSumSolver(root, currSum, targetSum, prefixMap, result);
        }

        return result;
    }
private:
    void pathSumSolver(TreeNode* curr, int currSum, int targetSum, unordered_map<int, int> prefixMap, int& result) {
        currSum += curr->val;

        // Case 1: there is a match from root->curr
        if (currSum == targetSum) {
            result++;
        }

        // Case 2: there is an existing path (node) where root->node == currSum - target
        // then the node->curr is target.
        if (prefixMap.find(currSum - targetSum) != prefixMap.end()) {
            result += prefixMap[currSum - targetSum];
        }

        if (prefixMap.find(currSum) == prefixMap.end()) {
            prefixMap.emplace(currSum, 0);
        }

        prefixMap[currSum]++;
        if (curr->left != nullptr) {
            pathSumSolver(curr->left, currSum, targetSum, prefixMap, result);
        }

        if (curr->right != nullptr) {
            pathSumSolver(curr->right, currSum, targetSum, prefixMap, result);
        }
    }
};

TreeNode* MakeTest1()
{
    TreeNode* n1 = new TreeNode(10);
    TreeNode* n2 = new TreeNode(5);
    TreeNode* n3 = new TreeNode(-3);
    TreeNode* n4 = new TreeNode(3);
    TreeNode* n5 = new TreeNode(2);
    TreeNode* n6 = new TreeNode(11);
    TreeNode* n7 = new TreeNode(3);
    TreeNode* n8 = new TreeNode(-2);
    TreeNode* n9 = new TreeNode(1);  
    n1->left = n2;
    n1->right = n3;
    n2->left = n4;
    n2->right = n5;
    n3->right = n6;
    n4->left = n7;
    n4->right = n8;
    n5->right = n9;

    return n1;
}

TreeNode* MakeTest2() {
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n2 = new TreeNode(-2);
    TreeNode* n3 = new TreeNode(-3);
    n1->left = n2;
    n2->right = n3;

    return n1;   
}

int main ()
{
    Solution1 s1;
    Solution2 s2;
    TreeNode* t1 = MakeTest1();
    TreeNode* t2 = MakeTest2();

    cout << s2.pathSum(t1, 8) << endl;
    cout << s2.pathSum(t2, -1) << endl;
}