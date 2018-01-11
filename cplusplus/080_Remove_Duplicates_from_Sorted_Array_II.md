Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the new length.

# Solution

### Solution one

I like this solution because it is straightforward, and easy to be expanded to "duplicates are allowed at most K times".

If duplicates are allowed at most k times, we just change the ```count < 2``` here to be ```count < k```.

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;
        int len(1);
        int cur_num(nums[0]), count(1);
        for (int i = 1, n = nums.size(); i < n; ++i) {
            if (nums[i] == cur_num) {
                if (count < 2) { 
                    nums[len++] = nums[i];
                }
                ++ count;
            } else {
                nums[len++] = nums[i];
                cur_num = nums[i];
                count = 1;
            }
        }
        return len;
    }
};
```

### Solution two

I actually don't like this solution, since it is not straightforwad, and it is hard to be adjusted to  "duplicates are allowed at most K times".

__Note here we compare each number with nums[i-2].__

```cpp
int removeDuplicates(vector<int>& nums) {
    int i = 0;
    for (int n : nums)
        if (i < 2 || n > nums[i-2])
            nums[i++] = n;
    return i;
}
```
