Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums should be [1, 3, 12, 0, 0].

Note:
1. You must do this in-place without making a copy of the array.
2. Minimize the total number of operations.

# Solution

This problem is simple. Just note that we need to maintain the relative order of the non-zero elements. And we also need to minimize the total number of operations.


### Solution one

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        std::size_t nonzero_end(0);
        
        // Shift non-zero values as far forward as possible
        for (int num : nums) {
            if (num != 0) {
                nums[nonzero_end] = num;
                ++ nonzero_end;
            }
        }
        
        // Fill remaining space with zeros
        const std::size_t nums_size(nums.size());
        while (nonzero_end < nums_size) {
            nums[nonzero_end] = 0;
            ++ nonzero_end;
        }
    }
};
```

##### Solution two

  
```cpp  
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int exclusive_begin(-1), inclusive_end(0);
        const std::size_t nums_size(nums.size());
        while (inclusive_end < nums_size) {
            if (0 != nums[inclusive_end]) {
                ++ exclusive_begin;
                std::swap(nums[exclusive_begin], nums[inclusive_end]);
            }
            ++ inclusive_end;
        }
    }
};
```
