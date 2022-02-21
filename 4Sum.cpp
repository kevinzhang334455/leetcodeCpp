#include "PrintUtil.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// [2, 2, 2, 2, 2 ,3]

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> ans;
        if (nums.empty()) {
            return ans;
        }

        int N = nums.size();
        if (N < 4) {
            return ans;
        }

        sort(nums.begin(), nums.end());
        for (int i = 0; i < N - 3; i++) {
            if (i != 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            for (int j = i + 1; j < N - 2; j++) {
                if (j != i + 1 && nums[j] == nums[j - 1]) {
                    continue;
                }

                int two_sum_target = target - nums[i] - nums[j];
                for (int k = j + 1, l = N - 1; k < l; ) {
                    if (k != j + 1 && nums[k] == nums[k - 1]) {
                        k++;
                        continue;
                    }

                    if (nums[k] + nums[l] == two_sum_target) {
                        vector<int> temp = {nums[i], nums[j], nums[k], nums[l]};
                        ans.push_back(temp);
                        k++; l--;
                    } else if (nums[k] + nums[l] < two_sum_target) {
                        k++;
                    } else {
                        l--;
                    }
                }
            }
        }

        return ans;
    }
};

struct TestData
{
    vector<int> nums;
    int target;
    TestData(vector<int> nums, int target): nums(nums), target(target) {}
};

int main () {
    TestData t1({2,2,2,2,2,3}, 8);
    TestData t2({1,0,-1,0,-2,2}, 0);
    Solution s;
    PrintUtil::printVectorVectorOf(s.fourSum(t1.nums, t1.target));
    PrintUtil::printVectorVectorOf(s.fourSum(t2.nums, t2.target));
}