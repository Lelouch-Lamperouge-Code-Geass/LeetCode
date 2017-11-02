Given a non-negative integer, you could swap two digits at most once to get the maximum valued number. Return the maximum valued number you could get.

##### Example 1:

```
Input: 2736
Output: 7236
Explanation: Swap the number 2 and the number 7.
```

##### Example 2:

```
Input: 9973
Output: 9973
Explanation: No swap.
```

##### Note:

* The given number is in the range [0, 10 ^ 8]

# Solution

__Note that the number is non-negative, otherwise below solution won't work!__

### Solution one

__The key is to make sure for each digit, there is a larger digit after it. Then it means we can swap it. If multiple same large digits exist  after that, try to swap the rightmost one.__

Use buckets to record the last position of digit 0 ~ 9 in this num.

Loop through the num array from left to right. For each position, we check whether there exists a larger digit in this num (start from 9 to current digit). We also need to make sure the position of this larger digit is behind the current one. If we find it, simply swap these two digits and return the result.

__Time complexity O(N), space compleixty O(1).__

```cpp
class Solution {
public:
    int maximumSwap(int num) {
        std::string str(std::to_string(num));
        
        std::vector<std::size_t> last_positions(10,0);

        for (std::size_t i = 0, n = str.size();i < n; ++i) {
            last_positions[str[i] - '0'] = i;
        }
        
        for (std::size_t i = 0, n = str.size(); i < n; ++i) {
            for (int digit = 9; digit > str[i] - '0'; --digit) {
                if (last_positions[digit] > i) {
                    std::swap(str[i], str[last_positions[digit]]);
                    return std::stoi(str);
                }    
            }
            
        }
        
        return num; // No swap
    }
};
```

### Solution two

We only need to record a position array (pos[i]) which represent the largest number index form the i position.

For instance,

```
input 9 8 6 3 8
pos 0 4 4 4 4
input[pos] 9 8 8 8 8
```

Therefore, we only need to find the first input[i] != input[pos[i]]
and swap it.

Another example

```
input 5 4 3 1 2
pos 0 1 2 4 4
input[pos] 5 4 3 2 2
```

Note that using largest_digit_behind[i] != i won't work here, e.g 98368 => 98368,  1993 => 9193.

If for same digit, we record the rightmost.

```
input : 98368
pos : 04444

Then the second digit will be the first one that makes largest_digit_behind[i] != i
```

If for same digit we don't record the leftmost, that won't work.

```
input: 1993
pos: 1123
```
__Time complexity O(N), space compleixty O(N).__

```cpp
class Solution {
public:
    int maximumSwap(int num) {
        std::string str(std::to_string(num));
        
        const std::size_t n(str.size());
        std::vector<std::size_t> largest_digit_behind(n, -1);
    
        std::size_t cur_max_pos(n - 1);    
        for (std::size_t i = n; i -- > 0; ) {
            if (str[i] > str[cur_max_pos]) {
                cur_max_pos = i;
            }
            largest_digit_behind[i] = cur_max_pos;
        }
        
        for (std::size_t i = 0; i < n; ++i) {
            if (str[largest_digit_behind[i]] != str[i]) { 
                std::swap(str[i], str[largest_digit_behind[i]]);
                return std::stoi(str);
            }
        }
        
        return num; // No swap
    }
};
```
