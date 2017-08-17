Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.
  
# Solution
  
Notice that nums[mid] can have two status, each status divide the 
vectory into two parts.
(1) nums[mid] < nums[high], then [mid,high] is increasing
(2) nums[mid] > nums[high], then [low,mid] is increasing
We can use binary search based on the status.

```cpp  
class Solution {
public:
  int search(vector<int>& nums, int target) {
    int low(0),high(nums.size()-1);
    while(low<=high){
      int mid = low + (high-low)/2;
      if(nums[mid] == target) return mid;
      if(nums[mid]<nums[high]){
        if(target>nums[mid] && target <= nums[high]){
          low = mid + 1;
        } else {
          high = mid -1;
        }
      } else {
        if(target>=nums[low] && target < nums[mid]){
          high = mid - 1;
        } else {
          low = mid + 1;
        }
      }
    }
    return -1;
  }
};
```

If the input vector's size is quite big, we need to use std::size_t.
  
```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.empty()) return -1;
        
        std::size_t low(0), high(nums.size() - 1);
        
        while (low <= high) {
            std::size_t mid = low + (high - low) / 2;
            if (nums[mid] == target) {
                return mid;
            } else {
                if (nums[high] < nums[mid]) { // [low,mid] monotonically increasing
                    if (target >= nums[low] && target < nums[mid]) {
                        if (mid == 0) break;
                        high = mid - 1;
                    } else {
                        low = mid + 1;
                    }
                } else { // nums[high] >= nums[mid], [mid,high] monotonically increasing
                    if (target > nums[mid] && target <= nums[high]) {
                        low = mid + 1;
                    } else {
                        if (mid == 0) break;
                        high = mid - 1;
                    }
                }
            }
        }
        
        return -1;
    }
};
```
