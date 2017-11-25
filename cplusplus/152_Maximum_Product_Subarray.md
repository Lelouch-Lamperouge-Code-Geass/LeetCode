Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4], the contiguous subarray [2,3] has the largest product = 6.
  
# Solution
  
If we know the largest product of contiguous subarray ending with each number in this array. Then the largest product  is the maximum value of them.
  
Then now the problem becomes "how to find the largest product of contiguous subarray ending with current number"?  

Let's use max_product[i] means the largest product of contiguous subarray ending on index i.  
  
1. If current number nums[i] is negative, then we want to use minimum number to multiple with it, in that case, we need min_product[i - 1].  
2. If current number nums[i] is positive, then we want to use maximum number to multiple with it, in that case, we need max_product[i - 1].   
3.   
  

```
class Solution {
public:
  int maxProduct(vector<int>& nums) {
    if (nums.empty()) return INT_MIN;
    const int n (nums.size());
    int pre_max(nums[0]),pre_min(nums[0]),reval(nums[0]);
    for (int i=1;i<n;++i) {
      int cur_max = std::max( std::max (pre_max*nums[i],pre_min*nums[i]),nums[i]);
      int cur_min = std::min( std::min (pre_max*nums[i],pre_min*nums[i]),nums[i]);
      pre_max = cur_max;
      pre_min = cur_min;
      reval = std::max(reval,cur_max);
    }
    return reval;
  }
};
```
