class Solution {
public:
  void nextPermutation(vector<int>& nums) {
    if (nums.size()<=1) return;
    int i = nums.size()-2;
    while (i>=0) {
      if (nums[i]<nums[i+1]) {
        break;
      } else {
        --i;
      }
    }
    std::reverse(nums.begin()+i+1,nums.end());
    if (i==-1) return;
    auto iter = std::upper_bound(nums.begin()+i+1,nums.end(),nums[i]);
    std::swap(nums[i],*iter);
  }
};
