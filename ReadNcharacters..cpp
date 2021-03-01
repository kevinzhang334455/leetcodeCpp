#include <queue>
using namespace std;
/**
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf4);
 */

// We can consider layering this and define what layer should do what jobs:
// 1. read4 layer
//    -- determine whether it reach EOF by determine whether the # of characters is < 4.
// 2. readn layer
//    -- if n < 4, then save the remaining chars for next read.
//    -- flip the flag iff EOF is raised by read4
//    -- keep reading until n is fufilled.
//    -- count the chars that returned by the readn function. 

int read4(char *buf4);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char *buf, int n) {
        if (n <= 0) {
            return 0;
        }
        
        int count = 0;

        // read remaining buffer first.
        while (!buffer.empty() && count < n) {
            buf[count++] = buffer.front();
            buffer.pop();
        }
        
        // read the file by calling read 4.
        while (!eof && count < n) {
            int num_to_read = std::min(4, n - count);
            char* buf4 = new char[4];
            int read = read4(buf4);
            if (read < 4) {
                eof = true;
            }
            
            for (int i = 0; i < read; i++) {
                if (i < num_to_read) {
                    buf[count + i] = buf4[i];
                } else {
                    buffer.push(buf4[i]);
                }
            }
            
            count += min(num_to_read, read);
        }
        
        return count;
    }
    
private:
    bool eof = false;
    queue<char> buffer;
};