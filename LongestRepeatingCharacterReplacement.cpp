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

// This solution comes from https://leetcode.com/problems/longest-repeating-character-replacement/discuss/91271/Java-12-lines-O(n)-sliding-window-solution-with-explanation
// But I don't think it's a good solution because it's hard to understand.
class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> counts(26, 0);
        int maxCount = 0;
        int len = 0;
        for (int p1 = 0, p2 = 0; p2 < s.size(); p2++) {
            counts[s[p2] - 'A']++;

            // The tricky part of this algorithm is this `maxCount`.
            // This `maxCount` is *NOT* monopoly increasing (see Test 2). What makes this tricky algorithm
            // correct is because we only care about the maximum of this `maxCount` since an optimal solution
            // would be len = maxCount + k, and K is fixed, then only maxCount matters. 
            // The disgusting part is that len is not necessarily equal to maxCount + k, E.g.
            // "AABAB", p2 = 4, p1 = 0, maxCount = 3. The result = 4.
            // Which makes this a very bad algorithm and not easy to maintain.
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

// This is an improvement from the above solution, basically the idea is that we only care 
// about the very *first* time that the maxCount changes and that time is where we need to calculate
// the optimial solution which purely comes from maxCount + k rather than len = p2 - p1 + 1.
class Solution2 {
public:
    int characterReplacement(string s, int k) {
        vector<int> counts(26, 0);
        int maxIdx = -1, maxCount = 0;
        int len = 0;
        for (int p1 = 0, p2 = 0; p2 < s.size(); p2++) {
            int maxCharCount = maxIdx != -1 ? counts[maxIdx] : 0;
            int currCharCount = ++counts[s[p2] - 'A'];

            if (currCharCount > maxCharCount) {
                // The optimal solution is derived from maxCount, rather than two pointers. 
                len = max(len, min(currCharCount + k, (int)s.size()));
                maxIdx = s[p2] - 'A';
                maxCharCount = currCharCount;
            }

            // The logic here is that if maxCharCount is indeed increased, then below is an no-op,
            // otherwise we need to shrink the sliding window if needed.
            if (p2 - p1 + 1 - maxCharCount > k) {
                --counts[s[p1] - 'A']; // what if p1 is maxIdx? Doesn't matter b/c then maxCharCount will decrease with next loop.
                p1++;
            }
        }

        return len;
    }
};

int main () {
    Solution2 s;

    // Test 1, expect length == 1
    cout << s.characterReplacement("ABCA", 1) << endl;

    // Test 2, expect length == 4
    cout << s.characterReplacement("AABABBA", 1) << endl;

    // Test 3,
    cout << s.characterReplacement("AABBAA", 1) << endl;
}