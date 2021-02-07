#include <vector>
#include <iostream>
#include <deque>

using namespace std;

// leetcode 239

/* 
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5  // broken for idea 1
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7 
 */

// The initial idea is to maintain a monopoly decrasing queue so that the maximum would be always the head of the queue.
// Initially I was thinking two pointers, which is wrong, because when new element comes it will break this property.

// The correct way to do is that We need to maintain a decreasing deque where the left == max(left, iterator_pos - k + 1)
// and right == min(iterator_pos, right)

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if (k == 1) {
            return nums;
        } else if (k >= nums.size()) {
            return vector<int>(1, *std::max_element(nums.begin(), nums.end()));
        }

        vector<int> result;
        deque<int> dq;
        for (int i = 0; i < nums.size(); i++) {
            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }

            dq.push_back(i);

            if (dq.front() < i - k + 1) {
                dq.pop_front();
            }

            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }

        return result;
    }
};

void Test(vector<int>& testCase, int k) {
    Solution s;
    auto res = s.maxSlidingWindow(testCase, k);
    for (int x : res) {
        cout << x << ' '; 
    }

    cout << endl;
}

int main () {
    vector<int> test1 = { 1, 3, -1, -3, 5, 3, 6, 7 };
    vector<int> test2 = { 1, -1, 1, 3, 2, -1, -2, -3 };
    vector<int> test3 = { 1, 2, 3, 4, 5 };
    vector<int> test4 = { 5, 4, 3, 2, 1 };
    vector<int> test5 = { 5, 5, 5, 5, 5};
    Test(test1, 3);
    Test(test1 ,4);
    Test(test2, 3);
    Test(test2, 4);
    Test(test3, 2);
    Test(test4, 2);
    Test(test4, 5);
    Test(test5, 2);
}