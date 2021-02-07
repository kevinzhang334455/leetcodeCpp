#include <string>
#include <stack>
#include <iostream>

using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        path.append(1, '/');
        stack<string> components;
        for (int p1 = 1, p2 = 1; p2 < path.size(); p2++) {
            if (path[p2] == '/') {
                int len = p2 - p1;
                if (len != 0) {
                    string comp = path.substr(p1, len);
                    if (comp == ".." && !components.empty()) {
                        components.pop();
                    } else if (comp != "." && comp != "..") {
                        components.push(comp); // don't push ".." if component is empty.
                    }
                }
                
                p1 = p2 + 1;
            }
        }
        
        if (components.empty()) {
            return string("/");
        }
        
        string result;
        while (!components.empty()) {
            string comp = components.top();
            result.insert(0, comp);
            result.insert(result.begin(), '/');
            components.pop();
        }
        
        return result;
    }
};

int main () {
    Solution s;
    string test1("/home/");
    string test2("/a/../b/c");
    string test3("/a/././b/../../c/");
    string test4("/../");
    cout << s.simplifyPath(test1) << endl;
    cout << s.simplifyPath(test2) << endl;
    cout << s.simplifyPath(test3) << endl;
    cout << s.simplifyPath(test4) << endl;
}