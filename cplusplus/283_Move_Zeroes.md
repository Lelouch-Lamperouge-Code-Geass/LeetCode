Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums should be [1, 3, 12, 0, 0].

Note:
1. You must do this in-place without making a copy of the array.
2. Minimize the total number of operations.

# Solution
  
### Solution one

  This solution doesn't meet the second requirement "Minimize the total number of operations", because there are a lot of swaps here.
  
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

__What if the input vector's length can be larger than 2147483647 ? __

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        std::size_t MINUS_ONE(-1);
        std::size_t exclusive_begin(MINUS_ONE), inclusive_end(0);
        const std::size_t nums_size(nums.size());
        while (inclusive_end < nums_size) {
            if (0 != nums[inclusive_end]) {
                exclusive_begin = (exclusive_begin == MINUS_ONE ? 0 : exclusive_begin + 1);
                std::swap(nums[exclusive_begin], nums[inclusive_end]);
            }
            ++ inclusive_end;
        }
    }
};
```

### Solution two : a better solution

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