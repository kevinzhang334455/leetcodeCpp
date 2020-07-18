#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

// Given an unsorted array, find the maximum gap between the successive elements
// in its sorted form.

// E.g. [9, 1, 7, 5]
// Then return 4 as the maximum gap is 5 - 1 == 4.
// Try do this in O(n) time and O(n) space

// Key Algorithm:
// Consider sorted nums are on the axis. if you move a number closer to one of its two neighbors, 
// then this number has to be farther away from another one.
// Thus we can know the lower bound of the gap -- it should be the value where each number segment
// equally. e.g.:
// |*****|*****|*****|
// if you move any of the '|' in the middle, then the result will increase. So in this example, 5 is the
// minimum result we can get. 
// Thus, given an size N array where min value is Vmin and max value is Vmax, the lower bound of the result
// is CEIL{(Vmax - Vmin) / (N - 1)}.
// What we can do with this lower bound? Here we have the fun part: if you bucketize this array where the 
// bucket size equals to this lower bound, then the only thing you need to do is to check with the result
// with adjacent buckets by recording a max value and a min value which are in the bucket range. E.g.,

// Arr = {1, 4, 5, 9}. 
// After bucketize --
// B1: [min = 1, max = 4]
// B2: [min = 5, max = 5]
// B3: [min = 9, max = 9]
// Then result = B3.min - B2.max

// One note: no matter what the bucket size is (e.g. bucket size == 1), the number of buckets == N - 1. 
// So the time complexity is O(n) no matter what is the number distributions.

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        if (nums.empty() || nums.size() == 1) {
            return 0;
        }

        int maxElem = *std::max_element(nums.begin(), nums.end());
        int minElem = *std::min_element(nums.begin(), nums.end());
        int N = nums.size();

        int bucketSize = static_cast<int>(ceil((maxElem - minElem) * 1.0 / (N - 1)));
        auto minVals = vector<int>(N, INT_MAX);
        auto maxVals = vector<int>(N, INT_MIN);

        for (int i = 0; i < nums.size(); i++) {
            int idx = (nums[i] - minElem) / (bucketSize + 1);
            minVals[idx] = std::min(nums[i], minVals[idx]);
            maxVals[idx] = std::max(nums[i], maxVals[idx]);
        }

        int result = bucketSize;
        for (int p1 = 1, p2 = 0; p1 < N; ) {
            int num1 = minVals[p1];
            int num2 = maxVals[p2];

            if (num1 == INT_MAX) {
                p1++;
                continue;
            }

            result = std::max(num1 - num2, result);

            // Since minVal[p1] has value, maxValue[p1] must have a value as well.
            p2 = p1;
            p1 = p1 + 1;
        }

        return result;
    }
};

int main() {
    Solution s;

    vector<int> arr1 = {9, 1, 7, 5};
    cout << s.maximumGap(arr1) << endl;

    vector<int> arr2 = {75, -1, 3, 8, 94};
    cout << s.maximumGap(arr2) << endl;

    vector<int> arr3 = {100, 101, 102, 103, 104, 105};
    cout << s.maximumGap(arr3) << endl;

    vector<int> arr4 = {100, 101, 102, 103, 104, 105, 107};
    cout << s.maximumGap(arr4) << endl;

    vector<int> arr5 = {10, 20, 30, 40, 50};
    cout << s.maximumGap(arr5) << endl;

    vector<int> arr6 = {100, 1};
    cout << s.maximumGap(arr6) << endl;

    vector<int> arr7 = {102, 102, 102};
    cout << s.maximumGap(arr7) << endl;
}