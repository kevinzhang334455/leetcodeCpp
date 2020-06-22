#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;

// Find target in rotated sort array, return its index if found.
// e.g. nums = {3,4,5,1,2}
// search(nums, 2) -> 4;
// search(nums, 6) -> -1;
// Without duplicates
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.empty())
        {
            return -1;
        }

        int begin = 0, end = nums.size() - 1;
        while (begin + 1 < end)
        {
            int mid = begin + (end - begin) / 2;
            if (nums[mid] == target)
            {
                return mid;
            } 
            else if (nums[begin] == target)
            {
                return begin;
            }
            else if (nums[end] == target)
            {
                return end;
            }

            bool targetGreaterThanMid = target > nums[mid];
            bool targetGreaterThanBegin = target > nums[begin];
            bool targetGreaterThanEnd = target > nums[end];

            // 1, 2, 3, 4, 5
            if (nums[begin] < nums[mid] && nums[mid] < nums[end])
            {
                if (targetGreaterThanMid)
                {
                    begin = mid + 1;
                }
                else
                {
                    end = mid - 1;
                }
            }
            // 2, 3, 4, 5, 1
            else if (nums[begin] < nums[mid] && nums[mid] > nums[end])
            {
                if (targetGreaterThanMid || !targetGreaterThanBegin)
                {
                    begin = mid + 1;
                }
                else
                {
                    end = mid - 1;
                }
            }
            // 4, 5, 1, 2, 3
            else if (nums[begin] > nums[mid] && nums[mid] < nums[end])
            {
                if (!targetGreaterThanMid || targetGreaterThanEnd)
                {
                    end = mid - 1;
                }
                else
                {
                    begin = mid + 1;
                }
            }
        }

        return nums[end] == target ? end : (nums[begin] == target ? begin : -1); 
    }
};

int main()
{
    Solution s;

    // Test 1:
    vector<int> nums1  = {4,5,6,7,0,1,2};
    cout << s.search(nums1, 1) << endl;

    // Test 2:
    vector<int> nums2 = {4,5,6,7,0,1,2};
    cout << s.search(nums2, 5) << endl;

    // Test 3:
    vector<int> nums3 = {5,6,7,0,1,2,4};
    cout << s.search(nums3, 2) << endl;

    // Test 4:
    vector<int> nums4 = {5, 6, 7, 0, 1, 2, 4};
    cout << s.search(nums4, 5) << endl;

    // Test 5:
    vector<int> nums5 = {7, 0, 1, 2, 4, 5, 6};
    cout << s.search(nums5, 1) << endl;
}