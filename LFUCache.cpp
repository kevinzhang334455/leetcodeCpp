#include <iostream>
#include <map>
#include <unordered_map>
#include <list>
using namespace std;

// The first idea is to determine what is the data structure.
// a ordered map may be a good candidate. 
// ordered map cannot have complexity of O(1).

// We can use two maps. One is frequency map in which key
// is frequency (int) and value are nodes organized by a double-linked
// list. One is node map in which key is the node key and value is the 
// iterator of the node in frequence map.

class LFUCache {
public:
    LFUCache(int capacity) {
        _capacity = capacity;
        _minf = 1;
    }
    
    int get(int key) {
        if (_nmap.find(key) == _nmap.end()) {
            return -1;
        }

        auto& node = _nmap.at(key);

        move(node);
        return node.value;
    }
    
    void put(int key, int value) {
        if (_capacity == 0) {
            return;
        }

        if (_nmap.find(key) == _nmap.end()) {
            if (_nmap.size() == _capacity) {
                int remove_key = *_fmap[_minf].crbegin();
                _fmap[_minf].pop_back();
                _nmap.erase(remove_key);
            }

            _minf = 1;
            if (_fmap.find(_minf) == _fmap.end()) {
                _fmap.emplace(_minf, std::list<int>());
            }

            _fmap[_minf].emplace_front(key);
            Node newnode(key, value, 1, _fmap[_minf].cbegin());
            _nmap.emplace(key, newnode);

        } else {
            auto& node = _nmap.at(key);
            node.value = value;
            move(node);
        }
    }
private:
    struct Node {
        int key;
        int value;
        int freq;
        list<int>::const_iterator it;

        Node(int k, int v, int f, list<int>::const_iterator i) 
        : key(k), value(v), freq(f), it(i) {}
    };

    void move(Node& node) {
        int curr_freq = node.freq;
        int next_freq = node.freq + 1;
        if (_fmap.find(next_freq) == _fmap.end()) {
            _fmap.emplace(next_freq, std::list<int>());
        }

        _fmap[curr_freq].erase(node.it);

        if (_fmap[curr_freq].empty()) {
            _fmap.erase(curr_freq);
            if (curr_freq == _minf) {
                _minf = next_freq;
            }
        }

        _fmap[next_freq].emplace_front(node.key);
        node.it = _fmap[next_freq].cbegin();
        node.freq = next_freq;
    }

    int _minf;
    int _capacity;

    unordered_map<int, Node> _nmap;
    map<int, std::list<int>> _fmap;
};

int main () {
    LFUCache lfuCache(2);
    cout << lfuCache.get(1) << endl;

    lfuCache.put(1, 2);

    cout << lfuCache.get(1) << endl;

    lfuCache.put(2, 3);
    lfuCache.put(3, 4);

    cout << lfuCache.get(2) << endl; // should be evicted.
    cout << lfuCache.get(3) << endl; // should stay.
    cout << lfuCache.get(1) << endl; // should stay.

    lfuCache.put(4, 5);
    cout << lfuCache.get(3) << endl; // should be evicted. 
}