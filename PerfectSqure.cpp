#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class Solution {
public:
    int numSquares(int n) {
        vector<int> table(n + 1, -1);
        int end = static_cast<int>(floor(sqrt(n)));
        for (int i = 1; i <= end; i++) {
            table[i * i] = 1;
        }
        return numSquareHelper(n, table);
    }
private:
    int numSquareHelper(int num, vector<int>& table) {
        if (table[num] != -1) {
            return table[num];
        }
        
        int ans = num;
        int end = static_cast<int>(floor(sqrt(num)));

        // By iterating from sqaures (i*i) we can save 1 call of 
        // numSqaureHelper, comparing to iterate from i to num/2.
        for (int i = 1; i <= end; i++) {
            int remain = numSquareHelper(num - i * i, table);
            ans = min(ans, 1 + remain);
        }
        
        table[num] = ans;
        return ans;
    }
};

int main () {
    Solution s;
    cout << s.numSquares(12) << endl;
}