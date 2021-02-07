#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<vector<int> > reconstructQueue(vector<vector<int> >& people) {
        vector<vector<int> > res;
        if (people.size() == 0 || people.size() == 1) {
            return people;
        }
        
        std::sort(people.begin(), people.end(), [](vector<int>& a, vector<int>& b) {
            if (a[0] > b[0]) {
                return true; 
            } else if (a[0] == b[0] && a[1] < b[1]) {
                return true;
            } else {
                return false;
            }
        });
        
        for (int i = 0; i < people.size(); i++) {
            if (res.empty()) {
                res.push_back(people[i]);
            } else {
                res.insert(res.begin() + people[i][1], people[i]);
            }
        }
        
        return res;
    }
};

int main ()
{
    Solution s;

    vector<vector<int> > test1 = {{7,0},{4,4},{7,1},{5,0},{6,1},{5,2}};
    auto res = s.reconstructQueue(test1);

    for (auto v : res) {
        cout << '[' << v[0] << ',' << v[1] << ']' << ',';
    }

    cout << endl;
}