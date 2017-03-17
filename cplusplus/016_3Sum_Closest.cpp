class Solution {
public:
  int threeSumClosest(vector<int>& nums, int target) {
    if(nums.size()<=3) {
      return std::accumulate(nums.begin(), nums.end(), 0);
    }
    int reval(nums[0]+nums[1]+nums[2]);
    std::sort(nums.begin(),nums.end());
    const std::size_t nums_size(nums.size());
    for (std::size_t i=0;i<nums_size;++i) {
      std::size_t low(i+1),high(nums_size-1);
      while (low<high) {
        int sum = nums[i]+nums[low]+nums[high];
        if (sum==target) {
          return target;
        }

        if (std::abs(sum-target)<std::abs(reval-target)) reval = sum;

        const int cur_high(nums[high]), cur_low(nums[low]);
        if (sum>target) {
          while(low<high && nums[high]==cur_high) -- high;
        } else {
          while(low<high && nums[low]==cur_low) ++ low;
        }
      }
      while (i+1<nums_size && nums[i+1]==nums[i]) ++i;
    }
    return reval;

  }
};
