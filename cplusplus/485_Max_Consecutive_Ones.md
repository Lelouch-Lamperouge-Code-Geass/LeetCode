Given a binary array, find the maximum number of consecutive 1s in this array.

#### Example 1:

```
Input: [1,1,0,1,1,1]
Output: 3
Explanation: The first two digits or the last three digits are consecutive 1s.
    The maximum number of consecutive 1s is 3.
```

##### Note:

* The input array will only contain 0 and 1.
* The length of input array is a positive integer and will not exceed 10,000

# Solution

```cpp
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int max_len(0), cur_len(0);
        
        for (int num : nums) {
            if (num == 1) {
                ++ cur_len;
            } else {
                cur_len = 0;
            }
            max_len = std::max(max_len, cur_len);
        }
        
        return max_len;
    }
};
```
