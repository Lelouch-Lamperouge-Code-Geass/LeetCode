The count-and-say sequence is the sequence of integers with the first five terms as following:

```
1.     1
2.     11
3.     21
4.     1211
5.     111221
```

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.
Given an integer n, generate the nth term of the count-and-say sequence.

Note: Each term of the sequence of integers will be represented as a string.

Example 1:

```
Input: 1
Output: "1"
```

Example 2:

```
Input: 4
Output: "1211"
```

# Pitcall

How to handle last char.

# Solution


```cpp
class Solution {
public:
    string countAndSay(int n) {
        if (n <= 0) return "";
        string reval("1");
        -- n;
        while (n-- > 0) {
            std::size_t count(0);
            char cur_char(reval[0]);
            std::string new_reval("");
            const std::size_t reval_size(reval.size());
            for (std::size_t i = 0; i <= reval_size; ++i) {
                if (i == reval_size) {
                    new_reval += std::to_string(count) + cur_char; 
                } else if (reval[i] != cur_char) {
                    new_reval += std::to_string(count) + cur_char;                
                    cur_char = reval[i]; 
                    count = 1;
                } else {
                    ++ count;
                }
            }
            
            reval = new_reval;
        }
        
        return reval;
    }
};
```

# knowledge

### Run-length encoding

Run-length encoding (RLE) is a very simple form of lossless data compression in which runs of data (that is, sequences in which the same data value occurs in many consecutive data elements) are stored as a single data value and count, rather than as the original run. This is most useful on data that contains many such runs. Consider, for example, simple graphic images such as icons, line drawings, and animations. It is not useful with files that don't have many runs as it could greatly increase the file size.

For example, consider a screen containing plain black text on a solid white background. There will be many long runs of white pixels in the blank space, and many short runs of black pixels within the text. A hypothetical scan line, with B representing a black pixel and W representing white, might read as follows:

```
WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW
```

With a run-length encoding (RLE) data compression algorithm applied to the above hypothetical scan line, it can be rendered as follows:

```
12W1B12W3B24W1B14W
```

The run-length code represents the original 67 characters in only 18. While the actual format used for the storage of images is generally binary rather than ASCII characters like this, the principle remains the same. Even binary data files can be compressed with this method; file format specifications often dictate repeated bytes in files as padding space.

