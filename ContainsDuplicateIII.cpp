#include <unordered_map>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

// the gist here is to 1) maintain a slide window with K. 2) make key as 
// bucket (with t + 1) number, and value as the actual value. Then the
// duplicate only can occur in the same bucket or in adjacent buckets.

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if (nums.size() < 2 || k < 1 || t < 0) {
            return false;
        }

        unordered_map<long long, int> mp;
        int min_num = *std::min_element(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            long long bucket = ((long long)nums[i] - (long long)min_num) / ((long long)t + (long long)1);
            if (mp.find(bucket) != mp.end() 
            || (mp.find(bucket + 1) != mp.end() && mp[bucket + 1] - nums[i] <= t)
            || (mp.find(bucket - 1) != mp.end() && nums[i] - mp[bucket - 1] <= t))
            {
                return true;
            }

            mp[bucket] = nums[i];
            if (mp.size() > k) {
                mp.erase((nums[i - k] - min_num) / (t + 1));
            }
        }

        return false;
    }
};

int main () {
    Solution s;

    vector<int> nums1 = {1, 2, 3, 1};
    vector<int> nums2 = {1, 4, 2, 3};
    vector<int> nums3 = {5, 1, 8, 14, 4};
    vector<int> nums4 = {INT_MAX, -1, INT_MIN };
 
    // cout << s.containsNearbyAlmostDuplicate(nums1, 3, 0) << endl;
    // cout << s.containsNearbyAlmostDuplicate(nums2, 1, 2) << endl;
    // cout << s.containsNearbyAlmostDuplicate(nums3, 3, 3) << endl;
    cout << s.containsNearbyAlmostDuplicate(nums4, 1, INT_MAX) << endl;
}
