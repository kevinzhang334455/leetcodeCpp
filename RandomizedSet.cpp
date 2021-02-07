#include <vector>
#include <unordered_map>

using namespace std;

// Implement a RandomizedSet class such that insert, delete and getRandom has a O(1) time complexity in average.
// Basic idea is to achieve GetRandom O(1) via a vector and use a unordered_map to keep track of insert and delete. 

class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (idxMap.find(val) != idxMap.end()) {
            return false;
        }
        
        vec.push_back(val);
        
        idxMap.insert(make_pair(val, vec.size() - 1));
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (idxMap.find(val) == idxMap.end()) {
            return false;
        }
        
        // To achieve the vector deletion of O(1) we can do a swap then do a pop back. 
        int idx = idxMap[val];
        idxMap[vec.back()] = idx;
        swap(vec[vec.size() - 1], vec[idx]);
        vec.pop_back();
        
        idxMap.erase(val);
        
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        int randIdx = rand() % vec.size();
        return vec[randIdx];
    }
    
private:
    vector<int> vec;
    unordered_map<int, int> idxMap;    
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */