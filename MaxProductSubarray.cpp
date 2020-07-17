#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {      
        if (nums.empty())
            return 0;
        
        int localMax = 1;
        int localMin = 1;
        
        // Buggy: cannot assume the result > 0.
        // int result = 1;

        int result = INT_MIN;
        
        for (int i = 0; i < nums.size(); i++) {
            int prevMax = localMax;
            int prevMin = localMin;

            if (nums[i] > 0) {
                localMax = prevMax > 0 ? nums[i] * prevMax : nums[i];
                localMin = prevMin < 0 ? nums[i] * prevMin : nums[i];
            } else {
                localMin = prevMax > 0 ? nums[i] * prevMax : nums[i];
                localMax = prevMin < 0 ? nums[i] * prevMin : nums[i];
            }
            
            result = std::max(localMax, result);
        }
        
        return result;
    }
};

int main () {
    Solution s;

    vector<int> arr1 = {2, 3, -2, 4};
    cout << s.maxProduct(arr1) << endl;

    vector<int> arr2 = {3, -6, 0, 2, -1, -3};
    cout << s.maxProduct(arr2) << endl;

    vector<int> arr3 = {10, -6, 0, 2, -1, -4};
    cout << s.maxProduct(arr3) << endl;

    vector<int> arr4 = {-2, 0, -1};
    cout << s.maxProduct(arr4) << endl;
}