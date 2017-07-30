A peak element is an element that is greater than its neighbors.

Given an input array where num[i] ≠ num[i+1], find a peak element and return its index.

The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.

You may imagine that num[-1] = num[n] = -∞.

For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.

Your solution should be in logarithmic complexity.
  
# Solution
  
I find it useful to reason about binary search problems using invariants.

Assume we initialize left = 0, right = nums.length - 1. The invariant I'm using is the following:

  nums[left - 1] < nums[left] && nums[right] > nums[right + 1]
  
  
```cpp
class Solution {
public:
  /*
   * The key point is to find out whether nums[mid]
   * is on upslope or downslope.
   */
  int findPeakElement(vector<int>& nums) {
    int low(0),high(nums.size()-1);
    while (low<high) {
      int mid = low + (high - low)/2;
      if (nums[mid]>nums[mid+1]) { // downslope
        high = mid;
      } else { //upslope or flat
        low = mid + 1;
      }
    }
    return low;
  }
};
```
