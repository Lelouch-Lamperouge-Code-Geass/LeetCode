class Solution {
public:
  // n distinct numbers gave the hint.
  // won't work if not distince
  int missingNumber(vector<int>& nums) {
    const int n(nums.size());
    int reval(0);
    for (int i=0;i<n;++i) {
      reval ^= nums[i];
      reval ^= i;
    }
    reval ^= n;
    return reval;
  }
};
