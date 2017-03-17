class Solution {
public:
  vector<int> productExceptSelf(vector<int>& nums) {
    const int nums_size(nums.size());
    vector<int> reval(nums_size,1);

    int pre(1);
    for (int i=0;i<num_size;++i) {
      reval[i] *= pre;
      pre *= nums[i];
    }

    pre = 1;
    for (int i=num_size-1;i>=0;--i) {
      reval[i] *= pre;
      pre *= nums[i];
    }
    return reval;
  }
};
