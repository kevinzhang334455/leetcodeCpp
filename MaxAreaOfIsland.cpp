#include <vector>
#include <map>
#include <iostream>
using namespace std;

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if (grid.empty()) {
            return 0;
        }
        
        int M = grid.size();
        int N = grid[0].size();
        int ans = 0;
        
        vector<int> uf(M * N, -1);
        map<int, int> area_map;
        
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 0) {
                    continue;
                } else {
                    int pos = i * N + j;
                    uf[pos] = pos;
                    
                    int left = j != 0 ? find(uf, i * N + j - 1) : -1;
                    int up = i != 0 ? find(uf, (i - 1) * N + j) : -1;
                    
                    int u = -1;
                    if (left != -1 && up != -1) {
                        uf[left] = up;
                        u = up;
                    } else if (left != -1) {
                        u = left;
                    } else if (up != -1) {
                        u = up;
                    }
                    
                    if (u != -1) {
                        uf[pos] = u;
                    } else {
                        u = pos;
                    }
                    
                    if (area_map.find(u) == area_map.end()) {
                        area_map.emplace(u, 1);
                    } else if (left == -1 || up == -1 || up == left) {
                        area_map[u]++;
                    } else {
                        int new_area = area_map[left] + area_map[up] + 1;
                        area_map.erase(left);
                        area_map.erase(up);
                        area_map.emplace(u, new_area);
                    }

                    ans = max(ans, area_map[u]);
                }
            }
        }

        return ans;
    }
    
private:
    int find(const vector<int>& uf, int pos) {
        if (pos < 0 || pos >= uf.size()) {
            return -1;
        }
        
        if (uf[pos] == -1 || uf[pos] == pos) {
            return uf[pos];
        } else {
            return find(uf, uf[pos]);
        }
    }
};

int main () {
    Solution s;
    vector<vector<int>> grid = {{0,0,1,0,0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,1,1,1,0,0,0},{0,1,1,0,1,0,0,0,0,0,0,0,0},{0,1,0,0,1,1,0,0,1,0,1,0,0},{0,1,0,0,1,1,0,0,1,1,1,0,0},{0,0,0,0,0,0,0,0,0,0,1,0,0},{0,0,0,0,0,0,0,1,1,1,0,0,0},{0,0,0,0,0,0,0,1,1,0,0,0,0}};
    cout << s.maxAreaOfIsland(grid) << endl;
}