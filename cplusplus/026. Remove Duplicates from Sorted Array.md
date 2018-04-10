Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

For example,
Given input array nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. It doesn't matter what you leave beyond the new length.

# Solution

The basic idea is, we use ```unique_index``` represents the the current index of "unique array". And then we iterate nums, and since nums is sorted, we can check each number with its previous number to see whether it is a duplicate one. If not we just put it into ```nums[unique_index++]```. One interesting fact is that the gap between ```unique_index``` and ```i``` are area which is safe to overwrite, and the gap difference is how many duplicates we have meet so far. 

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
