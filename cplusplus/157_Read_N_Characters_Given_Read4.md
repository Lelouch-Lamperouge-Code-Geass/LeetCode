The API: ```int read4(char *buf)``` reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function ```int read(char *buf, int n)``` that reads n characters from the file.

# Solution

This problem's description is pretty bad.

Actually, this question may be more practical than it looks like at your first glimpse.

In reality, hardware or system may have constraints for read from file system. eg. hardeware DMA engine may fetch data 128 bytes from disk. another example is that loading 4-bytes in aligned ddr should be obviously faster than load 1 byte 4 times. It is exactly same as read4 problem.

However, I still don't think this is a good interview question. The concept behind the problem is important, but a knowledge-based question is enough.

Edge cases:

1. The final read may not need 4 chars.
2. __The ``` read4(char *buf)``` function does not move buff pointer forward, notice that here it is passed by copy pointer__.

```cpp
// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    
    int read(char *buf, int n) {
        int count(0), char_read(0);
        
        while (n > 0) {
            // How many chars we read by calling API
            char_read = read4(buf); 
            // How many chars we can actually add to buffer
            int can_add = std::min(n, char_read); 
            buf += can_add; // Move buffer's pointer forward
            n -= can_add; 
            count += can_add;
            if (char_read < 4) break; // Can't read from API anymore
        }
        
        return count;
    }

};
```
