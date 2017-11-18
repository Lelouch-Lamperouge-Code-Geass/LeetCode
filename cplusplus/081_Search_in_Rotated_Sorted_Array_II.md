Follow up for "Search in Rotated Sorted Array":

What if duplicates are allowed?

Would this affect the run-time complexity? How and why?
  
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Write a function to determine if a given target is in the array.

The array may contain duplicates.
  
# Solution

When there could be duplicates in the array, the worst case time complexity is __O(n)__.  
  
```cpp
class Solution {
public:
  bool search(vector<int>& nums, int target) {
    int low(0),high(nums.size()-1);
    while(low <= high){
      int mid = low + (high - low)/2;
      if(nums[mid] == target){
        return true;
      } else {
        if(nums[mid] < nums[high]){ // [mid,high] is sorted
          if(target > nums[mid] && target <= nums[high]){
            // target is within this sorted range
            low = mid + 1;
          } else {
           // target is NOT　within this sorted range
            high = mid - 1;
          }
        } else if(nums[mid] > nums[high]){// [low,mid] is sorted
          if(target >= nums[low] && target < nums[mid]){
            // target is within this sorted range
            high = mid - 1;
          } else {
          　// target is NOT　within this sorted range
            low = mid + 1;
          }
        } else {//nums[mid] == nums[high]
          --high;
        }
      }
    }
    return false;
  }
};
```

If int range is not good enough, we may need std::size_t.
  
It is no different from above solution except that we need prevent overflow.
  
```cpp
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        if (nums.empty()) return false;
        
        std::size_t low(0), high(nums.size() - 1);
        
        while (low <= high) {
            std::size_t mid = low + (high - low) / 2;
            
            if (nums[mid] == target) {
                return true;
            } else {
                if (nums[mid] > nums[high]) { // [mid,high] is sorted
                    if (nums[low] <= target && nums[mid] > target) {
                        // target is within this sorted range
                        if (mid == 0) return false;
                        high = mid - 1;
                    } else {
                        // target is NOT within this sorted range
                        low = mid + 1;
                    }
                } else if (nums[mid] < nums[high]) {
                    if (nums[mid] < target && nums[high] >= target) {
                    // target is within this sorted range
                        low = mid + 1;
                    } else {
                        // target is NOT within this sorted range
                        if (mid == 0) return false;
                        high = mid - 1;
                    }
                } else { // nums[mid] == nums[high]
                    if (high == 0) return false;
                    -- high;
                }
            }
        }
        
        return false;
    }
};
```
