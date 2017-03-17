class Solution {
public:
  int maxSubArray(vector<int>& nums) {
    int reval(INT_MIN), max_include_curr(0);
    for (int num : nums) {
      max_include_curr = std::max(num,max_include_curr+num);
      reval = std::max(reval,max_include_curr);
    }
    return reval;
  }
};
