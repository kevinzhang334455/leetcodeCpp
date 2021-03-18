#include <vector>
#include <iostream>
using namespace std;

/* 
Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4] 
*/

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int groups = gcd(int(nums.size()), k);
        for (int i = 0; i < groups; i++) {
            int temp = nums[i];
            int curr_idx = i;
            for (int j = 0; j < static_cast<int>(nums.size()) / groups; j++) {
                int next_idx = (curr_idx + k) % nums.size();
                int next_temp = nums[next_idx];
                nums[next_idx] = temp;
                temp = next_temp;
                curr_idx = next_idx;
            }
        }
    }
private:
    int gcd(int a, int b) {
        return a == 0 ? b : gcd(b % a, a);
    }
};

void TestUtil(vector<int>& arr, int k) {
    Solution s;
    s.rotate(arr, k);
    for (auto i : arr) {
        cout << i << ' ';
    }

    cout << endl;
}

int main ()
{
    vector<int> test1 = {1,2,3,4,5,6,7};
    vector<int> test2 = {1,2,3,4,5,6,7,8,9,10,11,12};
    vector<int> test3 = {1,2,3,4,5,6,7};
    vector<int> test4 = {1,2,3,4,5,6,7,8,9,10,11,12};
    vector<int> test5 = {1,2,3,4,5,6,7,8,9,10,11,12};

    TestUtil(test1, 3);
    TestUtil(test2, 4);
    TestUtil(test3, 6);
    TestUtil(test4, 24);
    TestUtil(test5, 15);
}