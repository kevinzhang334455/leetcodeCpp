#include "PrintUtil.hpp"
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ans;
        if (matrix.empty()) {
            return ans;
        }
        
        int M = matrix.size();
        int N = matrix[0].size();
        vector<int> walls = {N, M, -1, -1};
        int i = 0, j = 0;
        
        while (true) {            
            // go right
            for (; j < walls[0]; j++) {
                ans.push_back(matrix[i][j]);
            }

            if (ans.size() == M * N) {
                break;
            }
            
            --j;
            ++i;
            walls[3]++;
            
            // go down
            for (; i < walls[1]; i++) {
                ans.push_back(matrix[i][j]);
            }

            if (ans.size() == M * N) {
                break;
            }
            
            --i;
            --j;
            --walls[0];
            
            // go left
            for (; j > walls[2]; j--) {
                ans.push_back(matrix[i][j]);
            }

            if (ans.size() == M * N) {
                break;
            }
            
            ++j;
            --i;
            --walls[1];
            
            // go up
            for (; i > walls[3]; i--) {
                ans.push_back(matrix[i][j]);
            }

            if (ans.size() == M * N) {
                break;
            }
            
            ++i;
            ++j;
            ++walls[2];
        }
        
        return ans;
    }
};

int main () {
    Solution s;
    vector<vector<int>> mat = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    PrintUtil::printVectorOf(s.spiralOrder(mat));
}