#include <vector>
#include <iostream>
using namespace std;

// try with algorithm with O(NlgN).
// Basic Idea:
// Maintain an array tails[] such that tails[i] is the minimum element of all possible increasing 
// subsequences of length i + 1.

// Conlusion 1: tails[] has to be monotonically increaing.
// Proof: if there exists tails[i] > tails[i + 1]. Then tails[i + 1] has to be the minimum element of all
// increaing subsequence of length i + 1, which means tails[i + 1] should be put into tails[i]. 

// We can use the conclusion above to expedite our dynamic programming process. 

// In regular DP approach, given nums[i] we need to iterate all the dp[0..i) and determine the longest one
// by maximum{dp[0..i)} && nums[j] < nums[i].

// So in this approach, when we iterate nums[], we can rely on the conclusion and examine whether nums[i] 
// exceed the value of the current rightmost element in tails[] (which we can denote as tails[rightmost]),
// if it exceeds, we know that there is an optimal solution where LIS has a length of rightmost + 1. In same
// time, we need to update the tails[] array when iterate nums[]. Since this array is monotonic, we can use
// binary search to update so for each nums[i] the cost of updating tails[] is O(lgN), so the overall of time
// complexity is O(NlgN). 

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty() || nums.size() == 1) {
            return nums.size();
        }

        vector<int> tails(nums.size(), 0);
        int len = 0; // LIS length
        for (auto num : nums) {
            int begin = 0, end = len - 1;
            bool update = false;
            while (begin <= end) {
                int mid = begin + (end - begin) / 2;
                if (num < tails[mid] && (mid == 0 || num > tails[mid - 1])) {
                    tails[mid] = num;
                    update = true;
                    break;
                } else if (mid != 0 && num <= tails[mid - 1]) {
                    end = mid - 1;
                } else if (num >= tails[mid]) {
                    begin = mid + 1;
                }
            }

            if (!update && (len == 0 || tails[len - 1] < num)) {
                tails[len] = num;
                len++;
            }
        }

        return len;
    }
};

int main () {
    Solution s;

    // test 0:
    vector<int> test0 = {4,10,4,3,8,9};
    cout << s.lengthOfLIS(test0) << endl;

    // test 1:
    vector<int> test1 = { 1, 2, 3, 4, 5 };
    cout << s.lengthOfLIS(test1) << endl;

    // test 2:
    vector<int> test2 = { 5, 4, 3, 2, 1 };
    cout << s.lengthOfLIS(test2) << endl;

    // test 3:
    vector<int> test3 = {3, 2, 5, 1, 6, 7, -1};
    cout << s.lengthOfLIS(test3) << endl;

    // test 4:
    vector<int> test4 = {3, 2, 1, 4, -1, 5, 6, 7, 8};
    cout << s.lengthOfLIS(test4) << endl;

    // test 5:
    vector<int> test5 = {3, 2, 7, 7, 7};
    cout << s.lengthOfLIS(test5) << endl;
}