#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> result;
        std::sort(intervals.begin(), intervals.end(), [](vector<int> a, vector<int> b) {
            return a[0] < b[0];
        });

        for (auto interval : intervals) {
            if (result.empty()) {
                result.push_back(interval);
                continue;
            }

            auto& last = result.back();
            if (last[1] < interval[0]) {
                result.push_back(interval);
            } else {
                last[1] = std::max(last[1], interval[1]);
            }
        }
        
        return result;
    }
};

int main () {
    Solution s;
    vector<vector<int>> intervals = {{1, 3}, {2, 6}, {3, 5}, {10, 15}};
    auto mergedInterval = s.merge(intervals);
}