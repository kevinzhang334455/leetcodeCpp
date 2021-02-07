#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
using namespace std;

// Dynamic Programming
// O(n ^ 3) time, O(n ^ 2) space.

// Basic idea:
// Since for each stone i the frog has to jump from previous stone j, in which the number of required steps 
// jumping from stone j should be exact stones[i] - stones[j]. Then we need look through all the successful
// jumps to stone j from previous stone k and check whether the jump from stone k to stone j has either the
// number of steps of {stones[i] - stones[j] - 1, stones[i] - stones[j] + 1, stones[i] - stones[j]}. And we 
// can do a dynamic programming to progressively figure out dp[i][j] by dp[j][k] where k < j < i.

// The O(n ^ 3) will be TLE.

// What we can do is we can use a hashmap to basically make the query of dp[j] as a O(1).

// then O (n ^ 2 * lgN) will be TLE as well.

class Solution {
public:
    bool canCross(vector<int>& stones) {
        if (stones.size() == 0 || stones.size() == 1) {
            return true;
        } else if (stones.size() == 2 && 
                   (stones[0] != 0 || stones[1] != 1)) {
            return false;
        }
        
        const int N = stones.size();
        
        vector<unordered_set<int>> dp(N, unordered_set<int>());
        dp[0].insert(1);
        dp[1].insert(1);
        
        for (int i = 1; i < N; i++) {
            for (int j = 0; j < i; j++) {
                int target = stones[i] - stones[j];
                if (dp[j].find(target) != dp[j].end() || 
                dp[j].find(target + 1) != dp[j].end() ||
                dp[j].find(target - 1) != dp[j].end()) {
                    dp[i].insert(target);
                }
            }
        }

        return !dp.back().empty();
    }
};

// Improvement: 
class Solution2 {
public:
    bool canCross(vector<int>& stones) {
        if (stones.empty() || stones.size() == 1) {
            return true;
        }

        unordered_map<int, unordered_set<int>> mp;
        for (int i = 0; i < stones.size(); i++) {
            mp.insert(make_pair(stones[i], unordered_set<int>()));
        }

        mp[0].insert(0);

        for (int i = 0; i < stones.size(); i++) {
            int currPos = stones[i];
            for (auto it = mp[currPos].begin(); it != mp[currPos].end(); it++) {
                int steps = *it;
                for (int s = max(1, steps - 1); s <= steps + 1; s++) {
                    if (mp.find(s + currPos) != mp.end()) {
                        mp[s + currPos].insert(s);
                    }
                }
            }
        }

        return !mp[stones.back()].empty();
    }
};

int main() {
    Solution s;
    Solution2 s2;
    vector<int> test1 = { 0, 1, 3, 5, 6, 8, 12, 17 };

    // Test1 should be expected to true because 
    // cout << s.canCross(test1) << endl;
    cout << s2.canCross(test1) << endl;
}

