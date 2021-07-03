#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        if (points.empty() || points.size() == 1) {
            return points.size();
        }
        
        int result = 1;
        unordered_map<string, int> slope_map; // key is searialzation of (num1)_(num2) and value is count.
        
        for (int i = 0; i < points.size(); i++) {
            slope_map.clear();
            int vertical = 1;
            int horizontal = 1;
            
            for (int j = 0; j < points.size(); j++) {
                if ((i == j) || (points[i][0] == points[j][0] && points[i][1] == points[j][1])) {
                    continue;
                }

                if (points[i][0] == points[j][0]) {
                    vertical++;
                    result = max(result, vertical);
                } else if (points[i][1] == points[j][1]) {
                    horizontal++;
                    result = max(result, horizontal);
                } else {
                    int num1 = points[i][0] - points[j][0];
                    int num2 = points[i][1] - points[j][1];

                    bool is_positive = !(num1 > 0 ^ num2 > 0);
                    int divisor = gcd(abs(points[i][0] - points[j][0]), abs(points[i][1] - points[j][1]));
                    string key_part1 = to_string(abs(num1) / divisor);
                    string key_part2 = to_string(abs(num2) / divisor);
                    string key = key_part2 + "_" + key_part1 + (is_positive ? "" : "-");
                    if (slope_map.find(key) == slope_map.end()) {
                        slope_map.insert(make_pair(key, 2));
                    } else {
                        slope_map[key]++;
                    }

                    result = max(result, slope_map[key]);
                }
            }
        }

        return result;
    }
private:
    int gcd(int x, int y) {
        return x == 0 ? y : gcd(y % x, x);
    }
};

int main ()
{
    vector<vector<int>> test1 = {{1, 1}, {2, 2}, {3, 3}, {2, 0}, {0, 2}, {0, 0}};
    vector<vector<int>> test2 = {{1, 1}, {1, 0}};
    vector<vector<int>> test3 = {{1, 1}, {0, 1}};
    Solution s;
    cout << s.maxPoints(test1) << endl;
    cout << s.maxPoints(test2) << endl;
    cout << s.maxPoints(test3) << endl;
}