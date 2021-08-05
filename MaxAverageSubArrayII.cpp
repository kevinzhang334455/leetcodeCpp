#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/* You are given an integer array nums consisting of n elements, and an integer k.

Find a contiguous subarray whose length is greater than or equal to k that has the maximum average value and return this value. Any answer with a calculation error less than 10-5 will be accepted.

 

Example 1:

Input: nums = [1,12,-5,-6,50,3], k = 4
Output: 12.75000
Explanation:
- When the length is 4, averages are [0.5, 12.75, 10.5] and the maximum average is 12.75
- When the length is 5, averages are [10.4, 10.8] and the maximum average is 10.8
- When the length is 6, averages are [9.16667] and the maximum average is 9.16667
The maximum average is when we choose a subarray of length 4 (i.e., the sub array [12, -5, -6, 50]) which has the max average 12.75, so we return 12.75
Note that we do not consider the subarrays of length < 4.
Example 2:

Input: nums = [5], k = 1
Output: 5.00000
 

Constraints:

n == nums.length
1 <= k <= n <= 104
-104 <= nums[i] <= 104 */

// Initial thought: This problem should use two pointer and use greedy approach.

class Solution1 {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int sum = 0;
        int p2 = 0;

        for (; p2 < min(k, static_cast<int>(nums.size())); p2++) {
            sum += nums[p2];
        }

        double currentAvg = calcAvg(sum, p2);
        double result = currentAvg;

        if (p2 == nums.size()) {
            return result;
        }

        for (int p1 = 0; p2 < nums.size(); ) {
            if (cast(nums[p1]) < result) {
                sum -= nums[p1];
                p1++;

                if (p2 - p1 < k) {
                    sum += nums[p2];
                    p2++;
                }

            } else {
                sum += nums[p2];
                p2++;
            }

            currentAvg = calcAvg(sum, p2 - p1);
            result = max(result, currentAvg);
        }

        return result;
    }
private:
    double calcAvg(int sum, int count) {
        return static_cast<double>(sum * 1.0 / count);
    }

    double cast(int num) {
        return static_cast<double>(num * 1.0);
    }
};

// The above approach is wrong see test case {7, 4, 5, 8, 8, 3, 9, 8, 7, 6}, and N = 7;
// The maximum subset is {8, 8, 3, 9, 8, 7, 6} which has average of 7 but the above approach has 6.55
// and the subset is {7, 4, 5, 8, 8, 3, 9, 8, 7}, in which the challenge is how to purge 4, 5, and add
// 6 to form a higher average even if 7 is first (and above avg 6.55). 
// The right approach might be using a deque so that
// when right hand side > left hand side the lhs can be purged. 

int main () {
    Solution1 s1;

    vector<int> test1 = {30, 1, 2, 1, 26};
    cout << s1.findMaxAverage(test1, 3) << endl;

    vector<int> test2 = {11, 12, 13, 9, 8};
    cout << s1.findMaxAverage(test2, 3) << endl;

    vector<int> test3 = {92, 35, 1, 44, 335};
    cout << s1.findMaxAverage(test3, 3) << endl;

    vector<int> test4 = {3, 6, 0, 1, 8, 0};
    cout << s1.findMaxAverage(test4, 3) << endl;

    vector<int> test5 = {1, 12, -5, -6, 50, 3};
    cout << s1.findMaxAverage(test5, 4) << endl;

    vector<int> test6 = {7, 4, 5, 8, 8, 3, 9, 8, 7, 6};
    cout << s1.findMaxAverage(test6, 7) << endl;
}