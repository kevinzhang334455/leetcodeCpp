#include <vector>
#include <iostream>

using namespace std;

/* A 2d grid map of m rows and n columns is initially filled with water. 
We may perform an addLand operation which turns the water at position (row, col) into a land. 
Given a list of positions to operate, count the number of islands after each addLand operation. 
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. 
You may assume all four edges of the grid are all surrounded by water.

Example:

Input: m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]]
Output: [1,1,2,3] */

class Solution {
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        vector<int> uf(m * n, -1);
        vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        vector<int> result;

        for (auto pos : positions) {
            int currFlattedPos = pos[0] * n + pos[1];
            int currCount = !result.empty() ? result.back() : 0;
            if (!isValidPos(m, n, pos) || uf[currFlattedPos] != -1) {
                result.push_back(currCount);
                continue;
            }

            int targetCount = currCount + 1;
            int unionVal = -1; // undecided value to set to the uf for currFlattedPos.

            for (auto dir : dirs) {
                vector<int> adjPos = {pos[0] + dir.first, pos[1] + dir.second};
                if (!isValidPos(m, n, adjPos)) {
                    continue;
                }

                auto adjFlattedPos = adjPos[0] * n + adjPos[1];
                auto adjParent = find(uf, adjFlattedPos);
                if (adjParent == -1 || unionVal == adjParent) {
                    continue;
                } else {
                    // In this case the current adjacency has aleady been processed. So either 1)
                    // the union val is still undetermined, we will set the union value to current
                    // adjParent or 2) the union value is not null which means we need to union
                    // the current **parent** of the adjacency to unionVal.
                    if (unionVal == -1) {
                        unionVal = adjParent;
                    } else {
                        uf[adjParent] = unionVal; // NOT uf[adjFlattedPos] = unionVal. We need to union root.
                    }

                    // either case the target count should be decreased.
                    targetCount--;
                }
            }

            // Union the currFlattedPos.
            uf[currFlattedPos] = unionVal != -1 ? unionVal : currFlattedPos;

            result.push_back(targetCount);
        }

        return result;
    }

private:
    bool isValidPos(int m, int n, vector<int>& pos) {
        return pos[0] >= 0 && pos[0] < m && pos[1] >= 0 && pos[1] < n;
    }

    int find(vector<int>& uf, int flattedPos) {
        int currPos = flattedPos;
        while (uf[currPos] != -1 && uf[currPos] != currPos) {
            currPos = uf[currPos];
        }

        return uf[currPos];
    }
};

struct TestStruct
{
    int M;
    int N;
    vector<vector<int>> Points;

    TestStruct(int m, int n, vector<vector<int>> points) {
        M = m;
        N = n;
        Points = points;
    }
};

void Test(TestStruct ts) {
    Solution s;
    auto counts = s.numIslands2(ts.M, ts.N, ts.Points);
    for (auto cnt : counts) {
        cout << cnt << ' ';
    }

    cout << endl;
}


int main() {
    // TestStruct testStruct1(3, 3, {{0,0},{0,1},{1,2},{2,1}});
    // Test(testStruct1);

    TestStruct testStruct2(3, 3, {{0,1},{1,2},{2,1},{1,0},{0,2},{0,0},{1,1}});
    Test(testStruct2);
}