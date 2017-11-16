Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.
  
# Solution

In this problem, the array is sorted in __ascending order__ and rotated at some pivot.

In the description, it also mentioned that __no duplicate exists__ in the array. Note if there are duplicates, below solution needs to be adjusted.

We all know how to do binary search on a sorted array. Right now the array is rotated, then this array will have two sorted sub-array.
We can still do binary search here.

We begin with ```low = 0, high = n -1```.

Then ```mid = low + (high - low) / 2```.
  
Notice that nums[mid] can have two status, each status divide the vectory into two parts, at least one part is a sorted array, another part might be rotated or sorted. We can always check whether the target value is in the sorted part by comparing target with the minimum value and maximum value of the sorted part. 

Once we confirmed that the target is within this range, we just need to change low and high pointers to point to this sorted range and in following steps we only need to do binary search here.

If the target is not within the sorted range, we can adjust low and high pointers to discard the sorted part.

__Time complexity is O(logN).__

```
If nums[mid] == target, return mid.

Else :
(1) nums[mid] < nums[high], then [mid,high] is increasing.
    * Target is in this range, make low = mid + 1.
    * Target is not in this range, make high = mid - 1
(2) nums[mid] > nums[high], then [low,mid] is increasing.
    * Target is in this range, make high = mid - 1.
    * Target is not in this range, make low = mid + 1
```

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
          // target is within the sorted range.
          low = mid + 1;
        } else {
          // target is NOT　within the sorted range.
          high = mid -1;
        }
      } else {
        if(target>=nums[low] && target < nums[mid]){
          // target is within the sorted range.
          high = mid - 1;
        } else {
          // target is NOT　within the sorted range.
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
                } else { // nums[high] > nums[mid], [mid,high] monotonically increasing
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
