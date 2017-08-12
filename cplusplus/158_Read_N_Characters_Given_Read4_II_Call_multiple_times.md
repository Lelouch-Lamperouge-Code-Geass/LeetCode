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

```jave
/* The read4 API is defined in the parent class Reader4.
      int read4(char[] buf); */

public class Solution extends Reader4 {
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */

    private int buffPtr = 0;
    private int buffCnt = 0;
    private char[] buff = new char[4];
    
    public int read(char[] buf, int n) {
        int ptr = 0;
        while (ptr < n) {
            if (buffPtr == 0) {
                buffCnt = read4(buff);
            }
            if (buffCnt == 0) break;
            while (ptr < n && buffPtr < buffCnt) {
                buf[ptr++] = buff[buffPtr++];
            }
            if (buffPtr >= buffCnt) buffPtr = 0;
        }
        return ptr;
    }
```
