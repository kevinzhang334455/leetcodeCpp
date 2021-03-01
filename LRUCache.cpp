#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

class LRUCache {
public:
    LRUCache(int capacity) {
        _capacity = capacity;
    }
    
    int get(int key) {
        if (posStore.find(key) == posStore.end()) {
            return -1;
        }

        move(key);
        return dataStore[key];
    }
    
    void put(int key, int value) {
        if (_capacity <= 0) {
            return;
        }

        if (dataStore.find(key) != dataStore.end()) {
            dataStore[key] = value; 
        } else {
            if (keys.size() == _capacity) {
                int lastKey = keys.back();
                dataStore.erase(lastKey);
                posStore.erase(lastKey);
                keys.pop_back();
            }

            keys.push_back(key);
            dataStore.insert(make_pair(key, value));
            posStore.insert(make_pair(key, --keys.end()));
        }

        move(key);
    }
private:
    void move(int key) {
        auto iter = posStore[key];

        keys.erase(iter);
        keys.insert(keys.begin(), key);

        posStore[key] = keys.begin();
    }

    list<int> keys;
    unordered_map<int, int> dataStore;
    unordered_map<int, list<int>::iterator> posStore;
    int _capacity;
};

int main () {
    LRUCache lruCache(3);
    cout << lruCache.get(1) << endl;
    lruCache.put(1, 3);
    cout << lruCache.get(1) << endl;
    lruCache.put(1, 4);
    cout << lruCache.get(1) << endl;
    lruCache.put(3, 5);
    lruCache.put(4, 6);
    lruCache.put(5, 7);
    cout << lruCache.get(1) << endl;
    cout << lruCache.get(5) << endl;
    cout << lruCache.get(3) << endl;
    cout << lruCache.get(4) << endl;
}