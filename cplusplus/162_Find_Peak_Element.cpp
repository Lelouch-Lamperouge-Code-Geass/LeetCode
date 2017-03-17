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
