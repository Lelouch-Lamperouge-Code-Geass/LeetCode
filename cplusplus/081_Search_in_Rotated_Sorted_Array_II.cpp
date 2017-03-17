class Solution {
public:
  bool search(vector<int>& nums, int target) {
    int low(0),high(nums.size()-1);
    while(low<=high){
      int mid = low + (high - low)/2;
      if(nums[mid] == target){
        return true;
      } else {
        if(nums[mid]< nums[high]){//[mid,high] is sorted
          if(target>nums[mid] && target<=nums[high]){
            low = mid + 1;
          } else {
            high = mid - 1;
          }
        } else if(nums[mid] > nums[high]){//[low,mid] is sorted
          if(target>=nums[low] && target<nums[mid]){
            high = mid - 1;
          } else {
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
