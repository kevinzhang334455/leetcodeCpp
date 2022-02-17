#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    bool validWordAbbreviation(string word, string abbr) {
        int len = 0;
        int i = 0, j = 0;
        while (i != word.size() && j != abbr.size()) {
            if (isdigit(abbr[j])) {
                // avoid leading 0s
                if (len == 0 && abbr[j] == '0') {
                    break;
                }
                
                len = len * 10 + (abbr[j] - '0');
                j++;
            } else {
                if (len != 0) {
                    i += len;
                    len = 0;
                }
                
                if (i >= word.size() || word[i] != abbr[j]) {
                    break;
                } else {
                    i++;
                    j++;
                }
            }
        }
        
        if (len != 0) {
            i += len;
        }
        
        return i == word.size() && j == abbr.size();
    }
};

int main () {
    Solution s;
    cout << s.validWordAbbreviation("internationalization", "i12iz4n") << endl;
}