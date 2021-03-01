#include <vector>
using namespace std;

class HitCounter {
public:
    /** Initialize your data structure here. */
    HitCounter() {
        counts = vector<int>(size, 0);
        cycles = vector<int>(size, 0);
    }
    
    /** Record a hit.
        @param timestamp - The current timestamp (in seconds granularity). */
    void hit(int timestamp) {
        int cycle = timestamp / 300;
        int idx = timestamp % 300;

        if (cycles[idx] == cycle) {
            counts[idx]++;
        } else {
            cycles[idx] = cycle;
            counts[idx] = 1;
        }
    }
    
    /** Return the number of hits in the past 5 minutes.
        @param timestamp - The current timestamp (in seconds granularity). */
    int getHits(int timestamp) {
        int res = 0;
        for (int t = std::max(0, timestamp - 300) + 1; t <= timestamp; t++) {
            int cycle = t / 300;
            int idx = t % 300;
            if (cycle == cycles[idx]) {
                res += counts[idx];
            }
        }

        return res;
    }

private:
    vector<int> counts; // counting the hits given timestamp which equals to 300 * cycles[idx] + idx; 
    vector<int> cycles; // recording the curent cycles which has 300 seconds / cycle.
    const int size = 300; // the buffer size.
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter* obj = new HitCounter();
 * obj->hit(timestamp);
 * int param_2 = obj->getHits(timestamp);
 */