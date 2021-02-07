#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

/* Given an array nums which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays.

Write an algorithm to minimize the largest sum among these m subarrays.

Example 1:

Input: nums = [7,2,5,10,8], m = 2
Output: 18
Explanation:
There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8],
where the largest sum among the two subarrays is only 18. */

// Hint: this can use binary search...The correct answer should fall in between
// the number of arrays (which is m + 1) and the sum(nums). 

// The main idea is following:
// for each {mid}, we can try test whether it can split to m + 1 subarrays where the sums of sub arrays
// is close but less than {mid}.
// If the number of subarrays is less than m, which means the mid is too big, then we need to move
// the mid to left.
// If the number of subarrays more than m, which means the mid is too small, then we need to move
// the mid to right.

// The gist of this algorithm is that the answer has a lower bound and a upper bound, so we can just
// do a binary search between the lower bound and upper bound. 

class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        long long l = *std::max_element(nums.begin(), nums.end());
        long long r = std::accumulate(nums.begin(), nums.end(), (long long) 0);

        // the answer should fall with [l, r] and no possible that the answer is empty.
        // and if we want to find the minimum one the answer should be l.

        while (l <= r) {
            long long mid = l + (r - l) / 2;
            int arrayCount = CountSubArrays(nums, mid);
            if (arrayCount <= m) {
                // In this case it means the mid is either too large (when arrayCount < m) or is
                // sub-optimal (when arrayCount == m && l < r). 
                r = mid - 1;
            } else {
                // In this case we know that this is too small and would not be a sub-optmial solution,
                // move l to mid + 1 and continue to search.
                l = mid + 1;
            }
        }

        return l;
    }

private:
    int CountSubArrays(vector<int>& nums, int targetSum) {
        int count = 1, sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            if (sum > targetSum) {
                sum = nums[i];
                count++;
            }
        }

        return count;
    }
};

int main ()
{
    Solution s;

    vector<int> test1 = {7,2,5,10,8};
    cout << s.splitArray(test1, 2) << endl;

    vector<int> test2 = {1,2,3,4,5};
    cout << s.splitArray(test2, 2) << endl;

    vector<int> test3 = {1, 4, 4};
    cout << s.splitArray(test3, 3) << endl;

    vector<int> test4 = {2, 3, 1, 1, 1, 1, 1};
    cout << s.splitArray(test4, 5) << endl;
}