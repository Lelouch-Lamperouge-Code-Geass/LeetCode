Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

For example,
Given input array nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. It doesn't matter what you leave beyond the new length.

# Solution

### Solution one

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty()) return 0;
        std::size_t index(0);
        for(std::size_t i=1;i<nums.size();++i){
            if(nums[i]!=nums[index]){
                nums[++index] = nums[i];
            }
        }
        return index + 1;
    }
};
```

### Solution two
```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int len(0);
        
        for (int num : nums) {
            if (len == 0 || num != nums[len - 1]){
                nums[len++] = num;
            }
        }
        
        return len;
    }
};
```
