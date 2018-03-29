Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].

Solve it without division and in O(n).

For example, given [1,2,3,4], return [24,12,8,6].

Follow up:
Could you solve it with constant space complexity? (Note: The output array does not count as extra space for the purpose of space complexity analysis.)

# Solution
  
```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        const std::size_t nums_size(nums.size());
        vector<int> reval(nums_size, 1);
        
        int pre(1);
        for (std::size_t i = 0; i < nums_size; ++i) {
            reval[i] *= pre;
            pre *= nums[i];
        }
        
        pre = 1;
        for (std::size_t i = nums_size; i-- > 0;) {
            reval[i] *= pre;
            pre *= nums[i];
        }
        
        return reval;
    }
    
};
```

A different style.

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        const int n = nums.size();
        vector<int> reval(n, 1);
        
        int carry(1), counter_carry(1);
        
        for (int i = 0; i < n; ++i) {
            int counter_i = n - i - 1;
            
            reval[i] *= carry;
            reval[counter_i] *= counter_carry;
            
            carry *= nums[i];
            counter_carry *= nums[counter_i];
        }
        
        return reval;
    }
};
```
