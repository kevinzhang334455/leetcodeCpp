#include "PrintUtil.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <stack>

using namespace std;

// Initial thought: to use balanced tree (e.g. set or map) to insert each element and then find
// the previous node by finding the previous iterator.

// Drawback is that it's hard to tell whether the prev iter is the previous element.

// A better solution is to use stack.

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        const int N = nums.size();
        vector<int> results(N, -1);
        stack<int> st;

        for (int i = 0; i < 2 * N - 1; i++) {
            while (!st.empty() && nums[st.top()] < nums[i % N]) {
                results[st.top()] = nums[i % N];
                st.pop();
            }

            if (i < N) {
                st.push(i % N);
            }
        }

        return results;
    }
};

int main() {
    Solution s;
    vector<int> test1 = {1, 2, 1};
    vector<int> test2 = {4, 3, 2};
    vector<int> test3 = {5, 4, 3, 2, 1}; // this should make the change to while loop.
    PrintUtil::printVectorOf<int>(s.nextGreaterElements(test1));
    PrintUtil::printVectorOf<int>(s.nextGreaterElements(test2));
    PrintUtil::printVectorOf<int>(s.nextGreaterElements(test3));
}