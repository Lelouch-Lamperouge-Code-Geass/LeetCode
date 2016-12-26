/*
Solution 1
*/

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

/*
Solution 2
*/

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
