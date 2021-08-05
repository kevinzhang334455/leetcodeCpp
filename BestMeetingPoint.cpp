#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

// https://leetcode.com/problems/best-meeting-point/

/* Given an m x n binary grid grid where each 1 marks the home of one friend, return the minimal total travel distance.

The total travel distance is the sum of the distances between the houses of the friends and the meeting point.

The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|. */

// The first approach would be DFS + hashmap
// This approach would be result in TLE. Time complexity m^2*n^2 (for each point in grid it needs to reach
// the whole board which takes O(m*n), so total would be O(m^2 * n^2))

// Second approach is directly caclulating the Manhattan distance in each cell of the grid. 
// Should be same time complexity.

// Third approach: Directly find median point of the existing points. 
// Proof: Think about the 1D dimension. 
// Case [1, 0, 0, 1, 1]. The cost array is {7, 6, 5, 4, 5}. The minimum cost is median point
// since the delta of cost where all points moving from median has to be > 0. E.g. in the case 
// above, the median point is x = 3, and if we take average of points x = (0 + 3 + 4) / 3 = 2,
// it caused #(rhs points) > #(lhs points) and the distance increase is #(rhs points) and the 
// distance decrease is #(lhs points), so delta(total) = #(rhs points) - #(lhs points). 
// So the mininum should always be median point. 

// Optimization. We can also avoid sort (which takes mn*Log(mn)) by iterating two times of the
// Grid. So the time complexity could be O(m * n).

// Another proof from Math Induction (数学归纳法):
// n = 1, it's the median point. We know this is the best point.
// n = 2, there are two middle point x0,x1, (x0<=x1) pick any one is the best point. 
// This gives the min distance x1 - x0. 
// n = 1,2 are our base cases, we prove the median point is the best point.
// For n>=3. We can filter out (or say ignore) the leftmost point x0 and rightmost point xn
// because the min distance for these two points alone *have to be* xn - x0.
// so in the remaining n-2 points we already prove the median point 
// of the n-2 points is the best. So the best for n points is same as the best for the 
// middle n-2 points. So this means that we can recursively ignore the boundary points
// and to consider only the center point(s) which falls to the base case where n = 1 or 2.

class Solution1 {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        if (grid.empty()) {
            return 0;
        }

        int M = grid.size();
        int N = grid[0].size();
        int result = INT_MAX;

        // Need to initialization.
        vector<vector<unordered_map<int, int>>> visMap(M, vector<unordered_map<int, int>>(N)); // int-int map: id - shortest distance.
        queue<tuple<int, int, int>> q; // id, pos, dis

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 1) {
                    int id = GetVal(i, j, N);
                    q.emplace(id, id, 0);
                }
            }
        }

        const int sourceCount = q.size();
        vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

        while (!q.empty()) {
            auto [curr_id, curr_pos_val, curr_dis] = q.front();
            q.pop();

            auto curr_pos = GetPos(curr_pos_val, M, N);
            auto& curr_map = visMap[curr_pos.first][curr_pos.second];

            curr_map.insert(make_pair(curr_id, curr_dis));
            if (curr_map.size() == sourceCount) {
                // all starting points reaches this node
                int total_dis = 0;

                for (auto [id, dis] : curr_map) {
                    total_dis += dis;
                }

                result = min(result, total_dis);
            }

            // Visit adjacencies and push to queue if available.
            for (auto [p1, p2] : dirs) {
                auto next_pos = make_pair(curr_pos.first + p1, curr_pos.second + p2);

                if (next_pos.first < 0 || next_pos.first >= M || next_pos.second < 0 || next_pos.second >= N) {
                    continue;
                } else if (visMap[next_pos.first][next_pos.second].find(curr_id) != visMap[next_pos.first][next_pos.second].end()) {
                    continue; // the position has been visited.
                }

                int next_pos_val = GetVal(next_pos.first, next_pos.second, N);
                q.push(std::make_tuple(curr_id, next_pos_val, curr_dis + 1));
            }
        }

        return result;
    }
private:
    int GetVal(int x, int y, int N) {
        return x * N + y;
    }

    pair<int, int> GetPos(int val, int M, int N) {
        return make_pair<int, int>(val / N, val % N);
    }
};

class Solution2 {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        if (grid.empty()) {
            return 0;
        }

        auto sortedRow = GetSortedPointsInRow(grid);
        auto sortedCol = GetSortedPointsInCol(grid);
        return 
        GetTotalDistanceInDim(sortedRow, sortedRow.size() / 2) + 
        GetTotalDistanceInDim(sortedCol, sortedCol.size() / 2);
    }

private:
    int GetTotalDistanceInDim(const vector<int>& points, int pos) {
        int distance = 0;
        int median = points[pos];

        for (auto point : points) {
            distance += point - median > 0 ? point - median : median - point;
        }

        return distance;
    }

    vector<int> GetSortedPointsInRow(const vector<vector<int>>& grid) {
        vector<int> sortedRows;

        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) {
                    sortedRows.push_back(i);
                }
            }
        }

        return sortedRows;
    } 
    
    vector<int> GetSortedPointsInCol(const vector<vector<int>>& grid) {
        vector<int> sortedCols;

        for (int j = 0; j < grid[0].size(); j++) {
            for (int i = 0; i < grid.size(); i++) {
                if (grid[i][j] == 1) {
                    sortedCols.push_back(j);
                }
            }
        }

        return sortedCols;
    }
};

int main () {
    Solution1 s1;
    Solution2 s2;
    vector<vector<int>> test1 = {{ 1, 0, 0, 0, 1 }, { 0, 0, 0, 0, 0 },{ 0, 0, 1, 0, 0} };

    cout << s1.minTotalDistance(test1) << endl;
    cout << s2.minTotalDistance(test1) << endl;
}