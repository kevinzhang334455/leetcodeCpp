#include "PrintUtil.hpp"
#include <iostream>
#include <vector>
#include <set>

// The basis idea should be similar to "Find Median in Data Stream."
// The difference is that how to remove previous elements if they are out of window.

// The target is time complexity is O(log(K) * N) where K is the window size.

// I don't know how to do this in first place and I copied 
// https://leetcode.com/problems/sliding-window-median/discuss/96392/C%2B%2B-95-ms-single-multiset-O(n-*-log-n)
// So basically the idea is that we need to maintain a median iterator and update the iterator when
// 1) Purge the left from window, and 2) add new element from right. 

using namespace std;

class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> res;
        multiset<int> window(nums.begin(), nums.begin() + k);
        auto mid = std::next(window.begin(), k / 2);

        for (int i = k; i <= nums.size(); i++) {
            res.push_back((*mid + *std::next(mid, k % 2 - 1)) / 2.0);

            if (i == nums.size()) {
                return res;
            }

            // Purge 
            if (nums[i - k] == *mid) {
                mid = window.erase(mid);
            } else {
                window.erase(window.find(nums[i - k]));
                if (nums[i - k] < *mid) {
                    mid++;
                }
            }

            if (nums[i] == *mid) {
                mid = window.insert(mid, nums[i]);
            } else {
                window.insert(nums[i]);

                if (nums[i] < *mid) {
                    mid--;
                }
            }
        }

        return res;
    }
};

int main()
{
    Solution s;
    PrintUtil printUtil;

    vector<int> test1 = { 5, 1, 3, 8, 2, 6, 9 };
    vector<int> test2 = { 3, 1, 3, 5, 7, 5, 3 };
    vector<int> test3 = { 1, 2 };

    // printUtil.printVectorOf<double>(s.medianSlidingWindow(test1, 3));
    // printUtil.printVectorOf<double>(s.medianSlidingWindow(test2, 4));
    printUtil.printVectorOf<double>(s.medianSlidingWindow(test3, 1));
}