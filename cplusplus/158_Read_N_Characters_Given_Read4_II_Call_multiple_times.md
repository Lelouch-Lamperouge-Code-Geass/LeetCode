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

__Note that read4 function will read chars into the buffer, but since the pointer is copied by value, it won't actually increase the buffer pointer's address. In this solution, our private buffer's address won't change at all, but we need increas pointer ```buf```.__

```cpp
// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
private:
    int m_buff_pos = 0;
    int m_buff_end = 0;
    char m_buff[4];
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int reval(0);
        while (n > 0) {
            // As long as we have characters in private buffer,
            // read from private buffer.
            if (m_buff_pos < m_buff_end) {
                while (n > 0 && m_buff_pos < m_buff_end) {
                    *buf = m_buff[m_buff_pos];
                    ++ buf;
                    ++ m_buff_pos;
                    ++ reval;
                    -- n;
                }
            }
            
            // All the characters in private buffer has been read.
            // Read from file to private buffer.
            if (m_buff_pos == m_buff_end) {
                int chars_read = read4(m_buff);
                if (chars_read == 0) return reval; // No more characters in file!
                m_buff_end = chars_read;
                m_buff_pos = 0;
            }
            
        }
        
        return reval;
    }
};
```

Same methodology, different style.

```cpp
// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
private:
    char m_buf[4];
    int m_buf_pos = 0;
    int m_end_of_buf = 0;
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int to_read(n);
        bool end_of_file(false);
        while (to_read > 0) {
            // If private buffer has chars, read from it.
            while (m_buf_pos != m_end_of_buf && to_read > 0) {
                *buf = m_buf[m_buf_pos];
                ++ buf, ++m_buf_pos, -- to_read;
            }
            
            if (end_of_file) break; // No chars left in file
            
            // Only read from file when private buffer's chars
            // have been all read.
            if (m_buf_pos == m_end_of_buf) {
                m_buf_pos = m_end_of_buf = 0;
                int num_of_chars = read4(m_buf);
                end_of_file = num_of_chars < 4 ? true : false;
                m_end_of_buf += num_of_chars;
            }
        }
        
        return n - to_read;
    }
};
```
