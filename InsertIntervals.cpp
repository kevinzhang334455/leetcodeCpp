#include <vector>
using namespace std;

// [[1, 3], [6, 9]], [4, 5] ==> [[1, 3], [4, 5], [6, 9]]
// [[1, 3], [6, 9]], [2, 5] ==> [[1, 5], [6, 9]]
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> results;
        bool isMerged = false;
        for (int i = 0; i < intervals.size(); i++) {
            bool isNewInterval = !isMerged && newInterval[0] < intervals[i][0];
            vector<int>& currInterval = isNewInterval ? newInterval : intervals[i];
            if (isNewInterval) {
                i--;
                isMerged = true;
            }
            
            merge(results, currInterval);
        }
        
        if (!isMerged) {
            merge(results, newInterval);
        }

        return results;    
    }
    
private:
    void merge(vector<vector<int>>& results, vector<int>& interval) {
        if (results.empty() || results.back().at(1) < interval[0]) {
            results.push_back(interval);
        } else {
            auto& last = results.back();
            last[1] = std::max(last[1], interval[1]);
        }
    }
};