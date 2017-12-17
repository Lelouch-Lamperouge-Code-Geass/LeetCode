Follow up for "Find Minimum in Rotated Sorted Array":

What if duplicates are allowed?

Would this affect the run-time complexity? How and why?
 
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

The array may contain duplicates.

# Solution

For problems similar using binary search, we need to make sure two conditions are satisfied:

1. __Loop Invariant__: An assertion about the current state useful for designing, analyzing and proving the correctness of iterative algorithms.  
2. __Exit condition__: The statement of what must be true to exit a loop. 
 
In sort, we need to make sure the element we are seeking is within the narrowed range, and we also need to make sure we can exit the loop eventually.

When low <= high:

1. If nums[mid] > nums[high] : we know that the element is on the right side of mid, therefore low = mid + 1;
2. If nums[mid] < nums[high] : we know that the element is on the left side but it is also possible on mid posiition, therefore high = mid;
3. If nums[mid] == nums[high] : we can only decrease high in this condition.

 ```
 case 1 : 3,3,3,3,3,3,3,3,0,1,2,3
 case 2 : 3,3,0,1,2,3,3,3,3,3,3,3
 ```
 
Therefore, when nums[mid] == nums[high], we can only decrease high.I prefer to compare nums[mid] with nums[high] instead of nums[low],
because nums[mid] could equal to nums[low] which is one more scenario we have to handle.

You can see that here, whenever we try to narrow down the range, we always make sure that the element is in the narrowed range.
 
We also observe that we can exit this loop because we always reduce the range on every loop step.
 
And based on the loop condition, we know for sure that eventually, high will be smaller than low.
 
The number we are looking for is on nums[low]. 
 
```cpp 
class Solution {
public:
    int findMin(vector<int>& nums) {
        if (nums.empty()) throw std::invalid_argument("vector can't be empty!");
        
        int low(0), high(nums.size() - 1);     
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] > nums[high]) {
                low = mid + 1;
            } else if (nums[mid] < nums[high]){
                high = mid;
            } else {
                -- high;
            }
        }
        
        return nums[low];
    }
};
```
