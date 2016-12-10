class Solution {
public:
  void moveZeroes(vector<int>& nums) {
    int index(-1),nums_size(nums.size());
    for (int i=0;i<nums_size;++i) {
      if (nums[i]!=0) {
        std::swap(nums[++index],nums[i]);
      }
    }
  }
};
