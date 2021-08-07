#include <iostream>
#include <vector>

using namespace std;

/* You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it represented by an array nums. You are asked to burst all the balloons.

If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins. If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a balloon with a 1 painted on it.

Return the maximum coins you can collect by bursting the balloons wisely.

Example 1:

Input: nums = [3,1,5,8]
Output: 167
Explanation:
nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
Example 2:

Input: nums = [1,5]
Output: 10 */

// Original thought -- thinking dp[i][j] would be the sub-problem of origin problem and get max from there
// The thinking is right however it's hard to think about the transformation function -- e.g. [3, 1, 5].
// If you burst first [1] then how to form the sub-problem of [3, 5]? You don't have the sub-problem
// for non-consecutive array which is newly formed.

// So this just needs a bit trick here -- to think which is going to burst last. And think dp[i][j] is
// the maximum points you can get for [left][i...j][right]. Then dp[i][j] = 
// max(dp[i][w-1] + w * left * right + dp[w+1][j]), in which the left and right for dp[i][w-1] is left, w
// in respectively. So sometime you just can think reversely about the graph and see what we can do from
// there.

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        vector<vector<int>> dp(nums.size(), vector<int>(nums.size(), 0));
        for (int l = 1; l <= nums.size(); l++) {
            for (int i = 0; i + l - 1 < nums.size(); i++) {
                int left = i != 0 ? nums[i - 1] : 1;
                int right = i + l != nums.size() ? nums[i + l] : 1;
                int j = i + l - 1;
                for (int w = i; w < i + l; w++) {
                    if (l == 1) {
                        dp[i][j] = nums[i] * left * right;
                        continue;
                    }

                    int lastBurstPoints = nums[w] * left * right;
                    int leftPoints = w != i ? dp[i][w - 1] : 0;
                    int rightPoints = w != i + l - 1 ? dp[w + 1][j] : 0;
                    int curr = lastBurstPoints + leftPoints + rightPoints;

                    dp[i][j] = max(curr, dp[i][j]);
                }
            }
        }

        return dp[0][nums.size() - 1];
    }
};

int main () {
    Solution s;
    vector<int> test1 = { 3, 1, 5, 8 };

    cout << s.maxCoins(test1) << endl;
}