A message containing letters from A-Z is being encoded to numbers using the following mapping way:

```
'A' -> 1
'B' -> 2
...
'Z' -> 26
```

Beyond that, now the encoded string can also contain the character '*', which can be treated as one of the numbers from 1 to 9.

Given the encoded message containing digits and the character '*', return the total number of ways to decode it.

Also, since the answer may be very large, you should return the output mod 10^9 + 7.

##### Example 1:

```
Input: "*"
Output: 9
Explanation: The encoded message can be decoded to the string: 
"A", "B", "C", "D", "E", "F", "G", "H", "I".
```

##### Example 2:

```
Input: "1*"
Output: 9 + 9 = 18
```

##### Note:

1. The length of the input string will fit in range [1, 10^5].
2. The input string will only contain the character '*' and digits '0' - '9'.

# Solution

Let count[i] represent the number of decode ways when reach index i of s. The most tricky part is how can we handle case like "\*\*", "\*\*\*", etc. Because how many decode ways on index i, is partailly depended on the value on s[i - 1], means whether s[i - 1] is '0', '1', '2' or other numbers, and '\*' makes it more complicate to handle. 

Let's keep track of:

```
e0 = current number of ways we could decode, ending on any number;
e1 = current number of ways we could decode, ending on an open 1;
e2 = current number of ways we could decode, ending on an open 2;
```

(Here, an "open 1" means a 1 that may later be used as the first digit of a 2 digit number, because it has not been used in a previous 2 digit number.)

With the right idea of what to keep track of, our dp proceeds straightforwardly.

Say we see some character c. We want to calculate f0, f1, f2, the corresponding versions of e0, e1, e2 after parsing character c.

If ```c == '*'```, then the number of ways to finish in total is: we could put * as a single digit number (```9*e0```), or we could pair * as a 2 digit number 1* in ```9*e1``` ways, or we could pair * as a 2 digit number 2* in ```6*e2``` ways. The number of ways to finish with an open 1 (or 2) is just e0.

If ```c != '*'```, then the number of ways to finish in total is: we could put c as a single digit if it is not zero (```(c>'0')*e0```), or we could pair c with our open 1, or we could pair c with our open 2 if it is 6 or less (```(c<='6')*e2```). The number of ways to finish with an open 1 (or 2) is e0 iff ```c == '1'``` (or ```c == '2'```).

```cpp
class Solution {
public:
    int numDecodings(string s) {
        static long max_limit = 1000000007;
        
        // e0 = current number of ways we could decode, ending with any number;
        // e1 = current number of ways we could decode, ending with open 1;
        // e2 = current number of ways we could decode, ending with open 2;
        long e0(1), e1(0), e2(0);
        
        for (char c : s) {
            long f0(0), f1(0), f2(0);
            if (c == '*') {
                f0 = e0 * 9 + e1 * 9 + e2 * 6;
                f1 = e0; // '*' can be treated as open '1'
                f2 = e0; // '*' can be treated as open '2'
            } else {
                f0 = (c > '0'? 1 : 0) * e0 + 1 * e1 + (c <= '6' ? 1 : 0) * e2;
                f1 = (c == '1' ? e0 : 0);
                f2 = (c == '2' ? e0 : 0);
            }
            
            e0 = f0 % max_limit;
            e1 = f1;
            e2 = f2;
        }
        
        return e0;
    }
};
```

Maybe a more clear style.

```cpp
class Solution {
public:
    int numDecodings(string s) {
        static long max_limit = 1000000007;
        
        // pre_end_with_any referes to previous strings which end with any char,
        // it will not be used to pair with following chars. pre_end_with_one refers to
        // number of previous strings which end with an open '1', 
        // it is used only to pair with following chars.
        // Same as pre_end_with_two.
        long pre_end_with_any(1), pre_end_with_one(0), pre_end_with_two(0);
        
        for (char c : s) {
            long cur_end_with_any(0), cur_end_with_one(0), cur_end_with_two(0);
            
            if (c == '*') {
                cur_end_with_any =  (pre_end_with_any * 9 + pre_end_with_one * 9 + pre_end_with_two * 6);
                cur_end_with_one = pre_end_with_any; // '*' can be treated as open '1'
                cur_end_with_two = pre_end_with_any; // '*' can be treated as open '2'          
            } else {
                cur_end_with_any = (c != '0' ? pre_end_with_any : 0) 
                                    + pre_end_with_one 
                                    + (c >= '0' && c <= '6' ? pre_end_with_two : 0);
                cur_end_with_one = (c == '1'? pre_end_with_any : 0);
                cur_end_with_two = (c == '2'? pre_end_with_any : 0);
            }
            
            pre_end_with_any = cur_end_with_any % max_limit;
            pre_end_with_one = cur_end_with_one;
            pre_end_with_two = cur_end_with_two;
        }
        
        return pre_end_with_any;
    }
};
```
