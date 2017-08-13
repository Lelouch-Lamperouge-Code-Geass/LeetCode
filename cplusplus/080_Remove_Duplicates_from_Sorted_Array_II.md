Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the new length.

# Solution

### Solution one

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 2) return nums.size();
        
        std::size_t index(0);
        
        for (std::size_t i = 0; i < nums.size(); ) {
            const int cur_num(nums[i]);
            int count(0);
            
            while (i < nums.size() && nums[i] == cur_num) {
                ++ count;
                ++ i;
            }    
            
            count = std::min(count, 2);
            while (count > 0) {
                -- count;
                nums[index++] = cur_num;
            }
        }
        
        return index;
    }
};
```

### Solution two

```cpp
int removeDuplicates(vector<int>& nums) {
    int i = 0;
    for (int n : nums)
        if (i < 2 || n > nums[i-2])
            nums[i++] = n;
    return i;
}
```
