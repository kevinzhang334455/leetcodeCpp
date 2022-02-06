#include <vector>
#include <iostream>
using namespace std;

// Given an array of non-negative integers nums, you are initially positioned at the first index of the array.

// Each element in the array represents your maximum jump length at that position.

// Your goal is to reach the last index in the minimum number of jumps.

// You can assume that you can always reach the last index.

// Example 1:

// Input: nums = [2,3,1,1,4]
// Output: 2
// Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.

class Solution {
public:
    int jump(vector<int>& nums) {
        const int N = nums.size();
        
        if (N == 0 || N == 1) {
            return 0;
        }
        
        int ans = 1;
        int farthest = nums[0]; // farthest means what is the maximum reach if jump with at most `ans + 1` steps.
        int curr = farthest; // curr is defined as the maximum reach given jump 'ans' steps.
        
        for (int i = 1; i < nums.size(); i++) {
            if (i > curr) {
                ans++;
                curr = farthest;
            }
            
            farthest = max(farthest, min(nums[i] + i, N - 1));
        }
        
        return ans;
    }
};

int main () {
    Solution s;
    vector<int> nums = {2, 3, 1, 1, 4};
    cout << s.jump(nums) << endl;
}