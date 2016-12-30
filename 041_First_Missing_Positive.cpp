class Solution {
public:
  int firstMissingPositive(vector<int>& nums) {
    const std::size_t nums_size(nums.size());
    for (std::size_t i=0;i<nums_size;++i) {
      while (nums[i]!=i+1
                             && nums[i]-1>=0
                             && nums[i]-1<nums_size
             && nums[i]!=nums[nums[i]-1]) {
        std::swap(nums[i],nums[nums[i]-1]);
      }
    }

    int index(0);
    while (index<nums_size) {
      if (nums[index]!= index+1) break;
      ++ index;
    }
    return index+1;
  }
};
