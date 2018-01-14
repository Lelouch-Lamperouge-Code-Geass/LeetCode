The API: ```int read4(char *buf)``` reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function ```int read(char *buf, int n)``` that reads n characters from the file.

Note:

The read function may be called multiple times.

# Solution

What is the difference between call once and call multiple times?

The only thing is when you call read4() which reads 4 bytes into your buffer you might read more than you need, so you want to store those bytes in the structure, and next time you call read will start from those stored bytes, then read more from the file.

Think that you have 4 chars "a, b, c, d" in the file, and you want to call your function twice like this:

```
read(buf, 1); // should return 'a'
read(buf, 3); // should return 'b, c, d'
```

All the 4 chars will be consumed in the first call. So the tricky part of this question is how can you preserve the remaining 'b, c, d' to the second call.

Therefore, we maintain a private buffer, and we need to read from file whenever m_pos is 0. Otherwise, we need to copy chars from private buffer to final buffer.

In short, if we have chars in private buffer, read them to output buffer first. Otherwise, read from file and put chars to private buffer. Therefore, we read chars from file to private buffer, and read chars from private buffer to output buffer.

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
        int count(0);
        
        while (count < n) {
            // Read into private buffer
            if (m_pos == 0) {
                m_buff_count = read4(m_buff);
            }
            
            if (m_buff_count == 0) break;

            // Read from private buffer to output buffer.
            while (count < n && m_pos < m_buff_count) {
                *buf = m_buff[m_pos];
                ++ buf, ++ m_pos, ++ count;
            }
            
            if (m_pos >= m_buff_count) m_pos = 0;
        }
        
        return count;
    }
private:
    int m_pos = 0;
    int m_buff_count = 0;
    char m_buff[4];
};
```
