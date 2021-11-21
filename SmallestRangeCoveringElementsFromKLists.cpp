#include "PrintUtil.hpp"
#include <set>
#include <vector>

using namespace std;

class Solution {
    struct numinfo {
        int val;
        int arr;
        int idx;

        numinfo(int v, int a, int i) : val(v), arr(a), idx(i) {} 
    };
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        vector<int> result;
        auto cmp = [](numinfo a, numinfo b) {
            return a.val < b.val || (a.val == b.val && a.arr < b.arr);
        };
        
        set<numinfo, decltype(cmp)> s(cmp);

        for (int i = 0; i < nums.size(); i++) {
            s.emplace(nums[i][0], i, 0);
        }
        
        while (!s.empty() && s.size() == nums.size()) {
            int l = s.begin()->val;
            int laid = s.begin()->arr;
            int lidx = s.begin()->idx;
            int h = (--s.end())->val;

            if (result.empty() || result[1] - result[0] > h - l) {
                vector<int> newres = {l, h};
                result = newres;
            }

            if (result[1] == result[0]) {
                // cannot have more optimal solution, break.
                break;
            }

            s.erase(s.begin());
            if (lidx + 1 < nums[laid].size()) {
                s.emplace(nums[laid][lidx + 1], laid, lidx + 1);
            }
        }

        return result;
    }
};

int main () {
    Solution s;
    vector<vector<int>> test1 = {{1}, {2}, {3}};
    vector<vector<int>> test2 = {{1,11,18},{12, 18, 29}, {18, 29, 30}};
    vector<vector<int>> test3 = {{4, 10, 14, 15, 26}, {17, 20, 24}, {25, 28}};
    PrintUtil::printVectorOf(s.smallestRange(test1));
    PrintUtil::printVectorOf(s.smallestRange(test2));
    PrintUtil::printVectorOf(s.smallestRange(test3));
}