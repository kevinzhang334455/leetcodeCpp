#include "PrintUtil.hpp"
#include <vector>

using namespace std;

// backtracking.
// note that using set/hashmap might be adding extra time when remove elements. it will TLE.
// directly using board for checking.

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        if  (board.empty() ||board[0].empty()) {
            return;
        }

        solve(board);
    }

private:
    bool solve(vector<vector<char>>& board) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] == '.') {
                    for (int val = 1; val <= 9; val++) {
                        char c = '0' + val;
                        if  (isValid(board, i, j, c)) {
                            board[i][j] = c;
                            if (solve(board)) {
                                return true;
                            }

                            board[i][j] = '.';
                        }
                    }

                    return false;
                }
            }
        }

        // all cells are filled.
        return true;
    }

    bool isValid(vector<vector<char>>& board, int row, int col, char c) {
        for (int i = 0; i < 9; i++) {
            if (board[row][i] != '.' && board[row][i] == c) return false;
            if (board[i][col] != '.' && board[i][col] == c) return false;

            //  blk idx + element idx
            if (board[(row / 3) * 3 + i / 3][(col / 3) * 3 + i % 3] != '.' 
            && board[(row / 3) * 3 + i / 3][(col / 3) * 3 + i % 3] == c) return false;
        }

        return true;
    }
};

int main () {
    vector<vector<char>> board = 
    {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'},
    };

    Solution s;
    s.solveSudoku(board);

    PrintUtil::printVectorVectorOf(board);
}