class Solution {
public:
  bool canJump(vector<int>& nums) {
    std::size_t reach(0), nums_size(nums.size());
    for (std::size_t i=0;i<=reach && i<nums_size;++i) {
      reach = std::max(reach,i+nums[i]);
    }
    return nums.empty() || reach >= nums_size - 1;
  }
};
