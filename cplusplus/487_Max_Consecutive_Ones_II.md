Given a binary array, find the maximum number of consecutive 1s in this array if you can flip at most one 0.

##### Example 1:

```
Input: [1,0,1,1,0]
Output: 4
Explanation: Flip the first zero will get the the maximum number of consecutive 1s.
    After flipping, the maximum number of consecutive 1s is 4.
```

##### Note:

* The input array will only contain 0 and 1.
* The length of input array is a positive integer and will not exceed 10,000

##### Follow up:

What if the input numbers come in one by one as an infinite stream? In other words, you can't store all numbers coming from the stream as it's too large to hold in memory. Could you solve it efficiently?

# Solution

The idea is to keep a window [l, h] that contains at most k zero

The following solution does not handle follow-up, because nums[l] will need to access previous input stream
__Time: O(n) Space: O(1)__

```cpp
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        const std::size_t n(nums.size());
        
        std::size_t start(0), max_len(0), zero_count(0);
        
        for (std::size_t i = 0; i < n; ++i) {
            if (nums[i] == 0) ++ zero_count;
            
            while (zero_count > 1) {
                if (nums[start] == 0) --zero_count;
                ++ start;
            }
            
            max_len = std::max(max_len, i - start + 1);
        }
        
        return max_len;
    }
};
```


Now let's deal with follow-up, since the input numbers is an infinite stream and we can't store it in memory, we can store up to k indexes of zero within the window [l, h] so that we know where to move l next when the window contains more than k zero. If the input stream is infinite, then the output could be extremely large because there could be super long consecutive ones. In that case we can use BigInteger for all indexes. For simplicity, here we will use int
Time: O(n) Space: O(k).

```cpp
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        const std::size_t n(nums.size());
        
        std::size_t start(0), max_len(0), zero_count(0);
        std::deque<std::size_t> zero_indexes;
        for (std::size_t i = 0; i < n; ++i) {
            if (nums[i] == 0) {
                zero_indexes.emplace_back(i);
            } 
            
            if (zero_indexes.size() > k) {
                start = zero_indexes.front() + 1;
                zero_indexes.pop_front();
            }
            
            max_len = std::max(max_len, i - start + 1);
        }
        
        return max_len;
    }
};
```

Note that setting k = 0 will give a solution to the earlier version [Max Consecutive Ones](https://leetcode.com/problems/max-consecutive-ones/description/).

For k = 1 we can apply the same idea to simplify the solution. Here q stores the index of zero within the window [l, h] so its role is similar to Queue in the above solution.

```cpp
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        const std::size_t n(nums.size());
        
        std::size_t start(0), max_len(0), zero_index(-1); // Intended overflow for zero_index
        for (std::size_t i = 0; i < n; ++i) {
            if (nums[i] == 0) {
                start = zero_index + 1;
                zero_index = i;
            } 
            
            max_len = std::max(max_len, i - start + 1);
        }
        
        return max_len;
    }
};
```










