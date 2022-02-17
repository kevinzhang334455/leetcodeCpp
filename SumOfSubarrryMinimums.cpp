#include <vector>
#include <iostream>
#include <stack>
using namespace std;

// Given an array of integers arr, find the sum of min(b), 
// where b ranges over every (contiguous) subarray of arr. 
// Since the answer may be large, return the answer modulo 10^9 + 7.

// Example 1:

// Input: arr = [3,1,2,4]
// Output: 17
// Explanation: 
// Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4]. 
// Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
// Sum is 17.
// Example 2:

// Input: arr = [11,81,94,43,3]
// Output: 444
 
// Constraints:

// 1 <= arr.length <= 3 * 104
// 1 <= arr[i] <= 3 * 104

// The technique here is using monotonic stack to keep track of the previous less
// element and the next less element given each element in array (let's denote arr[i]). 
// Then we can have a range such that the minimum element is arr[i].

class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        int N = arr.size();
        stack<int> st1, st2; // monotonic increasing stack.
        vector<int> left(N, -1); // stands for counting from left, how many elements
        // can be served by current element such that current element is the smallest.
        vector<int> right(N, -1); // stands for counting from right, how many elements
        // can be served by current element such that current element is the smallest.

        for (int i = 0; i < N; i++) {
            left[i] = i + 1; // i can be served to 0~i
            right[i] = N - i; // i can be served from i~N-1
        }

        for (int i = 0; i < arr.size(); i++) {
            while (!st1.empty() && arr[st1.top()] > arr[i]) {
                st1.pop();
            }

            if (!st1.empty()) {
                left[i] = i - st1.top(); // served from st.top() ~ i
            }

            st1.push(i);
        }

        for (int i = N - 1; i >= 0; i--) {
            while (!st2.empty() && arr[st2.top()] > arr[i]) {
                st2.pop();
            }

            if (!st2.empty()) {
                right[i] = st2.top() - i; // served from i ~ st.top. 
            }

            st2.push(i);
        }

        int ans = 0;
        // [3,1,2,5,4]
        for (int i = 0; i < arr.size(); i++) {
            // [2,1,2] => [1], [1,2], [2,1], [2,1,2]
            ans += (left[i] * arr[i] * right[i]) % (1000000007);
        }

        return ans;
    }
};

int main () {
    Solution s;
    vector<int> test1 = {3,1,2,4};
    cout << s.sumSubarrayMins(test1) << endl;
}