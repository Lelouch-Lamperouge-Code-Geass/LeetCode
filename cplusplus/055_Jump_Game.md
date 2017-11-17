Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false.

# Solution  
  
```cpp  
class Solution {
public:
  bool canJump(vector<int>& nums) {
    std::size_t reach(0), nums_size(nums.size());
    for (std::size_t i = 0;i <= reach && i < nums_size;++i) {
      reach = std::max(reach,i+nums[i]);
    }
    return nums.empty() || reach >= nums_size - 1;
  }
};
```
