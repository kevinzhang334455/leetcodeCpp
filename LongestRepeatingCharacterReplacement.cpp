#include <string>
#include <vector>
#include <iostream>

using namespace std;

/* Given a string s that consists of only uppercase English letters, 
you can perform at most k operations on that string.
In one operation, you can choose any character of the string and change it to any other uppercase 
English character.
Find the length of the longest sub-string containing all repeating letters you can get after performing
the above operations. */

// This problem is equivalent to find the maximum len = b - a + 1 such that in s[a..b] one character has
// len - k occurance.

// E.g. s = ABABAA, k = 2

class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> counts(26, 0);
        int maxCount = 0;
        int len = 0;
        for (int p1 = 0, p2 = 0; p2 < s.size(); p2++) {
            counts[s[p2] - 'A']++;
            maxCount = std::max(maxCount, counts[s[p2] - 'A']);
            while (p2 - p1 - maxCount + 1 > k) {
                counts[s[p1] - 'A']--;
                p1++;
            }

            len = std::max(len, p2 - p1 + 1);
        }

        return len;
    }
};

int main () {
    Solution s;

    // Test 1:
    cout << s.characterReplacement("cabccc", 1) << endl;
}