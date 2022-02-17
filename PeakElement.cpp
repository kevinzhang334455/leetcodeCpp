#include <vector>
#include <iostream>

using namespace std;

// A peak element is an element that is strictly greater than its neighbors.

// Given an integer array nums, find a peak element, and return its index. 
// If the array contains multiple peaks, return the index to any of the peaks.

// You may imagine that nums[-1] = nums[n] = -∞.
// You must write an algorithm that runs in O(log n) time.

// Example 1:

// Input: nums = [1,2,3,1]
// Output: 2
// Explanation: 3 is a peak element and your function should return the index number 2.

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        if (nums.empty()) {
            return -1;
        }

        int begin = 0, end = nums.size() - 1;
        while (begin < end) {
            int mid = begin + (end - begin) / 2;
            if ((mid == 0 || nums[mid] > nums[mid - 1]) && 
            (mid == nums.size() - 1 || nums[mid] > nums[mid + 1])) {
                return nums[mid];
            } else if (mid != 0 && nums[mid - 1] > nums[mid]) {
                end = mid - 1;
            } else {
                begin = mid + 1;
            }
        }

        // Invariant -> begin == end;
        return nums[begin];
    }
};

int main () {
    vector<int> test = {2, 1, 3, 2};
    Solution s;
    cout << s.findPeakElement(test) << endl;
}