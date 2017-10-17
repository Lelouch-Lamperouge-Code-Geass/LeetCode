A peak element is an element that is greater than its neighbors.

Given an input array where num[i] ≠ num[i+1], find a peak element and return its index.

The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.

You may imagine that num[-1] = num[n] = -∞.

For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.

Your solution should be in logarithmic complexity.
  
# Solution

It's easy to know this problem can be solve by using binary search.

The problem is that we can't compare nums[mid] with nums[low] or nums[high] to narrow down range.

Why ? 

1. Let's assume nums[mid] > nums[high], does that mean there is definitely a peak between [low, mid] ? NO!
   Does that mean there is definitely a peak between [mid, high] ? NO!
2. Same for nums[mid] < nums[high].  

While if we choose to compare nums[mid] with nums[mid + 1]:

1. If nums[mid] > nums[mid + 1], there is definitely a peak between [low, mid].
2. If nums[mid] < nums[mid + 1], there is definitely a peak between [mid+1, high].  
3. Note that nums[mid] can't be the same as nums[mid + 1].  

By comparing nums[mid] with its neighbor, we can know the slope is going upward or downward, which indicates where we can find a peak.


I find it useful to reason about binary search problems using invariants.

Assume we initialize left = 0, right = nums.length - 1. The invariant I'm using is the following:

``` nums[left - 1] < nums[left] && nums[right] > nums[right + 1] ```

That basically means that in the current interval we're looking, [left, right] the function started increasing to left and will eventually decrease at right. The behavior between [left, right] falls into the following 3 categories:

1. nums[left] > nums[left + 1]. From the invariant, nums[left - 1] < nums[left] => left is a peak

2. The function is increasing from left to right i.e. nums[left] < nums[left + 1] < .. < nums[right - 1] < nums[right]. From the invariant, nums[right] > nums[right + 1] => right is a peak

3. the function increases for a while and then decreases (in which case the point just before it starts decreasing is a peak) e.g. 2 5 6 3 (6 is the point in question)
  
As shown, if the invariant above holds, there is at least a peak between [left, right]. Now we need to show 2 things:

1. the invariant is initially true. Since left = 0 and right = nums.length - 1 initially and we know that nums[-1] = nums[nums.length] = -oo, this is obviously true

2. At every step of the loop the invariant gets reestablished. If we consider the code in the loop, we have mid = (left + right) / 2 and the following 2 cases:
  * nums[mid] < nums[mid + 1]. It turns out that the interval [mid + 1, right] respects the invariant (nums[mid] < nums[mid + 1] -> part of the cond + nums[right] > nums[right + 1] -> part of the invariant in the previous loop iteration)
  * nums[mid] > nums[mid + 1]. Similarly, [left, mid] respects the invariant (nums[left - 1] < nums[left] -> part of the invariant in the previous loop iteration and nums[mid] > nums[mid + 1] -> part of the cond)  

As a result, the invariant gets reestablished and it will also hold when we exit the loop. In that case we have an interval of length 2 i.e. right = left + 1. If nums[left] > nums[right], using the invariant (nums[left - 1] < nums[left]), we get that left is a peak. Otherwise right is the peak (nums[left] < nums[right] and nums[right] < nums[right + 1] from the invariant).

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
