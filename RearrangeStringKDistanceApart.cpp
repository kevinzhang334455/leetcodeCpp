#include <queue>
#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

/* 
Given a string s and an integer k, rearrange s such that the same characters 
are at least distance k from each other. If it is not possible to rearrange the 
string, return an empty string "". 
*/

class Solution {
public:
    string rearrangeString(string s, int k) {
        if (s.empty() || k <= 1) {
            return s;
        }

        unordered_map<char, int> hm;
        for (auto c : s) {
            if (hm.find(c) != hm.end()) {
                hm.emplace(c, 0);
            }

            hm[c]++;
        }

        auto cmp = [](pair<char, int> a, pair<char, int> b) {
            return a.second < b.second || (a.second == b.second && a.first < b.first);
        };
        priority_queue<pair<char, int>, vector<pair<char, int>>, decltype(cmp)> pq(cmp);
        for (auto& [k, v] : hm) {
            pq.push(make_pair(k, v));
        }

        // Here we can use a buffer queue to queue up the char that polled
        // from the pq, use the queue size to make sure that the char will
        // be put back to pq only if there are K different chars in queue
        // then we can make sure the char is K distance apart from the prev
        // char.
        // a good idiom using priority queue + queue.

        queue<pair<char, int>> buffer;
        string result;

        while (!pq.empty()) {
            auto kv = pq.top();
            pq.pop();
            result.append(1, kv.first);
            kv.second--;
            buffer.push(kv);
            if (buffer.size() < k) {
                // Make sure for each char polled from the priority queue,
                // it will be K distance aprt from the previous append.
                continue;
            }

            kv = buffer.front();
            buffer.pop();
            if (kv.second > 0) {
                pq.push(kv);
            }
        }

        return result.size() == s.size() ? result : "";
    }
};

int main () {
    string test1("abcdefg"); // abcdefg
    string test2("aaabc"); // abaca
    string test3("aabbcc"); // abcbca or abacbc
    string test4("aaaaccb"); // acabaca
    string test5("aaabc"); // ""
    string test6("aaaaa"); // ""
    string test7("aaaaccbaaaaccb"); // ""

    Solution s;
    cout << s.rearrangeString(test1, 1) << endl;
    cout << s.rearrangeString(test2, 2) << endl;
    cout << s.rearrangeString(test3, 2) << endl;
    cout << s.rearrangeString(test4, 2) << endl;
    cout << s.rearrangeString(test5, 3) << endl;
    cout << s.rearrangeString(test6, 2) << endl;
    cout << s.rearrangeString(test7, 2) << endl;
}