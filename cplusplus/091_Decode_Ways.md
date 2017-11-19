A message containing letters from A-Z is being encoded to numbers using the following mapping:

```
'A' -> 1
'B' -> 2
...
'Z' -> 26
```

Given an encoded message containing digits, determine the total number of ways to decode it.  

For example,  
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).  

The number of ways decoding "12" is 2.  

# Solution

### Solution one

Let's use decode_ways[i] to record how many decode ways we can have for substring [0, i] from input string s.

If s[i] is from '1' to '9', we know that we can simply make ```decode_ways[i] += decode_ways[i-1]```, this means that s[i] can extend string[0,i-1] and maintain ths extended string valid by treating s[i] independent. No more no less. This encode way can be expressed as
```[s[0,i-1], s[i]]```. And you can see, if s[i] == '0', this encode way won't work.

And we can also use another expression ```[s[0,i-2], s[i-1, i-2]]```  if the number made of s[i-1, i-2] is within [10,26]. Here we have one edge case which is when i is equals to 1.

```cpp
class Solution {
public:
    int numDecodings(string s) {
        if (s.empty()) return 0;
        
        const std::size_t n(s.size());
        vector<int> decode_ways(n, 0);
        
        decode_ways[0] = s[0] != '0' ? 1 : 0;
        
        for (std::size_t i = 1; i < n; ++i) {
            if (s[i] != '0') decode_ways[i] += decode_ways[i - 1];
            
            if (i >= 1) {
                int val = (s[i-1] - '0') * 10 + (s[i] - '0');
                if (val >= 10 && val <= 26) decode_ways[i] += (i >= 2 ? decode_ways[i - 2] : 1);
            }
        }
        
        return decode_ways[n - 1];
    }
};
```

Of course, you can optimize this solution to have O(1) space complexity.


### Solution two

Get inspiration from this problem : https://leetcode.com/problems/decode-ways-ii/description/.

Here we use:

* e0 = current number of ways we could decode, ending with any number;  
* e1 = current number of ways we could decode, ending with open 1;
* e2 = current number of ways we could decode, ending with open 2;

(Here, an "open 1" means a 1 that may later be used as the first digit of a 2 digit number, because it has not been used in a previous 2 digit number.)

__Then the number of ways to finish in total is: we could put c as a single digit if it is not zero (```(c>'0')*e0```), or we could pair c with our open 1, or we could pair c with our open 2 if it is 6 or less (```(c<='6')*e2```).__ The number of ways to finish with an open 1 (or 2) is e0 iff ```c == '1'``` (or ```c == '2'```).

```cpp
class Solution {
public:
    int numDecodings(string s) {
        if (s.empty() || s[0] == '0') return 0;
        
        // e0 = current number of ways we could decode, ending with any number;
        // e1 = current number of ways we could decode, ending with open 1;
        // e2 = current number of ways we could decode, ending with open 2;
        int e0(1), e1(0), e2(0);
        
        int f0(0), f1(0), f2(0);
        
        for (char c : s) {
            f0 = e0 * (c > '0' ? 1 : 0) + e1 * 1 + e2 * (c <= '6' ? 1 : 0);
            f1 = (c == '1' ? e0 : 0);
            f2 = (c == '2' ? e0 : 0);
            
            e0 = f0;
            e1 = f1;
            e2 = f2;
        }
        
        return e0;
    }
};
```
