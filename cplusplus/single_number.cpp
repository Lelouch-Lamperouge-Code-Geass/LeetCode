// Copyright (C) 2016 by yangliu
int singleNumber(vector<int>& nums) {
  return std::accumulate(nums.begin(),nums.end(),0,std::bit_xor<int>());
}
