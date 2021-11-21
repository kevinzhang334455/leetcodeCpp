#include <vector>
#include <iostream>
using namespace std;

/* 
You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an integer k.

Find the maximum profit you can achieve. You may complete at most k transactions.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

Example 1:

Input: k = 2, prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
Example 2:

Input: k = 2, prices = [3,2,6,5,0,3]
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3. 
*/

// Basic idea: suppose dp[i][j] means the maximum profit at day j for having i + 1 times of transaction
// *at most*.
// then dp[i][j] comes from either 1) dp[x][j] where x < i or 2) dp[x][j - 1] + T{y, i} where x <= y < i 
// The challenge here is how to get T{y, i}?

// Can T{y, i} get from Kadane algorithm? We can record the start of y as long as the accumulation > 0
// and then find the y.

/* 
--------------------------------------------------------------
K \ day | d0 = 3 | d1 = 2 | d2 = 6 | d3 = 5 | d4 = 0 | d5 = 3
--------------------------------------------------------------
 K = 1  |   0    |   0    |    4   |    4   |   4    |   4   |
 K = 2  |   0    |   0    |    4   |    4   |   4    |   7   | 

*/

// Basic Idea:
// Define dp[i][j] = the most profit at day j with i transactions at most.
// And on day j, we have two options: sell stock at day j or no.
// Define jj = the day when last time buy the stock. Then,
// dp[i][j] = max(dp[i][j - 1], prices[j] + dp[i - 1][jj] - prices[jj]) 
// where jj can be in range of [1..j-1].
// So, what we can do is that we can maintain the local variable
// prevLocalMax = dp[i - 1][jj] - prices[jj] for all jj = [1..j - 1]
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if (k <= 0 || prices.empty() || prices.size() == 1) {
            return 0;
        }

        vector<vector<int>> dp(k + 1, vector<int>(prices.size(), 0));
        for (int i = 1; i <= k; i++) {
            int prevLocalMax = -prices[0];
            for (int j = 1; j < prices.size(); j++) {
                dp[i][j] = max(dp[i][j - 1], prevLocalMax + prices[j]);
                prevLocalMax = max(prevLocalMax, dp[i - 1][j] - prices[j]);
            }
        }

        return dp.back().back();
    }
};

// Wrong Solution.
class Solution1 {
public:
    int maxProfit(int k, vector<int>& prices) {
        if (k <= 0 || prices.empty() || prices.size() == 1) {
            return 0;
        }

        vector<vector<int>> dp(k, vector<int>(prices.size(), 0));

        for (int i = 0; i < k; i++) {
            int start = 0, accumu = 0;

            for (int j = 1; j < prices.size(); j++) {
                int diff = prices[j] - prices[j - 1];
                if (diff + accumu < 0) {
                    start = j;
                    accumu = 0;
                } else {
                    accumu = accumu + diff;
                }

                if (j == 1) {
                    dp[i][j] = diff > 0 ? diff : 0;
                } else {
                    dp[i][j] = i == 0 ? 
                    max(dp[i][j - 1], accumu) : 
                    max(accumu + dp[i - 1][start], dp[i][j - 1]);
                }
            }
        }

        return dp.back().back();
    }
};

void Test(vector<int>& test, int k) {
    Solution s;
    cout << s.maxProfit(k, test) << endl;
}

int main () {
    vector<int> test1 = {2, 4, 1};
    vector<int> test2 = {3, 2, 6, 5, 0, 3};
    vector<int> test3 = {6, 1, 3, 2, 4, 7};

    // Test(test1, 2);
    // Test(test2, 2);
    Test(test1, 2);
}