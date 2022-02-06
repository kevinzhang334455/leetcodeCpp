#include "PrintUtil.hpp"
#include <vector>

using namespace std;

// find the longest reverse sequence, then find the first one doesn't satisify with this condition,
// call it pivot, then swap number in which 1) greater than pivot 2) within the sequence, with pivot
// number. then reverse the whole sequence.

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int N = nums.size();
        if (N == 0 || N == 1) {
            return;
        }

        int p = N - 1;

        for (; p > 0; p--) {
            if (nums[p - 1] < nums[p]) break;
        }

        // Invariant: p == 0 || nums[p - 1] >= nums[p];
        p--;

        if (p >= 0) {
            // swap with the number that is greater than pivot
            for (int i = N - 1; i > p;  i--) {
                if (nums[i] > nums[p]) {
                    std::swap(nums[i], nums[p]);
                    break;
                }
            }
        }

        for (int i = p + 1, j = N - 1; i < j; i++, j--) {
            std::swap(nums[i], nums[j]);
        }
    }
};

int main () {
    Solution s;
    vector<int> test1 = {1, 2, 3, 4}; // 1, 2, 4, 3
    vector<int> test2 = {1, 4, 3, 2}; // 2, 1, 3, 4
    vector<int> test3 = {1, 2, 4, 5, 3}; // 1, 2, 5, 3, 4
    vector<int> test4 = {4, 3, 2, 1}; // 1, 2, 3, 4
    vector<int> test5 = {1, 5, 4, 3, 2} ; // 2, 1, 3, 4, 5
    vector<int> test6 = {1, 1, 5}; // 1, 5, 1
    vector<int> test7 = {5, 1, 1}; // 1, 1, 5

    s.nextPermutation(test1);
    PrintUtil::printVectorOf(test1);

    s.nextPermutation(test2);
    PrintUtil::printVectorOf(test2);

    s.nextPermutation(test3);
    PrintUtil::printVectorOf(test3);

    s.nextPermutation(test4);
    PrintUtil::printVectorOf(test4);

    s.nextPermutation(test5);
    PrintUtil::printVectorOf(test5);

    s.nextPermutation(test6);
    PrintUtil::printVectorOf(test6);

    s.nextPermutation(test7);
    PrintUtil::printVectorOf(test7);
}