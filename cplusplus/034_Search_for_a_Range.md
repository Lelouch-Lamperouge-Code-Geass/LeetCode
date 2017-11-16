Given an array of integers sorted in ascending order, find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].

  
# Solution
  
The problem can be simply broken down as two binary searches for the begining and end of the range, respectively. The time complexity is O(logN).
  
While there are some edge cases that you need to think about:

* nums is empty  
* all numbers in nums are smaller than target, in this case the low pointer will >= n  
* all numbers in nums are larger than target, in this case, the low pointer won't move at all, and will stay at index == 0  

As long as nums[low] is confirmed, we know that the range definitely exists.  
  
### Solution one  

```cpp  
class Solution {
public:
  vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> reval(2,-1);
    int low(0),high(nums.size()-1);
    while (low<=high) {
      int mid = low + (high - low) / 2;
      if (nums[mid]>=target) {
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    }

    if (nums[low]!=target) return reval;
    reval[0] = low;

    high = nums.size()-1;
    while (low<=high) {
      int mid = low + (high - low + 1) /2;
      if (nums[mid]>target) {
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    }

    reval[1] = high;

    return reval;
  }
};
```

# Solution two

```cpp
class Solution {
public:
  vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> result(2,-1);
    std::vector<int>::iterator low=std::lower_bound (nums.begin(), nums.end(), target);
    if(*low != target) return result;
    std::vector<int>::iterator up= std::upper_bound (low, nums.end(), target) -1;
    result[0] = low - nums.begin();
    result[1] = up - nums.begin();
    return result;
  }
};
```
