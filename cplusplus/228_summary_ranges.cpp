class Solution {
 public:
  vector<string> summaryRanges(vector<int>& nums) {
    const int nums_size(nums.size());
    if (nums_size < 1) return vector<string>();
    vector<string> reval;
    for (int i = 0; i < nums_size;) {
      int end = i;
      while (end + 1 < nums_size && nums[end + 1] == nums[end] + 1) ++end;
      const std::string& item = (i == end ? std::to_string(nums[i])
                                          : std::to_string(nums[i]) + "->" +
                                                std::to_string(nums[end]));
      reval.push_back(item);

      i = end + 1;
    }
    return reval;
  }
};
