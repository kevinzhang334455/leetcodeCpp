#include "PrintUtil.hpp"
#include <iostream>
#include <vector>
#include <list>

using namespace std;

// What is the constraints here? What do we want to optimized for?
// Initial thought: have two vectors 1) one for interval starts 2) one for interval
// ends. 

// Then we consider some basic cases:
// 1) add a existing number.
// 2) add a new number where number - 1 and number + 1 doesn't exist.
// 3) merge end interval. e.g. [2, 2] then add 3, becomes [2,3]
// 4) merge start interval. e.g. [2, 2] then add 1, becomes [1,2]
// 5) merge both. e.g. [1,2], [4,5] then add 3, becomes [1,5].

// Another observation is that intervals are paired, namely, the numbers
// will be constantly even. e.g. [1,2], [4,5]. Then we can do a binary search
// to merge with the cases above. 

class SummaryRanges {
public:
    SummaryRanges() {
        _records = vector<bool>(10001, false);
    }
    
    void addNum(int val) {
        if (_records[val] == true) {
            return;
        }
        
        _records[val] = true;
        if (_arrs.empty()) {
            _arrs.push_back(val);
            _arrs.push_back(val);
            return;
        }

        int begin = 0; int end = _arrs.size() - 1;
        bool inserted = false;
        while (begin < end && inserted == false) {
            int mid = begin + (end - begin) / 2;
            if (val < _arrs[mid]) {
                end = mid;
            } else if (val > _arrs[mid + 1]) {
                begin = mid + 1;
            } else {
                // _arrs[mid] < val < _arrs[mid  + 1]
                inserted = true;

                if (_arrs[mid] + 1 < val && _arrs[mid + 1] - 1 > val) {
                    // C++ library insertion happens before iterator, so we need
                    // to insert mid + 1 to insert after mid iterator.
                    _arrs.insert(_arrs.begin() + mid + 1, val); 
                    _arrs.insert(_arrs.begin() + mid + 1, val);
                } else if (_arrs[mid] + 1 == val && _arrs[mid + 1] - 1 > val) {
                    _arrs[mid]++;
                } else if (_arrs[mid] + 1 < val && _arrs[mid + 1] - 1 == val) {
                    _arrs[mid + 1]--;
                } else {
                    // case: [x, n -1], [n + 1, y] -> merge to [x, y]
                    _arrs.erase(_arrs.begin() + mid + 1);
                    _arrs.erase(_arrs.begin() + mid);
                }
            }
        }

        // Invariant: begin == end
        if (!inserted) {
            if (val < _arrs[begin] - 1) {
                _arrs.insert(_arrs.begin(), val);
                _arrs.insert(_arrs.begin(), val);
            } else if (val == _arrs[begin] - 1) {
                _arrs[begin]--;
            } else if (val == _arrs[begin] + 1) {
                _arrs[begin]++;
            } else {
                _arrs.push_back(val);
                _arrs.push_back(val);
            }
        }
    }
    
    vector<vector<int>> getIntervals() {
        vector<vector<int>> ans;
        for (int i = 0; i < _arrs.size(); ) {
            vector<int> interval { _arrs[i], _arrs[i + 1] };
            ans.push_back(interval);
            i += 2;
        }
        return ans;
    }

private:
    vector<int> _arrs;
    vector<bool> _records;
};

int main () {
    SummaryRanges summaryRanges;
    summaryRanges.addNum(6);
    summaryRanges.addNum(0);
    summaryRanges.addNum(4);
    PrintUtil::printVectorVectorOf(summaryRanges.getIntervals());
}