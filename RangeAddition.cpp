#include "PrintUtil.hpp"
#include <vector>
#include <iostream>
using namespace std;

// https://leetcode.com/problems/range-addition/
// The basic idea here is for each updates mark the start index with +val
// and mark the end index with -val. Finally using prefix sum to build the
// answer.

class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> temp(length, 0);
        vector<int> ans(length, 0);
        for (int i = 0; i < updates.size(); i++) {
            int val = updates[i][2];
            temp[updates[i][0]] += val;

            // Note that [start, end] with increase with val so -val should be put
            // at index end + 1.
            if (updates[i][1] + 1 < length) {
                temp[updates[i][1] + 1] -= val;
            }
        }

        int sum = 0;
        for (int i = 0; i < length; i++) {
            sum += temp[i];
            ans[i] = sum;
        }

        return ans;
    }
};

int main () {
    Solution s;
    vector<vector<int>> updates = {{1,3,2},{2,4,3},{0,2,-2}};
    PrintUtil::printVectorOf(s.getModifiedArray(5, updates));
}