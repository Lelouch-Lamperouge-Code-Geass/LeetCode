Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.

# Solution
  
### Solution 1, Boyer–Moore majority vote algorithm
   
The Boyer–Moore majority vote algorithm is an algorithm for finding the majority of a sequence of elements using linear time and constant space.
  
In its simplest form, the algorithm finds a majority element, if there is one: that is, an element that occurs repeatedly for more than half of the elements of the input. However, if there is no majority, the algorithm will not detect that fact, and will still output one of the elements. A version of the algorithm that makes a second pass through the data can be used to verify that the element found in the first pass really is a majority.
  
The algorithm will not, in general, find the mode of a sequence (an element that has the most repetitions) unless the number of repetitions is large enough for the mode to be a majority. It is not possible for a streaming algorithm to find the most frequent element in less than linear space, when the number of repetitions can be small.  
  
  
In this problem, since "the array is non-empty and the majority element always exist in the array", we don't need the second loop here to verify the candidate is the major element.  
  
```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate(nums[0]), count(1);
        for (int i = 1, n = nums.size(); i < n; ++i) {
            if (nums[i] == candidate) {
                ++ count;
            } else {
                -- count;
                if (count == 0) {
                    candidate = nums[i];
                    count = 1;
                }
            }
        }
        return candidate;
    }
};
```

### Solution 2, Bit Manipulation


Another nice idea! The key lies in how to count the number of 1's on a specific bit. Specifically, you need a mask with a 1 on the i-the bit and 0 otherwise to get the i-th bit of each element in nums. The code is as follows.

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int major = 0, n = nums.size();
        // For every bit position(32-bit in total), we count how many
        // numbers have set its to be 1.
        for (int i = 0, mask = 1; i < 32; i++, mask <<= 1) {
            int bitCounts = 0;
            for (int j = 0; j < n; j++) {
                if (nums[j] & mask) bitCounts++;
                if (bitCounts > n / 2) {
                    major |= mask;
                    break;
                }
            }
        } 
        return major;
    } 
};
```

