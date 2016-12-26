
/*
 * Solution 1
*/
class Solution {
public:
  int findMin(vector<int>& nums) {
    if (nums.empty()) return INT_MIN;
    int low(0), high(nums.size()-1);
    while (low < high) {
      if(nums[low] < nums[high] ) {
        return nums[low];
      } else {
        int mid = low + (high - low) / 2;
        if (nums[mid] < nums[high]){
          high = mid;
        } else {
          low = mid + 1;
        }
      }
    }
    return nums[low];
  }
};

/*
 * Solution 2
 */
class Solution {
public:
  int findMin(vector<int>& nums) {
    if (nums.empty()) return INT_MIN;
    int low(0), high(nums.size()-1);
    while (low<high) {
      if(nums[low]<nums[high]) return nums[low];
      int mid = low + (high-low) / 2;
      if (nums[mid]>=nums[low]) { // including nums[mid]==nums[low] here
        low = mid + 1;
      } else {
        high = mid;
      }
    }
    return nums[low];
  }
};
