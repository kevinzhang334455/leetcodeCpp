#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {        
        const int N = nums.size();
        
        for (int i = 0; i < N; i++)
        {
            if (nums[i] != i + 1 && nums[i] > 0 && nums[i] <= N)
            {
                auto idx = nums[i] - 1;
                
                if (nums[idx] != nums[i])
                {
                    std::swap(nums[i], nums[idx]);
                    i--;
                }
            }
        }
        
        int res = 1;
        
        for (int i = 0; i < N; i++)
        {
            if (nums[i] != i + 1)
            {
                break;
            }
            else
            {
                res++;
            }
        }
        return res;
    }
};

int main()
{
    Solution s;
    vector<int> nums = { 3, 4, -1, 1};
    cout << s.firstMissingPositive(nums) << endl;
}