#include "PrintUtil.hpp"
#include <vector>
#include <utility>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        int diag_45 = 0, dir = 0, M = mat.size(), N = mat[0].size();
        vector<pair<int, int>> dirs = {{-1, 1}, {1, -1}, {0, 1}, {1, 0}};
        vector<int> result;
        if (mat.empty()) {
            return result;
        }

        unordered_set<int> vis;
        queue<int> q;
        q.push(0);
        vis.insert(0);
        while (!q.empty()) {
            pair<int, int> curr_pos = toPos(q.front(), N);
            result.push_back(mat[curr_pos.first][curr_pos.second]);
            q.pop();

            if (isOut(curr_pos.first + dirs[diag_45].first, curr_pos.second + dirs[diag_45].second, M, N)) {
                if (diag_45 == 0) {
                    dir = curr_pos.second + 1 < N ? 2 : 3;
                    diag_45 = 1;
                } else {
                    dir = curr_pos.first + 1 < M ? 3 : 2;
                    diag_45 = 0;
                }
            }
            else {
                dir = diag_45;
            }

            pair<int, int> next_pos = make_pair(curr_pos.first + dirs[dir].first, curr_pos.second + dirs[dir].second);
            int nextVal = toVal(next_pos, N);

            if (vis.find(nextVal) == vis.end() 
            && !isOut(next_pos.first, next_pos.second, M, N)) {
                vis.insert(nextVal);
                q.push(nextVal);
            }
        }

        return result;
    }
private:
    int toVal(const pair<int, int>& pos, int N) {
        return pos.first * N + pos.second;
    }
    
    pair<int, int> toPos(int val, int N) {
        return make_pair(val / N, val % N);
    }

    bool isOut(int y, int x, int M, int N) {
        return y < 0 || y >= M || x < 0 || x >= N;
    }
};

 vector<vector<int>> GenerateMat(int m, int n) {
     vector<vector<int> > mat(m, vector<int>(n, 0));
     int curr = 1;
     for (int i = 0; i < m; i++) {
         for (int j = 0; j < n; j++) {
             mat[i][j] = curr;
             curr++;
         }
     }

     return mat;
 }

int main () {
    Solution s;
    PrintUtil printUtil;
    vector<vector<int>> t1 = GenerateMat(2, 3);
    vector<vector<int>> t2 = GenerateMat(3, 3);
    vector<vector<int>> t3 = GenerateMat(3, 2);
    vector<vector<int>> t4 = GenerateMat(1, 4);
    vector<vector<int>> t5 = GenerateMat(4, 1);

    printUtil.printVectorOf<int>(s.findDiagonalOrder(t1));
    printUtil.printVectorOf<int>(s.findDiagonalOrder(t2));
    printUtil.printVectorOf<int>(s.findDiagonalOrder(t3));
    printUtil.printVectorOf<int>(s.findDiagonalOrder(t4));
    printUtil.printVectorOf<int>(s.findDiagonalOrder(t5));
}