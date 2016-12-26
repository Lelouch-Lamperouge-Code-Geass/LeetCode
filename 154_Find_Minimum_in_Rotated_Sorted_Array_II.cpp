/*
 * case 1 : 3,3,3,3,3,3,3,3,0,1,2,3
 * case 2 : 3,3,0,1,2,3,3,3,3,3,3,3
 * Therefore, when nums[mid] == nums[high], we can only decrease high.
 * I prefer to compare nums[mid] with nums[high] instead of nums[low],
 * because nums[mid] could equal to nums[low] which is one more scenario
 * we have to handle.
*/
class Solution {
 public:
  int findMin(vector<int>& nums) {
    if (nums.empty()) return INT_MIN;
    int low(0), high(nums.size() - 1);
    while (low < high) {
      int mid = low + (high - low) / 2;
      if (nums[mid] > nums[high]) {
        low = mid + 1;
      } else if (nums[mid] < nums[high]) {
        high = mid;
      } else if (nums[mid] == nums[high]) {
        --high;
      }
    }
    return nums[low];
  }
};
