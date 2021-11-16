#include <iostream>
#include <string>

using namespace std;

/* Given a string s and an integer k, return the length of the longest substring of s such that 
the frequency of each character in this substring is greater than or equal to k. */

// The basic idea is to build a hashmap to track every index that the char has occurred. When it
// reaches the size of K, we know that this char has possibly satisfies the criteria. And we can
// recursively find the substring from those delimiters.

// can we do O(N)?

class Solution {
public:
    int longestSubstring(string s, int k) {
        
    }
};