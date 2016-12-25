class Solution {
public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> res;
    std::sort(nums.begin(),nums.end());
    const std::size_t nums_size(nums.size());
    for (std::size_t i=0;i<nums_size;++i) {
      std::size_t low(i+1),high(nums_size-1);
      while (low<high) {
        int sum = nums[i]+nums[low]+nums[high];
        const int cur_high(nums[high]), cur_low(nums[low]);
        if (sum==0) {
          res.push_back({nums[i],nums[low],nums[high]});
          while(low<high && nums[low]==cur_low) ++ low;
          while(low<high && nums[high]==cur_high) -- high;
        } else if (sum>0) {
          while(low<high && nums[high]==cur_high) -- high;
        } else {
          while(low<high && nums[low]==cur_low) ++ low;
        }
      }
      while (i+1<nums_size && nums[i+1]==nums[i]) ++i;
    }
    return res;
  }
};
