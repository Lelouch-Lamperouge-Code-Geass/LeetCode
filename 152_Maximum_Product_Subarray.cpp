// Copyright (C) 2016 by Yang Liu
class Solution {
public:
  int maxProduct(vector<int>& nums) {
    if (nums.empty()) return INT_MIN;
    const int n (nums.size());
    int pre_max(nums[0]),pre_min(nums[0]),reval(nums[0]);
    for (int i=1;i<n;++i) {
      int cur_max = std::max( std::max (pre_max*nums[i],pre_min*nums[i]),nums[i]);
      int cur_min = std::min( std::min (pre_max*nums[i],pre_min*nums[i]),nums[i]);
      pre_max = cur_max;
      pre_min = cur_min;
      reval = std::max(reval,cur_max);
    }
    return reval;
  }
};
