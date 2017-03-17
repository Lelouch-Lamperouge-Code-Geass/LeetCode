/*
Notice that nums[mid] can have two status, each status divide the 
vectory into two parts.
(1) nums[mid] < nums[high], then [mid,high] is increasing
(2) nums[mid] > nums[high], then [low,mid] is increasing
We can use binary search based on the status.
*/
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
