// Copyright (C) 2016 by Yang Liu
class Solution {
public:
  int maximumGap(vector<int>& nums) {
    const int n(nums.size());
    if (n<2) return 0;
    // get total number of buckets and bucket size
    int min_val = * std::min_element(nums.begin(),nums.end());
    int max_val = * std::max_element(nums.begin(),nums.end());
    int range = max_val - min_val;
    int bucket_width = range / n + 1; // range might be smaller than n
    int bucket_num = range / bucket_width + 1; // range might be 0

    // track the maimum and minimum value of every buckets
    vector<int> bucket_min(bucket_num,INT_MAX), bucket_max(bucket_num,INT_MIN);
    for (int num : nums) {
      int id = (num - min_val) / bucket_width ;
      bucket_min[id] = std::min(bucket_min[id],num);
      bucket_max[id] = std::max(bucket_max[id],num);
    }

    int pre_max(min_val),max_gap(0);
    for (int i=0;i<bucket_num;++i) {
      if (bucket_min[i]==INT_MAX) continue; // empty bucket
      int cur_gap = bucket_min[i] - pre_max;
      max_gap = std::max(max_gap,cur_gap);
      pre_max = bucket_max[i];
    }
    return max_gap;
  }
};
